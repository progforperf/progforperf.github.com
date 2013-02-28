/*
 * smat.c - Data type and functions for square n x n matrices
 *
 * Implements basic constructors, descructor, printer, and accessor
 *   functions for smat_t.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "smat.h"

/* returns a random SMat with entries in [-1, 1] */
smat_t *random_SMat(int n)
{
    int i, j;
    smat_t *smat = malloc(sizeof(smat_t));

    double *mat = malloc(n * n * sizeof(double));

    for(i=0; i < n; i++)
    {
        for(j=0; j < n; j++)
        {
            mat[i * n + j] = (drand48() * 2) - 1;	    
        }
    }

    smat->mat = mat;
    smat->n = n;

    return smat;
}

/* Returns a deep copy of the give SMat */
smat_t *copy_SMat(smat_t *orig)
{
    int n = orig->n;
    size_t matSize = n * n * sizeof(double);
    smat_t *new = malloc(sizeof(smat_t));
    
    new->n = orig->n;
    
    new->mat = malloc(matSize);

    memcpy(new->mat, orig->mat, matSize);

    return new;
}

/* Frees all memory associated with the given SMat */
void free_SMat(smat_t *smat)
{
    free(smat->mat);
    free(smat);
}

/* Prints the given SMat to the terminal */
void print_SMat(smat_t *smat)
{
    int i, j;
    int n = smat->n;
    double *mat = smat->mat;
    
    printf("%d x %d Matrix:\n\n", n, n);

    for(i=0; i < n; i++)
    {
        for(j=0; j < n; j++)
        {
            printf("%1.3f\t", mat[i * n + j]);
        }
        
        printf("\n");
    }
}

/* Returns the element in the ith row, jth colum of smat */
double get_elt(smat_t* smat, int i, int j)
{
    double *mat = smat->mat;
    int n = smat->n;

    if(i >= n || i < 0 || j >= n || j < 0)
        return NaN;

    return mat[i * n + j];
}

/* Sets the element in the ith row, jth column of smat to x */
void set_elt(smat_t* smat, int i, int j, double x)
{
    double *mat = smat->mat;
    int n = smat->n;
    
    if(i >= 0 && i < n && j >= 0 && j < n)
        mat[i * n + j] = x;
    else
        printf("Set failed\n");
}
