#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
int main(int argc,char **argv){
    //initial params
    int thread_num = 2*omp_get_num_procs(); //default 2 times of CPU
    int N = 50;//iterate times
    if(argc>1){
        N = atoi(argv[1]);
    }
    if(argc>2){
        thread_num = atoi(argv[2]);
    }
    double res[N];int i;
    double t = 1.0/N;
    clock_t start,end;
   
    double omp_start,omp_end;
    start = clock();
    omp_start = omp_get_wtime();
    //cal
    #pragma omp parallel for num_threads(thread_num)
        for(i=0;i<N;i++){
            res[i] = 1/(1+((i+1)*t+i*t)/2*((i+1)*t+i*t)/2);
            printf("Thread id:%d,i:%d\n",omp_get_thread_num(),i);
        }
    double sum = 0;
    for(i=0;i<N;i++){
        sum+=res[i];
    }
    end = clock();
    omp_end = omp_get_wtime();
    printf("res = %f\n;alltime = %f;real time = %f",4*t*sum,(double)(end-start)/1000,omp_end - omp_start);
    return 0;
}


