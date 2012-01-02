#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/sysctl.h>
#include <uvm/uvm_param.h>
#include <sys/resource.h>
#include <sys/types.h>

#include "sar.h"
#include "query.h"

int
main(int argc, char *argv[])
{
  int ch, aflag;
  while ((ch = getopt(argc, argv, "A")) != -1)
    switch(ch) {
    case 'A':
      aflag = 1;
      break;
    }
  argc -= optind;
  argv += optind;

  if (aflag) {
    // print what we have for today
    getld();
    getmem();
  }
  return 0;
}

/* get the system load - vm.loadavg */
void
getld(void)
{
  struct loadavg load;
  size_t load_s;
  load_s = sizeof(load);
  sysctlbyname("vm.loadavg", &load, &load_s, NULL, 0);
//  printf("load: %4.2f,%4.2f,%4.2f\n", (double)load.ldavg[0]/load.fscale,(double)load.ldavg[1]/load.fscale,(double)load.ldavg[2]/load.fscale);
}


/* get memory stats */
void
getmem(void)
{
  uint64_t physm;
  struct uvmexp_sysctl uvmstat;
  size_t physm_s, uvmstat_s;
  physm_s = sizeof(physm);
  uvmstat_s = sizeof(uvmstat);
  sysctlbyname("hw.physmem64", &physm, &physm_s, NULL, 0);
  sysctlbyname("vm.uvmexp2", &uvmstat, &uvmstat_s, NULL, 0);
//  printf("mem: %d,%d,%d,%d,%d,%d\n", physm,uvmstat.npages*uvmstat.pagesize,uvmstat.free*uvmstat.pagesize); 
}

void
getnet(void)
{

}
