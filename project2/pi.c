#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float pi_cal(int count){
    int i=0;
    float x,y;
    int inCount = 0;
    for(i=0;i<count;i++){
        x = rand()/(RAND_MAX+1.0);
        y = rand()/(RAND_MAX+1.0);
        if(x*x+y*y<1.0){
            inCount++;
        }
    }
    return inCount*4.0/count;
}
int main(int argc,char **argv){
    srand((unsigned)time(NULL));
    int count = 1000;
    if(argc>1) count = atoi(argv[1]);
    clock_t start = clock();
    printf("pi = %.16f",pi_cal(count));
    printf(" clock()time = %f\n",(double)(clock() - start)/1000);
    return 0;
}
