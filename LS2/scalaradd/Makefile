gcc: scalaradd.c funcs.h rdtsc.h
	gcc -O3 -fno-tree-vectorize $< -o scalaradd -lm

icc: scalaradd.c funcs.h rdtsc.h
	icc -O3 -no-vec $< -o scalaradd

clean:
	rm scalaradd
