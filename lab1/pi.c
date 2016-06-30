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
pthread_mutex_t lock_sum;
void *func(void *arg){
    thread_data_t *data = (thread_data_t *)arg;
    printf("running tid:%d,i:%d\n",data->tid,data->i);
    double temp = 1/(1+((data->i+1)*t+data->i*t)/2*((data->i+1)*t+data->i*t)/2);
    pthread_mutex_lock(&lock_sum);
        sum += temp;
    pthread_mutex_unlock(&lock_sum);

    pthread_exit(NULL);
}
int main(int argc, char **argv){
    //initial params
    int N = 50;
    clock_t start,end;
    if(argc>1){
        N = atoi(argv[1]);
    }
    //initial thread and mux_lock
    pthread_t thread[N];
    pthread_mutex_init(&lock_sum,NULL);
    thread_data_t data[N];
    //cal
    int i = 0,rc;t = 1.0/N;
    start = clock();
    for(i=0;i<N;i++){
        //int idx = i%thread_num;
        data[i].tid = i;
        data[i].i = i;
        if((rc = pthread_create(&thread[i],NULL,func,data+i))){
            fprintf(stderr,"error: pthread_create,rc:%d\n",rc);
            return -1;
        }
    }

    for(i=0;i<N;i++){
        pthread_join(thread[i],NULL);
    }

    //display
    end = clock();
    printf("pi = %f,time = %f\n",4*sum*t,(double)(end-start)/1000);
    return 0;
}
