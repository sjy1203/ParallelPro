#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
typedef struct _thread_data_t{
    int tid;
    int i;
}thread_data_t;
double sum,t;
int N,thread_num;
pthread_mutex_t lock_sum;

void *func(void *arg){
    thread_data_t *data = (thread_data_t *)arg;
    int i;
    double* tempSum = (double*)malloc(sizeof(double));
    *tempSum = 0;
    for(i=data->tid;i<N;i+=thread_num){
        *tempSum +=  1/(1+((i+1)*t+i*t)/2*((i+1)*t+i*t)/2);
    }
    
    //pthread_mutex_lock(&lock_sum);
    //pthread_mutex_unlock(&lock_sum);

    printf("running tid:%d,i:%d; tempSum = %.16f\n",data->tid,data->i,4*t*(*tempSum));
    pthread_exit(tempSum);
}
int main(int argc, char **argv){
     //initial params
    N = 50;thread_num = 4;
    clock_t start,end;
    if(argc>1){
        N = atoi(argv[1]);
    }
    if(argc>2){
        thread_num = atoi(argv[2]);
    }
    //initial thread and mux_lock
    pthread_t thread[thread_num];
    thread_data_t data[thread_num];
    //cal
    int i = 0,rc;t = 1.0/N;
    start = clock();
    for(i=0;i<thread_num;i++){
        //int idx = i%thread_num;
        data[i].tid = i;
        data[i].i = i;
        if((rc = pthread_create(&thread[i],NULL,func,data+i))){
            fprintf(stderr,"error: pthread_create,rc:%d\n",rc);
            return -1;
        }
    }

    for(i=0;i<thread_num;i++){
        double* temp;
        pthread_join(thread[i],(void*)(&temp));
        sum += *temp;
        printf("pid:%d return tempSum=%.16f finish\n",i,4*t*(*temp));
    }

    //display
    end = clock();
    printf("pi = %.16f,time = %f\n",4*sum*t,(double)(end-start)/1000);
    return 0;
}
