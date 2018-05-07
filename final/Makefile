CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	final

all:		$(TARGETS)

final.o: final.c
	$(CC) $(CFLAGS) -c -o final.o final.c

final: final.o
	$(CC) $(LDFLAGS) -o final final.o

clean:
	rm -f $(TARGETS)
