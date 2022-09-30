#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <cmath>
//#include <omp.h>
//#define N 1073741824
using namespace std;

int main()
{
    timeval start,end;
    int i, j, k, bw=32, N=1073741824, M=N/bw;
    //double x, y, pi, sum=0;
    //do
    //int *x, *y;
    srand(42);
    int *x = (int *)malloc(N*sizeof(int));
    int *y = (int *)malloc(N*sizeof(int));
    for(i=0; i<N; i++)
    {
        x[i] = rand();
        //y[i] = rand();
    }

    // reorder the input
    for(i=0; i<N; i++)
    {
        j = i % bw * M + i / bw;
        y[i] = x[j];
    }

    //printf("%d %d %d %d\n", N, M, x[0], y[0]);
    gettimeofday(&start,NULL);
    for(k=0; k<10; k++)
    {

        #pragma omp simd
        for(i=bw; i<N; i+=bw)
        {
            //y[i] = ((x[i]<50)?x[i]:y[i]);
            //y[i] = x[i];
            //x[i] = max(x[i], x[i-1]-1);
            #pragma omp simd
            for(j=0; j<bw; j++)
            {
                y[i+j] = y[i-bw+j];
                //printf("break 48 %d %d\n", i, j);
            }
        }

        /*
        #pragma omp simd
        for(i=0; i<N; i+=M)
        {
            #pragma omp simd
            for(j=1; j<M; j++)
            {
                //y[M*k+i] = ((x[M*k+i]<y[M*k+i])?x[M*k+i]:y[M*k+i]);
                //x[M*k+i] = (x[M*k+i] > x[M*k+i-1]-1) ? x[M*k+i]: x[M*k+i-1]-1;
                //x[M*k+i] = max(x[M*k+i], x[M*k+i-1]-1);
                //x[i+k] = max(x[i+k], x[i+k-1]-1);
                x[i+j] = x[i+j-1]-1;

            }
        }
        */
    }
    gettimeofday(&end,NULL);
    //pi=sum*step;
    int pi=x[1024];
    int time_used=(1000000*(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec))/1000000;
    //int time_used=(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec)/1000;

    cout<<"time_used="<<time_used<<endl;
    cout<<"PI="<<pi<<endl;
    free(x);
    //free(y);
    return 1;

}
