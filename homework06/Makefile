CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs

TARGETS=	libstr.a libstr.so str-static str-dynamic

all:		$(TARGETS)

test:
	@$(MAKE) -sk test-all

test-all:	test-libstr test-str

test-libstr:	libstr.so test_libstr.py
	curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/homework06/test_libstr.py
	chmod +x test_libstr.py
	./test_libstr.py -v

test-str:	str-static str-dynamic test_str.sh
	curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/homework06/test_str.sh
	chmod +x test_str.sh
	./test_str.sh

clean:
	rm -f $(TARGETS) *.o

library.o:	library.c str.h
	$(CC) $(CFLAGS) -fPIC -c -o library.o library.c

main.o: main.c str.h
	$(CC) $(CFLAGS) -c -o main.o main.c

libstr.a:	library.o
	$(AR) $(ARFLAGS) libstr.a library.o

libstr.so:	library.o
	$(CC) $(LDFLAGS) -shared -o libstr.so library.o

str-dynamic: main.o libstr.so
	$(CC) $(LDFLAGS) -o str-dynamic main.o -lstr

str-static:	main.o libstr.a
	$(CC) -o str-static main.o libstr.a
