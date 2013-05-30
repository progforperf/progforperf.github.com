#
BHOME	=$(PWD)
#
F90	= ifort
CC	= icc
#
#
COMP	= -openmp
FOMP	= -openmp
COPTS	=  -O3 -fno-alias -fno-inline
FOPTS	=  -O3 -fno-inline
FLONG	= 
#
#
NOLINK= -c
#


J3D_F.exe: j3d_f.o timing.o dummy.o
	$(F90) $(FOMP) -o J3D_F.exe j3d_f.o timing.o dummy.o

J3D_C.exe: j3d_c.o timing.o dummy.o
	$(CC) $(COMP) -o J3D_C.exe j3d_c.o timing.o dummy.o

all: J3D_F.exe J3D_C.exe

%.o: %.c
	$(CC) $(COPTS) $(COMP) $(NOLINK) $<

%.o: %.f90
	$(F90) $(FOPTS) $(FOMP) $(NOLINK) $<

clean:
	rm -f *.o *.exe

