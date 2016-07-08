#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpich/mpi.h>
int main(int argc,char **argv){
    srand((unsigned)time(NULL));
    int count = 1000;
    if(argc>1) count = atoi(argv[1]);

    int numprocs,myid,sum=0,tempSum=0;
    double start;clock_t start_t = clock();
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    if(myid==0) start = MPI_Wtime();
    int i;
    float x,y;
    for(i=myid;i<count;i+=numprocs){
        x = rand()/(RAND_MAX+1.0);
        y = rand()/(RAND_MAX+1.0);
        if(x*x+y*y<1)
            tempSum += 1;
    }
    MPI_Reduce(&tempSum,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(myid==0) {
        printf("mpi_wtime = %f",MPI_Wtime() - start);
        printf(" pi = %.16f clock()time = %f\n",4.0*sum/count,(double)(clock()-start_t)/1000);
    }
    MPI_Finalize();
    printf(" %d fin\n",myid);
    return 0;
}
