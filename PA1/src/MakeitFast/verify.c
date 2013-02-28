/*
 * verify.c - runs two functions on the same inputs and checks
 *   that their outpus are equal.
 */
#include <math.h>
#include "verify.h"
#include "smat.h"
#include "verfunc.h"

#define EPS (1e-8)





/*
 * Checks whether or not the results of two computation functions are the
 * same (within a tolerance defined by EPS, to deal with rounding issues
 */
int check_valid(comp_func checkFunc, int chk_n)
{
    int i;
    
    int valid = 1;
    smat_t *a1 = random_SMat(chk_n);
    
    double *aMat1 = a1->mat;
    
    smat_t *a2 = copy_SMat(a1);    
    
    double *aMat2 = a2->mat;
    
    verfunc(a1 );
    checkFunc(a2);
    
    for(i = 0; i < chk_n * chk_n; i++)
    {
      if (isnan(aMat2[i])) {
		valid = 0;
		break; 
      }
	  
      if (! (fabs(aMat1[i] - aMat2[i]) < EPS)) {
	valid = 0;
	break;
      }
    }

    free_SMat(a1);
    free_SMat(a2);    
    return valid;
}


