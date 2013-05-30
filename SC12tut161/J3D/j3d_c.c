// Jacobi 3D skeleton program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timing.h"

void dummy(double*, double*);

const double oos=1./6.;

void jacobi_line(double* d, const double* s,
                 const double* top, const double* bottom,
                 const double* front, const double* back, 
                 const double* f, int n) {
                 int i,start=1;
                 for(i=1; i<n-1; ++i) {
                     d[i] = oos*(f[i]*s[i]+s[i-1]+s[i+1]+top[i]+bottom[i]+front[i]+back[i]);
                 }
}

int main(int argc, char** argv) {

  double wct_start,wct_end,cput_start,cput_end,runtime,r;
  int iter,size,i,j,k,n,t0,t1,t;
  int ofs;
  double* phi[2];
  double *f;

  if(argc!=2) {
    printf("Usage: %s <size>\n",argv[0]);
    exit(1);
  }

  size = atoi(argv[1]);
  phi[0] = malloc((size_t)size*size*size*sizeof(double));
  phi[1] = malloc((size_t)size*size*size*sizeof(double));
  f = malloc((size_t)size*size*size*sizeof(double));

  t0=0; t1=1;

  /* initialize w/ random numbers */
  for(i=0; i<size; ++i) {
    for(j=0; j<size; ++j) {
      ofs = i*size*size + j*size;
      for(k=0; k<size; ++k) {
	f[ofs+k] = phi[t1][ofs+k] = phi[t0][ofs+k] = rand()/(double)RAND_MAX;
      }
    }
  }	  

  iter=1;
  runtime=0.0;
  while(runtime<0.5) {

  // time measurement
  timing(&wct_start, &cput_start);
  for(n=0; n<iter; n++) {
#pragma omp parallel for private(j,ofs) schedule(static)
    for(i=1; i<size-1; ++i) {
      for(j=1; j<size-1; ++j) {
        ofs = i*size*size + j*size;
        jacobi_line(&phi[t1][ofs],&phi[t0][ofs],&phi[t0][ofs+size],&phi[t0][ofs-size],
		    &phi[t0][ofs+size*size],&phi[t0][ofs-size*size],&f[ofs],size);
      }
    }
    dummy(phi[0],phi[1]);
    t=t0; t0=t1; t1=t;
  }	  
  

  timing(&wct_end, &cput_end);
  runtime = wct_end-wct_start;
  iter *= 2;
  }

  iter /= 2;

  printf("size: %d  time: %lf  iter: %d  MLUP/s: %lf\n",size,runtime,iter,(double)iter*(size-2)*(size-2)*(size-2)/runtime/1000000.);
  
  return 0;
}
