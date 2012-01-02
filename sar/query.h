#define CREATE_TABLE_SQL "CREATE TABLE 'sar' \
( 'date' TEXT, \
'load1' INTEGER, 'load5' INTEGER, 'load15' INTEGER, \
'pagesize' INTEGER, 'pagemask' INTEGER, 'pageshift' INTEGER, 'npages' INTEGER, \
'free' INTEGER, 'active' INTEGER, 'inactive' INTEGER, 'paging' INTEGER, \
'wired' INTEGER, 'zeropages' INTEGER, 'reserve_pagedaemon' INTEGER, 'reserve_kernel' INTEGER, \
'freemin' INTEGER, 'freetarg' INTEGER, 'wiredmax' INTEGER, 'nswapdev' INTEGER, 'swpages' INTEGER, \
'swpginuse' INTEGER, 'swpgonly' INTEGER, 'nswget' INTEGER, 'unused1' INTEGER, \
'cpuhit' INTEGER, 'cpumiss' INTEGER, 'faults' INTEGER, 'traps' INTEGER, 'intrs' INTEGER, \
'swtch' INTEGER, 'softs' INTEGER, 'syscalls' INTEGER, 'pageins' INTEGER, 'swapins' INTEGER, \
'swapouts' INTEGER, 'pgswapin' INTEGER, 'pgswapout' INTEGER, 'forks' INTEGER, 'forks_ppwait' INTEGER, \
'forks_sharevm' INTEGER, 'pga_zerohit' INTEGER, 'pga_zeromiss' INTEGER, 'zeroaborts' INTEGER, \
'fltnoram' INTEGER, 'fltnoanon' INTEGER, 'fltpgwait' INTEGER, \
'fltpgrele' INTEGER, 'fltrelck' INTEGER, 'fltrelckok' INTEGER, 'fltanget' INTEGER, \
'fltanretry' INTEGER, 'fltamcopy' INTEGER, 'fltnamap' INTEGER, 'fltnomap' INTEGER, \
'fltlget' INTEGER, 'fltget' INTEGER, 'flt_anon' INTEGER, 'flt_acow' INTEGER, \
'flt_obj' INTEGER, 'flt_prcopy' INTEGER, 'flt_przero' INTEGER, 'pdwoke' INTEGER, \
'pdrevs' INTEGER, 'pdswout' INTEGER, 'pdfreed' INTEGER, 'pdscans' INTEGER, \
'pdanscan' INTEGER, 'pdobscan' INTEGER, 'pdreact' INTEGER, 'pdbusy' INTEGER, \
'pdpageouts' INTEGER, 'pdpending' INTEGER, 'pddeact' INTEGER, 'anonpages' INTEGER, \
'filepages' INTEGER, 'execpages' INTEGER, 'colorhit' INTEGER, 'colormiss' INTEGER, \
'ncolors' INTEGER );"
