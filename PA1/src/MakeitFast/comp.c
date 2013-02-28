/*
 * comp.c - contains the function superslow that you need to optimize
 *
 *
 */

#include <math.h>
#include <stdio.h>
#include "comp.h"
#include "perf.h"

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif


/* f(x, i, j) multiplies or divides by a sine expression depending
   on i + j being odd or even
*/
double f(double x, int i, int j)
{
    if((i + j) & 0x1)
        return x / (1 + sin(M_PI/(i+1)));
    else
        return x * sin(M_PI/(i+1));
}

/* This is the function you need to optimize. It takes one
   square matrix as input
*/
void superslow(smat_t *a)
{
    int i, j;
    double x,x2;

    // i is the column of a we're computing right now
    for(i = 0; i < a->n; i++)
    {
        // j is the row of a we're computing right now
        for(j = 0; j < a->n; j++)
        {            
                // First, compute f(A) for the element of a in question
			x = get_elt(a, i, j);
                x = f(x, i, j);
                
                // Add this to the value of a we're computing and store it
                x2 = get_elt(a, i, j);
			x = x * x2;
                set_elt(a, i, j, x);
            
        }
    }
}


/* 
 * Called by the driver to register your functions
 * Use add_function(func, description) to add your own functions
 */
void register_functions()
{
    // Registers comp_superslow with the driver
    add_function(&superslow, "superslow: original function");
	
	//Add your functions here
	//add_function(&superslow2, "superslow: Optimization X");
	
	
}
