#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/param.h>
#include <sys/sysctl.h>
#include <uvm/uvm_param.h>


void getload(long);

int
main(int argc, char *argv[])
{
  getload(3);
  return 0;
}

/* get memory stats */
void
getload(long flag)
{
  struct loadavg load;
  size_t load_s;
  load_s = sizeof(load);
  if ( sysctlbyname("vm.loadavg", &load, &load_s, NULL, 0) == -1 )
    exit -1;
/*
  double load[3];
  getloadavg(load, flag);
  printf("%.3f\t%.3f\t%.3f\n", load[0], load[1], load[2]);
*/
}
