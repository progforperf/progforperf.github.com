/*****************************************************************************
 *
 * Copyright (c) 2006 Intel Corporation 
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 *
 * * Redistributions of source code must retain the above copyright notice, 
 *   this list of conditions and the following disclaimer. 
 * * Redistributions in binary form must reproduce the above copyright notice, 
 *   this list of conditions and the following disclaimer in the documentation 
 *   and/or other materials provided with the distribution. 
 * * Neither name of Intel Corporation nor the names of its contributors 
 *   may be used to endorse or promote products derived from this software 
 *   without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#define NITERS 1000000


int inp[3000];
int glob1[1000];

int check_3odd(int *in_p, int *out_p)
{
    int i;
    int j;
    int n_ones = 0;

    for (i = 0, j = 0; i < 1000; i++, j += 3 ) {
        int t1 = in_p[j] & 1;
        int t2 = in_p[j+1] & 1;
        int t3 = in_p[j+2] & 1;
        int t4 = 0;
        
#ifdef FAST
        if ( (t1 | t2 | t3 ) == 0) {
            t4 = 1;
        }
#else
        if ( t1 == 0 && t2 == 0 && t3 == 0) {
            t4 = 1;
        }
#endif
        out_p[i] = t4;
        n_ones += t4;
    }

    return n_ones;
}

main()
{
    int sum = 0;
    int j;

    srand(20561);

    for (j = 0; j < 3000; j++) {
        inp[j] = rand();
    }

    for (j = 0; j < NITERS; j++) {
        sum += check_3odd(inp, glob1);
    }

    printf ("%d\n", sum);
}
