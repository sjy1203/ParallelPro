#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <time.h>

__global__ void vectorAdd(int *result,int N,int threadNum,int blockNum){
    double sum = 0.0,t = 1.0/N;
    int i = 0;
    const int tid = threadIdx.x;
    const int bid = blockIdx.x;
    for(i=bid*threadNum+tid;i<N;i+=threadNum*blockNum){
        sum += 1/((1+((i+1)*t+i*t)/2*((i+1)*t+i*t)/2));
    }
    result[bid*threadNum + tid] = 4*t*sum;
}
int main(int argc,char **argv){
    //initial
    int N = 50,threadNum = 4,blockNum = 4;
    if(argc>1) N = atoi(argv[1]);
    if(argc>2) threadNum = atoi(argv[2]);
    if(argc>3) blockNum = atoi(argv[3]);
    clock_t start;
    //allocate device mem
    double *cuda_result;
    start = clock();
    cudeMalloc((void*)&cuda_result,sizeof(double)*blockNum*threadNum);
    //cal
    vectorAdd<<<blockNum,threadNum,0>>>(cuda_result,N,threadNum,blockNum);
    //device to host
    int sum[threadNum*blockNum];
    cudaMemcpu(&sum,cuda_result,sizeof(int)*threadNum*blockNum,cudaMemcpyDeviceToHost);
    cudeFree(cuda_result);
    double final_sum = 0;
    int i ;
    for(i=0;i<threadNum*blockNum;i++){
        final_sum +=sum[i];
    }
    printf("divide:%d,threadNum:%d,blockNum:%d; pi = %.16f,time =
            %f\n",N,threadNum,blockNum,final_sum,clock()-start);
    return 0;
}
