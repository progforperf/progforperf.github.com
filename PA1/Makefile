CFLAGS?=-std=c99 -D_GNU_SOURCE -Wall -O2

default: all

all: 

report: report.pdf

bin:
	mkdir bin

bin/test bin/test1: src/test.c
	$(CC) $(CFLAGS) -o bin/test $<
	$(CC) $(CFLAGS) -DPARALLEL -pthread -o bin/test1 $<

report.pdf: report/report.tex
	cd report && pdflatex report.tex && pdflatex report.tex
	mv report/report.pdf report.pdf

clean:
	rm -r bin

