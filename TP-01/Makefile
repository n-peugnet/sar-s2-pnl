CFLAGS = -Wall -g

.PHONY : all clean check
.ONESHELL:

CHECK_PATCH=./checkpatch.pl --no-tree

all : testVersion testOffset testCommit testHistory

%.o : %.c
	gcc $(CFLAGS) -c $<

testVersion : testVersion.c version.o
	gcc $(CFLAGS) $^ -o $@

testOffset : testOffset.c version.o
	gcc $(CFLAGS) $^ -o $@

testCommit : testCommit.c version.o commit.o history.o
	gcc $(CFLAGS) $^ -o $@

testHistory : testHistory.c version.o commit.o history.o
	gcc $(CFLAGS) $^ -o $@

check : 
	for f in *.c *.h ; do
		$(CHECK_PATCH) -f $$f
	done

clean :
	rm -rf *.o testVersion testCommit testOffset
