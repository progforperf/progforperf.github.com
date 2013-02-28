#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n 2000
#define m 3000

void main()
{
  double **a, **b, c, norm;
  int i, j, l;
  
  a = (double**)malloc(n*sizeof(double*));
  b = (double**)malloc(n*sizeof(double*));

  for(i=0; i<n; i++)
    {
      a[i] = (double*)malloc(m*sizeof(double));
      for(j=0; j<n; j++) a[i][j] = drand48();
    }
    
  for(i=0; i<n; i++) b[i] = (double*)calloc(m, sizeof(double));
 
  c = 13.0;

  for(l=1; l<=30; l++)
    {
      i=0;
      
      while(i<n)
	{
	  j=0;

	  while(j<m)
	    {
	      if(j%2==0)
		{
		  b[i][j] = c*b[i][j]+a[i][j];
		} else {
		  b[i][j] = c*b[i][j]-a[i][j];
		}

	      j++;
	    }

	  i++;
	}
    }

  norm = 0.0;

  for(i=0; i<n; i++)
    for(j=0; j<m; j++)
      norm = norm + fabs(b[i][j]*b[i][j]);
 
  printf("norm: %10.4e    Value: %10.4e\n",norm, b[10][10]);
}
