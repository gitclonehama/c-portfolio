project = bin2oct

objs = main.o bin2oct.o
testobjs = tests.o bin2oct.o
filesdir = /user/cse320/files
testdir = $(COA_ARM64)/lib/coa/tests/$(project)

CC=gcc
CFLAGS := $(CFLAGS) -Wall

CLEANEXTS   = o

outputfile  = $(project)

# Default target
.PHONY: all
all: $(outputfile)

$(outputfile): $(objs)
	gcc -o $(outputfile) $(objs) $(LDLIBS)

.PHONY: clean 
clean:
	rm -f $(outputfile)
	rm -f test320
	for file in $(CLEANEXTS); do rm -f *.$$file; done

tester: $(testobjs)
	gcc -o tester $(testobjs) -L$(COA_ARM64)/lib -lgrlcoa -lm

.PHONY: test
test: tester
	./tester

.PHONY: tests
tests: test
 
tests.o: $(testdir)/tests.c bin2oct.h
	gcc -c $(CFLAGS) -I. -I$(COA_ARM64)/include $(testdir)/tests.c -lm

# Indicate dependencies of .ccp files on .hpp files
main.c: bin2oct.h
bin2oct.c: bin2oct.h
