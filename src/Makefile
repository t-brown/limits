#
#

CFLAGS  += -fPIC
FCFLAGS += -fPIC

.PHONY:
.PHONY: all clean install

.SUFFIXES:
.SUFFIXES: .c .h .F90

BINDIR = $(PREFIX)/bin
LIBDIR = $(PREFIX)/lib

LIB = liblimits.so

all: test $(LIB)

install: all
	install -d $(BINDIR)
	install -m 750 -s -t $(BINDIR) test
	install -d $(LIBDIR)

test: test.o $(LIB)
	$(FC) $(FCFLAGS) -o $@ $^ $(LDFLAGS)

$(LIB): rlimit.o plimit.o
	$(FC) -shared $(FCFLAGS) -o $(LIB) $^


clean:
	$(RM) $(LIB) *.o *.mod test

# Rules
%.o: %.F90
	$(FC) $(FCFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Dependencies
test.o: test.F90 rlimit.o plimit.o
rlimit.o: rlimit.F90 plimit.o
plimit.o: plimit.c
