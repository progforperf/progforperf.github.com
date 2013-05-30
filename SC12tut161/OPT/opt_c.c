#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "timing.h"

#define N 2000

void dummy(double*);

int main() {
  double mat[N][N], s[N][N], val, vv;
  int i, j,R,iter,v[N];
  double wct_start,wct_end,cput_start,cput_end,runtime;

  for(i=0; i<N ; ++i) {
    v[i] = rand();
    for(j=0; j<N; ++j)
      mat[i][j] = s[i][j] = rand()/RAND_MAX;
  }

  R=1;

  do {
    timing(&wct_start, &cput_start);

    for(iter=0; iter<R; ++iter) {
      
      for(i=0; i<N ; ++i) {
	for(j=0; j<N; ++j) {
	  val = (double)(v[i] % 256);
	  mat[j][i] = s[j][i]*(sin(val)*sin(val)-cos(val)*cos(val));
	}
      }
      if(mat[2][2]<-1000.) dummy(mat[2]);
    }
    
    timing(&wct_end, &cput_end);
    runtime = wct_end-wct_start;
    R += R;
  } while(runtime<0.2);
  
  R=R/2;
    
  printf("Performance: %lf MIt/s\n",(double)R*N*N/runtime/1000000.);

  
  return 0;
}
