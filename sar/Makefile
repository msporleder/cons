all : sar sql

sar : sar.c sar.h query.h
	gcc -o sar -g sar.c

sql : sql.c query.h
	gcc -I/usr/pkg/include -L/usr/pkg/lib -Wl,-R/usr/pkg/lib -o sql sql.c -lsqlite3
