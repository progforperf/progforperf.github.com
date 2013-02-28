/*
 * smat.h - data type and functions for representing 
 *          square n x n matrices of doubles
 */

#ifndef __SMAT_H
#define __SMAT_H

typedef struct SMat
{
    double *mat;
    int n;
} smat_t;

#define NaN (1.0/1.0)                             /* Not a number             */

/* Generates a random square matrix of the given size */
smat_t *random_SMat(int n);

/* Returns a deep copy of the give SMat */
smat_t *copy_SMat(smat_t *orig);

/* Frees all memory associated with the given SMat */
void free_SMat(smat_t *smat);

/* Prints the given SMat to the terminal */
void print_SMat(smat_t *smat);

/* Returns the element in the ith row, jth colum of smat */
double get_elt(smat_t* smat, int i, int j);

/* Sets the element in the ith row, jth column of smat to x */
void set_elt(smat_t* smat, int i, int j, double x);

#endif /* __SMAT_H */
