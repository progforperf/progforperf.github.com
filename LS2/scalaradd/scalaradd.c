#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "rdtsc.h" // Timing macros

#define NUM_RUNS 50
#define CYCLES_REQUIRED 1E8

#include "funcs.h" // Reduction functions

/*
 * microbench: timing setup
 * k: number of accumulators
 * l: unrolling factor
 * v: input vector of double precision elements
 * n: length of the input vector
 */
double microbench(char k, char l, double *v, double *dest, size_t n) {
  int i, num_runs;
  double cycles;
  tsc_counter start, end;
  
  num_runs = NUM_RUNS;
  
  // Cache warm-up for at least CYCLES_REQUIRED cycles,
  // recording the required number of executions

  CPUID(); RDTSC(start); RDTSC(end);
  CPUID(); RDTSC(start); RDTSC(end);
  CPUID(); RDTSC(start); RDTSC(end);

  while(1) {
    CPUID(); RDTSC(start);

    for(i = 0; i < num_runs; i++) {

      switch(k) {
        case 1:
          switch(l) {
            case 1:
              reduction_K1_L1(v, dest, n);
              break;
            case 2:
              reduction_K1_L2(v, dest, n);
              break;
            case 3:
              reduction_K1_L3(v, dest, n);
              break;
            case 4:
              reduction_K1_L4(v, dest, n);
              break;
            case 5:
              reduction_K1_L5(v, dest, n);
              break;
            case 6:
              reduction_K1_L6(v, dest, n);
              break;
            default: ;
          }
          break;
        case 2:
          switch(l) {
            case 2:
              reduction_K2_L2(v, dest, n);
              break;
            case 4:
              reduction_K2_L4(v, dest, n);
              break;
            case 6:
              reduction_K2_L6(v, dest, n);
              break;
            default: ;
          }
          break;
        case 3:
          switch(l) {
            case 3:
              reduction_K3_L3(v, dest, n);
              break;
            case 6:
              reduction_K3_L6(v, dest, n);
              break;
            default: ;
          }
          break;
        case 4:
          switch(l) {
            case 4:
              reduction_K4_L4(v, dest, n);
              break;
            default: ;
          }
          break;
        case 5:
          switch(l) {
            case 5:
              reduction_K5_L5(v, dest, n);
              break;
            default: ;
          }
          break;
        case 6:
          switch(l) {
            case 6:
              reduction_K6_L6(v, dest, n);
              break;
            default: ;
          }
          break;
        default: ;
      }

    }
    
    RDTSC(end); CPUID();

    cycles = ((double)COUNTER_DIFF(end, start));

    if(cycles >= CYCLES_REQUIRED) break;

    num_runs *= 2;

  }
  
  //Measurement of the selected function
  CPUID(); RDTSC(start);

  for(i = 0; i < num_runs; i++) {

    switch(k) {
      case 1:
        switch(l) {
          case 1:
            reduction_K1_L1(v, dest, n);
            break;
          case 2:
            reduction_K1_L2(v, dest, n);
            break;
          case 3:
            reduction_K1_L3(v, dest, n);
            break;
          case 4:
            reduction_K1_L4(v, dest, n);
            break;
          case 5:
            reduction_K1_L5(v, dest, n);
            break;
          case 6:
            reduction_K1_L6(v, dest, n);
            break;
          default: ;
        }
        break;
      case 2:
        switch(l) {
          case 2:
            reduction_K2_L2(v, dest, n);
            break;
          case 4:
            reduction_K2_L4(v, dest, n);
            break;
          case 6:
            reduction_K2_L6(v, dest, n);
            break;
          default: ;
        }
        break;
      case 3:
        switch(l) {
          case 3:
            reduction_K3_L3(v, dest, n);
            break;
          case 6:
            reduction_K3_L6(v, dest, n);
            break;
          default: ;
        }
        break;
      case 4:
        switch(l) {
          case 4:
            reduction_K4_L4(v, dest, n);
            break;
          default: ;
        }
        break;
      case 5:
        switch(l) {
          case 5:
            reduction_K5_L5(v, dest, n);
            break;
          default: ;
        }
        break;
      case 6:
        switch(l) {
          case 6:
            reduction_K6_L6(v, dest, n);
            break;
          default: ;
        }
        break;
      default: ;
    }

  }
  
  RDTSC(end); CPUID();
  
  cycles = ((double)COUNTER_DIFF(end, start)) / ((double) num_runs);

  return cycles;
}


