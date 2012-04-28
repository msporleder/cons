#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <poll.h>

/* This is a program by Matthew Sporleder
 * It will send and receive messages to/from a multicast ip and port
 * It should just compile with gcc -o mc mc.c
 * Run as ./mc 230.0.0.10 9999 message1
*/

int join_mcast( char *, uint16_t ); /* join mcast group and port */

static int sock, to;
static struct sockaddr_storage msrv, tosrv;
static socklen_t len;

int main(int argc, char *argv[])
{
	int ret = 0;
	ssize_t send_ret, recv_ret;
	char send_msg[1024];
	char buf[1024];
	uint32_t port;
	struct pollfd fds;

	if (argc < 3) { return 1; }

	memset(&send_msg, 0, sizeof(send_msg));
	strncpy(send_msg, argv[3], 1024);

	port = atoi(argv[2]);
	ret = join_mcast( argv[1], port );
	if (ret != 0) { return ret; }
	for(;;)
	{
		memset(&fds, 0, sizeof(fds));
		fds.fd = to;
		fds.events = POLLOUT;
		if( poll(&fds, 1, 0) > 0 )
		{
			send_ret = sendto(to, &send_msg, sizeof(send_msg), 0, (struct sockaddr *)&tosrv, len);
			if (send_ret < 0) { perror("sendto"); return send_ret; }
			if (send_ret == 0)
			{
				printf("SEND: nothing\n");
			} else {
				printf("SEND:%s\n", send_msg);
			}
		} else {
			perror("poll error writing\n"); return -1;
		}
		memset(&buf, 0, sizeof(buf));
		memset(&fds, 0, sizeof(fds));
		fds.fd = sock;
		fds.events = POLLIN;
		if( poll(&fds, 1, 3000) > 0 )
		{
			recv_ret = recvfrom(sock, &buf, sizeof(buf), 0, (struct sockaddr *)&msrv, &len); 
			if( recv_ret > 0 )
			{
				printf("READ:%s\n", buf);
				fflush(stdout);
			}
		}
		sleep(3);
	}
}

int join_mcast( char *mcast, uint16_t port )
{
	int setopt_ret, bind_ret, getsockname_ret, re = 1;
	struct ip_mreq mreq;
	u_char loop = 1;

/* setup the socket for multicast */
	memset(&mreq, 0, sizeof(mreq));
	memset(&msrv, 0, sizeof(msrv));
	memset(&msrv, 0, sizeof(tosrv));
	mreq.imr_multiaddr.s_addr = inet_addr(mcast);
	mreq.imr_interface.s_addr = INADDR_ANY;
	msrv.ss_family = AF_INET;
	tosrv.ss_family = AF_INET;

	sock = socket( msrv.ss_family, SOCK_DGRAM, IPPROTO_UDP ); /* ipv4 udp/ip */
	if (sock == -1) { perror("socket"); return sock; }
	to = socket( tosrv.ss_family, SOCK_DGRAM, IPPROTO_UDP ); /* ipv4 udp/ip */
	if (sock == -1) { perror("socket"); return sock; }

	setopt_ret = setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, &re, sizeof(re));
	if (setopt_ret < 0) { perror("setsockopt reuse"); return setopt_ret; }

/* join the multicast group */
	setopt_ret = setsockopt( sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
	if (setopt_ret < 0) { perror("setsockopt"); return setopt_ret; }
/* loop back our own traffic? */
	setopt_ret = setsockopt( sock, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));
	if (setopt_ret < 0) { perror("setsockopt"); return setopt_ret; }
	setopt_ret = setsockopt( sock, IPPROTO_IP, IP_MULTICAST_IF, &mreq.imr_interface.s_addr, sizeof(mreq.imr_interface.s_addr));
	if (setopt_ret < 0) { perror("setsockopt"); return setopt_ret; }

/* setup msrv for its many uses */
	len = sizeof(msrv);
	getsockname_ret = getsockname(sock, (struct sockaddr *)&msrv, &len);
	if (getsockname_ret < 0) { perror("getsockname"); return getsockname_ret; }
	((struct sockaddr_in *)&msrv)->sin_port = htons(port);
	((struct sockaddr_in *)&msrv)->sin_addr.s_addr = mreq.imr_multiaddr.s_addr;

	len = sizeof(tosrv);
	getsockname_ret = getsockname(to, (struct sockaddr *)&tosrv, &len);
	if (getsockname_ret < 0) { perror("getsockname"); return getsockname_ret; }
	((struct sockaddr_in *)&tosrv)->sin_port = htons(port);
	((struct sockaddr_in *)&tosrv)->sin_addr.s_addr = mreq.imr_multiaddr.s_addr;

/*	((struct sockaddr_in *)&msrv)->sin_family = AF_INET; */
/*	((struct sockaddr_in *)&msrv)->sin_len = sizeof(struct sockaddr_in); */

	bind_ret = bind(sock, (struct sockaddr *)&msrv, len);
	if (bind_ret < 0) { perror("bind"); return bind_ret; }
	return 0;
}
