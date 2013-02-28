/*
gcc -I/usr/apps/tools/papi/4.2.0-forge/include -c -std=c99 papi.c
gcc -o papi papi.o -L/usr/apps/tools/papi/4.2.0-forge/lib -lpapi
gcc -I/usr/apps/tools/papi/4.2.0-forge/include -c -std=c99 mmm_sample.c
gcc -o mmm_sample mmm_sample.o -L/usr/apps/tools/papi/4.2.0-forge/lib -lpapi
*/


#include <papi.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv)
{

   int ec = PAPI_library_init(PAPI_VER_CURRENT);
   if (ec != PAPI_VER_CURRENT && ec > 0) {
      fprintf(stderr,"PAPI library version mismatch!\n");
      exit(1);
   }

   if (ec < 0){
	fprintf(stderr, "PAPI init error %d: %s\n",ec,PAPI_strerror(ec));
      exit(1);
   }

   ec = PAPI_is_initialized();

   if (ec != PAPI_LOW_LEVEL_INITED){
      fprintf(stderr,"Low Level not invited\n");
   }

    int EventSet = PAPI_NULL;
    int errcode = PAPI_create_eventset(&EventSet);
    if (errcode != PAPI_OK) {
        fprintf(stderr,"Couldn't create event set\n");
	fprintf(stderr, "PAPI error %d: %s\n",errcode,PAPI_strerror(errcode));
        exit(-1);
    }

    const int NUMEVENTS  = 3;
    int events[] = {PAPI_TOT_INS, PAPI_FP_INS, PAPI_L2_TCM, PAPI_TOT_CYC};
    errcode = PAPI_add_events(EventSet, events, NUMEVENTS);
    if (errcode != PAPI_OK) {
       fprintf(stderr,"Couldn't add events to event set\n");
       fprintf(stderr, "PAPI error %d: %s\n",errcode,PAPI_strerror(errcode));
       exit(-1);
    }

    int N =  atoi(*++argv);
    printf("N = %d\n",N);
    double *x = (double *) malloc(N*sizeof(double));
    assert(x);
    double *y = (double *) malloc(N*sizeof(double));
    assert(y);
    for (int i=0; i< N; i++){
	x[i] = i;
    }
    long long values[NUMEVENTS];


    // Warm up the counters
    errcode  = PAPI_start(EventSet);
    PAPI_stop(EventSet, values);

    errcode  = PAPI_start(EventSet);
    if (errcode != PAPI_OK) {
        fprintf(stderr,"Couldn't start the counters\n");
	fprintf(stderr, "PAPI error %d: %s\n",errcode,PAPI_strerror(errcode));
        exit(-1);
    }


// Compute
   for (int i=0; i< N; i++)
      y[i] = 0.5*x[i];

    PAPI_stop(EventSet, values);
    printf("%f\n",x[N/2]);
//    events[] = {PAPI_TOT_INS, PAPI_FP_INS, PAPI_L2_TCM, PAPI_TOT_CYC};
//    printf("L2 DCA: %lld\n", values[0]);
    printf("Tot ins: %lld, fp ins: %lld Tot cycles: %lld\n", values[0], values[1], values[2]);
//    printf("Tot ins: %lld, fp ins: %lld Tot cycles: %lld L1_DCM: %lld\n", values[0], values[1], values[2], values[3]);
//    printf("Tot L2 misses: %lld, cyc: %lld\n", values[2], values[3]);
//    printf("Tot L2D acc: %lld, hits: %lld, misses: %lld\n", values[5], values[6], values[7]);
//    printf("Tot L2I acc: %lld, misses: %lld\n", values[8], values[9]);

    return 0;
}
