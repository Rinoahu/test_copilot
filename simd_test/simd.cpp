#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <cmath>
//#include <omp.h>
#define N 1000000000
using namespace std;

int main()
{
    timeval start,end;
    int i;
    double x, y, pi, sum=0;
    double step=1.0/N;
    gettimeofday(&start,NULL);
    for(int j=0; j<10; j++)
    {
        sum=j;
        #pragma omp simd reduction(+:sum) private(x)
        for(i=0;i<N;i++)
        {
            x=(i+0.5)*step;
            //y=(rand()>.5)?0:1;
            y=(i%2>0)?0:1;
            sum+=4.0/(1.0+x*x);
        }
    }
    gettimeofday(&end,NULL);
    pi=sum*step;
    int time_used=1000000*(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec);
    cout<<"time_used="<<time_used<<endl;
    cout<<"PI="<<pi<<endl;
    return 1;
}
