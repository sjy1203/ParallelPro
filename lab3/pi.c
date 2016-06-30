#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int main(int argc,char **argv){
    int N=50;
    if(argc>1){
        N = atoi(argv[1]);
    }
    double sum,tempPi;
    double t = 1.0/N;
    int myid,numprocs,i;
    double start,end;
    //mpi
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    if(myid==0){
        start = MPI_Wtime();
    }
    tempPi = 0.0;
    for(i = myid;i<N;i += numprocs){
        tempPi = tempPi + 1/((1+((i+1)*t+i*t)/2*((i+1)*t+i*t)/2));
    }
    MPI_Reduce(&tempPi,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    if(myid==0){
        end = MPI_Wtime();
        printf("time = %f,pi = %.16f\n",end-start,4*t*sum);
    }else{
        printf("tempPi=%.16f,pid:%d finish\n",4*t*tempPi,myid);
    }
    MPI_Finalize();
    return 0;
}
