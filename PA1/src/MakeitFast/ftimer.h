/* 
 * Higher level function timer routines 
 */
typedef void (*ftimer_test_funct)(void *); 

/* Estimate the running time of f(argp) using the Unix interval timer.
   Return the average of n runs */
double ftimer_itimer(ftimer_test_funct f, void *argp, int n);


/* Estimate the running time of f(argp) using gettimeofday 
   Return the average of n runs */
double ftimer_gettod(ftimer_test_funct f, void *argp, int n);


/*
 * Lower level interval timer routines
 */

/* Initializes the interval timer */
void init_etime(void);

/* Samples the interval timer */
double get_etime(void);

/* Routine that determines the clock rate */
double get_mhz(void);
