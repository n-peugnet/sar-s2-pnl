.PHONY : all clean check
.ONESHELL:

CHECK_PATCH=../../../../biblio/eudyptula/torvalds/scripts/checkpatch.pl

all : cron_func

%.o : %.c
	gcc -Wall -c $<

cron_func : cron_func.o nothing.o
	gcc -Wall $^ -o $@

check :
	for f in *.c *.h ; do
		$(CHECK_PATCH) -f $$f
	done

clean :
	rm -rf *.o cron_func
