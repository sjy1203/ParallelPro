#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

float pi_cal(int count,int thread_num){
    int i=0;
    float x,y;
    int inCount = 0;
    double start = omp_get_wtime();
#pragma omp parallel for num_threads(thread_num) reduction(+:inCount)
    for(i=0;i<count;i++){
        x = rand()/(RAND_MAX+1.0);
        y = rand()/(RAND_MAX+1.0);
        if(x*x+y*y<1.0){
            inCount = inCount + 1;
        }
    }
    printf("omp time = %f ",omp_get_wtime() - start);
    return inCount*4.0/count;
}
int main(int argc,char **argv){
    srand((unsigned)time(NULL));
    int count = 1000,thread_num = 2;
    if(argc>1) count = atoi(argv[1]);
    if(argc>2) thread_num = atoi(argv[2]);
    clock_t start = clock();
    printf("pi = %.16f",pi_cal(count,thread_num));
    printf(" clock()time = %f\n",(double)(clock() - start)/1000);
    return 0;
}
