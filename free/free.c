#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/sysctl.h>
#include <uvm/uvm_param.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/swap.h>

void getmem(long);

int
main(int argc, char *argv[])
{
  int ch;
  long flag = 1;
  while ((ch = getopt(argc, argv, "kmg")) != -1)
    switch(ch) {
    case 'k':
      flag = 1024;
      break;
    case 'm':
      flag = 1024*1024;
      break;
    case 'g':
      flag = 1024*1024*1024;
      break;
    }

  argc -= optind;
  argv += optind;

  getmem(flag);
  return 0;
}

/* get memory stats */
void
getmem(long flag)
{
  struct uvmexp_sysctl uvmstat;
  size_t physm_s, uvmstat_s;
  uvmstat_s = sizeof(uvmstat);
  sysctlbyname("vm.uvmexp2", &uvmstat, &uvmstat_s, NULL, 0);
  printf("\ttotal\t\tused\t\tfree\n");
  printf("Mem:\t%8d\t%8d\t%8d\n", uvmstat.npages*uvmstat.pagesize/flag, (uvmstat.npages*uvmstat.pagesize-uvmstat.free*uvmstat.pagesize)/flag, uvmstat.free*uvmstat.pagesize/flag);
  printf("Swap:\t%8d\t%8d\t%8d\n", uvmstat.swpages*uvmstat.pagesize/flag, uvmstat.swpginuse*uvmstat.pagesize/flag, (uvmstat.swpages*uvmstat.pagesize-uvmstat.swpginuse*uvmstat.pagesize)/flag); 
}
