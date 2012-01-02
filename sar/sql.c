#include <stdio.h>
#include <sys/types.h>
#include <sqlite3.h>
/* do some basic sqlite3 stuff */
#include "query.h"

int
main(int argc, char *argv[])
{
  sqlite3 *dbc;
  char *err;

  sqlite3_open_v2(argv[1], &dbc, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE, NULL);
  sqlite3_exec(dbc, CREATE_TABLE_SQL, NULL, NULL, &err);

  sqlite3_close(dbc);
  if ( err )
    printf("%s\n", err);
  return 0;
}
