#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
double sum;
int main(int argc, char **argv){
    int N = 50;
    clock_t start,end;
    if(argc>1){
        N = atoi(argv[1]);
    }

    int i = 0;double t = 1.0/N;
    start = clock();
    for(;i<N;i++){
        sum += 1/(1+pow(((i+1)*t+i*t)/2,2));
    }
    end = clock();
    printf("pi = %f,time = %f\n",4*sum*t,(double)(end-start)/1000);
    return 0;
}
