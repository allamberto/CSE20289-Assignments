CC=             gcc
CFLAGS=         -g -gdwarf-2 -Wall -std=gnu99
TARGETS=        sort grep

all:            $(TARGETS)

sort:
	$(CC) $(CFLAGS) -o sort sort.c
grep:
	$(CC) $(CFLAGS) -o grep grep.c

test:
	       @$(MAKE) -sk test-all

test-all:	test-sort test-grep

test-sort:	sort
	curl -LO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/reading08/test_sort.sh
	chmod +x test_sort.sh
	./test_sort.sh

test-grep:	grep
	curl -LO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/reading08/test_grep.sh
	chmod +x test_grep.sh
	./test_grep.sh

clean:
	rm -f $(TARGETS)

.SUFFIXES:
