project = armstrong

# Object files with paths
objs = $(project).o ../digitcounter/digitcounter.o
testobjs = tests.o $(project).o ../digitcounter/digitcounter.o
testdir = $(COA_ARM64)/lib/coa/tests/$(project)

CC = gcc
CFLAGS := $(CFLAGS) -I$(COA_ARM64)/include -Wall
LDLIBS := $(LDLIBS) -L$(COA_ARM64)/lib -lgrlcoa

CLEANEXTS = o

outputfile = $(project)

# Default target
.PHONY: all
all: $(outputfile)

$(outputfile): $(objs)
	$(CC) -o $(outputfile) $(objs) $(LDLIBS)

# Rule for compiling .S files in the current directory
%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule for compiling .S files in the digitcounter directory
../digitcounter/%.o: ../digitcounter/%.S
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(outputfile)
	rm -f tester
	for file in $(CLEANEXTS); do rm -f *.$$file; done

tester: $(testobjs)
	$(CC) -o tester $(testobjs) $(LDLIBS)

.PHONY: test
test: tester
	./tester
#	valgrind ./tester

.PHONY: tests
tests: test

tests.o: $(testdir)/tests.c
	$(CC) -c $(CFLAGS) -I. $(testdir)/tests.c
