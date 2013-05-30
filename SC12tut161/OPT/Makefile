#
BHOME	=$(PWD)
#
F90	= ifort
CC	= icc
#
#
COMP	= 
FOMP	= 
COPTS	=  -O3 
FOPTS	=  -O3 
FLONG	= 
#
#
NOLINK= -c
#

OPT_C.exe: opt_c.o timing.o dummy.o
	$(CC) $(COMP) -o $@ $^

OPT_F.exe: opt_f.o timing.o dummy.o
	$(F90) $(FOMP) -o $@ $^

all: OPT_F.exe OPT_C.exe

%.o: %.c
	$(CC) $(COPTS) $(COMP) $(NOLINK) $<

%.o: %.f90
	$(F90) $(FOPTS) $(FOMP) $(NOLINK) $<

clean:
	rm -f *.o *.exe

