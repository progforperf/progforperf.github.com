/*
 * perf.h - function for measuring the performance of an function.
 *   Result is in MFLOPs
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ftimer.h"

#include "comp.h"
#include "perf.h"
#include "verify.h"

#define TEST_RUNS  100
#define TEST_SIZE1 300
#define TEST_SIZE2 600

static int test_sizes[] = {TEST_SIZE1, TEST_SIZE2};
static int test_iters[] = {200, TEST_RUNS};

#define NUM_TESTS (sizeof(test_sizes) / sizeof(int))

#define MIN(x,y) (((x) < (y)) ? (x) : (y))


double comp_ftimer_itimer(comp_func f, smat_t *a, int n);
double get_perf_score(comp_func f, int size, int verbosity, int n);
double perf_test(comp_func f, char *desc, int verbosity);
void invalid_msg(int size, char *desc, int verbosity);

/* Global vars, used to keep track of student functions */
comp_func userFuncs[MAX_FUNCS];
char *funcNames[MAX_FUNCS];
int numFuncs = 0;

/*
 * Main driver routine - calls register_funcs to get student functions, then 
 * tests all functions registered, and reports the best performance
 */
int main(int argc, char **argv)
{
    double perf;
    double maxPerf = 0;
    int i;
    int maxInd = 0;
    int verbosity = 2;
    int score;
    int autograded = 0;
    
   
    register_functions();

    if(numFuncs == 0)
    {
        printf("No functions registered - nothing for driver to do\n");
        printf("Register functions by calling register_func(f, name)\n");
        printf("in register_funcs()\n");

        return 0;
    }
    
    for(i = 0; i < numFuncs; i++)
    {
        perf = perf_test(userFuncs[i], funcNames[i], verbosity);

        if(perf > maxPerf)
        {
            maxInd = i;
            maxPerf = perf;
        }
    }

    if(maxPerf > 0)
        printf("Best: %s\nPerf: %.3f MFLOPs\n", funcNames[maxInd], maxPerf);
    else
        printf("No valid functions registered\n"); 

    

    
    return 0;    
}

/*
 * Registers a user function to be tested by the driver program. Registers a
 * string description of the function as well
 */
void add_function(comp_func f, char *name)
{
    if(numFuncs >= MAX_FUNCS)
    {
        printf("Couldn't register %s, too many functions registered (Max: %d)",
                    name, MAX_FUNCS);
        return;
    }

    userFuncs[numFuncs] = f;
    funcNames[numFuncs] = name;

    numFuncs++;
}

/* 
 * Checks the given function for validity. If valid, then computes and 
 * reports and returns its performance in MFLOPs 
 * verbosity values <= 0 will suppress output, except for invalid result
 * warnings
 */
double perf_test(comp_func f, char *desc, int verbosity)
{
    double results_sum, avg;
    static int first = 1;
    int test_size, test_iter;
    int i;
    
    //Seed the random number generator once and only once
    if(first)
    {
        srand48(time(0));
        first = 0;
    }
    
    if(verbosity > 0)
    {
        printf("%s:", desc);
        if(verbosity > 1)
            printf("\n");
    }
    
    results_sum = 0;
    for (i = 0; i < NUM_TESTS; i++) {
      test_size = test_sizes[i];
      test_iter = test_iters[i];
      if (! check_valid(f, test_size)) {
        invalid_msg(test_size, desc, verbosity);
        return 0;
      }
      results_sum += get_perf_score(f, test_size, verbosity, test_iter);
    }
    avg = results_sum / NUM_TESTS;
        
    if(verbosity > 0)
    {
        if(verbosity > 1)
            printf("Average:");
        printf(" %.3f MFLOPs\n\n", avg);
    }
            
    return avg; 
}

/* Prints a message when a function fails validation */
void invalid_msg(int size, char *desc, int verbosity)
{
    if(verbosity > 0)
        printf("Invalid result for size %d\n\n", size);
    else
        printf("Invalid result for %s (size %d)\n", desc, size);
}

/******************************************************************************/

/*
 * ftimer_itimer - Use the interval timer to estimate the running time
 * of f(argp). Return the average of n runs.
 * (Adapted to work with 3 argument matrix funcs)
 */
double comp_ftimer_itimer(comp_func f, smat_t *ax, int n)
{
    double start, tmeas;
    int i;

    init_etime();
    start = get_etime();
    for (i = 0; i < n; i++)
        f(ax);
    tmeas = get_etime() - start;
    return tmeas / n;
}

/*
 * Gets the performance of a given function for a matrice of a given size
 * Result is in MFLOPs
 * verbosity values <= 1 will suppress printing of results
 */
double get_perf_score(comp_func f, int size, int verbosity, int n)
{
    smat_t *a;
    double result, mflops;
    
    a = random_SMat(size);

    
    result = comp_ftimer_itimer(f, a,n);
    mflops = (2*pow(size, 2) )/(result * 1e6);

    if(verbosity > 1)
        printf("Size %d: %.3f MFLOPs\n", size, mflops);
    
    free_SMat(a);


    return mflops;
}
