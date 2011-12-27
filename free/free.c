#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/sysctl.h>
#include <uvm/uvm_param.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/swap.h>

void getmem(void);

int
main(int argc, char *argv[])
{
  int ch, kflag, mflag, gflag;
  while ((ch = getopt(argc, argv, "kmg")) != -1)
    switch(ch) {
    case 'k':
      kflag = 1;
      break;
    case 'm':
      mflag = 1;
      break;
    case 'g':
      gflag = 1;
      break;
    }
  argc -= optind;
  argv += optind;

  getmem();
  return 0;
}

/* get memory stats */
void
getmem(void)
{
  struct uvmexp_sysctl uvmstat;
  size_t physm_s, uvmstat_s;
  uvmstat_s = sizeof(uvmstat);
  sysctlbyname("vm.uvmexp2", &uvmstat, &uvmstat_s, NULL, 0);
  printf("\ttotal\t\tused\t\tfree\n");
  printf("Mem:\t%d\t%d\t%d\n", uvmstat.npages*uvmstat.pagesize, uvmstat.npages*uvmstat.pagesize-uvmstat.free*uvmstat.pagesize, uvmstat.free*uvmstat.pagesize);
  printf("Swap:\t%d\t%d\t%d\n", uvmstat.swpages*uvmstat.pagesize, uvmstat.swpginuse*uvmstat.pagesize, uvmstat.swpages*uvmstat.pagesize-uvmstat.swpginuse*uvmstat.pagesize); 
}