int main(int argc, char **argv){
  
  long int i, j, n;
  double *x, dest, r;
  
  if(argc != 2) {
    printf("Usage: ./microbench <filename>\n");
    abort();
  }
  
  FILE * file = fopen(argv[1], "w");
  
  n = 2000;
  x = (double*)malloc(n*sizeof(double));
  for(j = 0; j < n; j++) x[j] = 1.;
  
  // Output in tabular format, with K rows and L columns.
  // Positions with no measurements are filled with 0s.
  printf("Testing: K = 1 and L = 1...");
  r = microbench(1, 1, x, &dest, n);
  printf("dest = %f\n", dest);
  fprintf(file, "%f,", r/n);
  printf("Testing: K = 1 and L = 2...");
  r = microbench(1, 2, x, &dest, n);
  printf("dest = %f\n", dest);
  fprintf(file, "%f,", r/n);
  printf("Testing: K = 1 and L = 3...");
  r = microbench(1, 3, x, &dest, n);
  printf("dest = %f\n", dest);
  fprintf(file, "%f,", r/n);
  printf("Testing: K = 1 and L = 4...");
  r = microbench(1, 4, x, &dest, n);
  printf("dest = %f\n", dest);
  fprintf(file, "%f,", r/n);
  printf("Testing: K = 1 and L = 5...");
  r = microbench(1, 5, x, &dest, n);
  printf("dest = %f\n", dest);
  fprintf(file, "%f,", r/n);
  printf("Testing: K = 1 and L = 6...");
  r = microbench(1, 6, x, &dest, n);
  printf("dest = %f\n", dest);
  fprintf(file, "%f\n", r/n);
  fprintf(file, "0,");
  printf("Testing: K = 2 and L = 2...");
  r = microbench(2, 2, x, &dest, n);
  printf("dest = %f\n", dest);
  fprintf(file, "%f,", r/n);
  fprintf(file, "0,");
  printf("Testing: K = 2 and L = 4...");
  r = microbench(2, 4, x, &dest, n);
  printf("dest = %f\n", dest);
  fprintf(file, "%f,", r/n);
  fprintf(file, "0,");
  printf("Testing: K = 2 and L = 6...");
  r = microbench(2, 6, x, &dest, n);
  printf("dest = %f\n", dest);
  fprintf(file, "%f\n", r/n);
  fprintf(file, "0,");
  fprintf(file, "0,");
  printf("Testing: K = 3 and L = 3...");
  r = microbench(3, 3, x, &dest, n);
  printf("dest = %f\n", dest);
  fprintf(file, "%f,", r/n);
  fprintf(file, "0,");
  fprintf(file, "0,");
  printf("Testing: K = 3 and L = 6...");
  r = microbench(3, 6, x, &dest, n);
  printf("dest = %f\n", dest);
  fprintf(file, "%f\n", r/n);
  fprintf(file, "0,");
  fprintf(file, "0,");
  fprintf(file, "0,");
  printf("Testing: K = 4 and L = 4...");
  r = microbench(4, 4, x, &dest, n);
  printf("dest = %f\n", dest);
  fprintf(file, "%f,", r/n);
  fprintf(file, "0,");
  fprintf(file, "0\n");
  fprintf(file, "0,");
  fprintf(file, "0,");
  fprintf(file, "0,");
  fprintf(file, "0,");
  printf("Testing: K = 5 and L = 5...");
  r = microbench(5, 5, x, &dest, n);
  printf("dest = %f\n", dest);
  fprintf(file, "%f,", r/n);
  fprintf(file, "0\n");
  fprintf(file, "0,");
  fprintf(file, "0,");
  fprintf(file, "0,");
  fprintf(file, "0,");
  fprintf(file, "0,");
  printf("Testing: K = 6 and L = 6...");
  r = microbench(6, 6, x, &dest, n);
  printf("dest = %f\n", dest);
  fprintf(file, "%f\n", r/n);
  
  free(x);
  
  return 0;
}
