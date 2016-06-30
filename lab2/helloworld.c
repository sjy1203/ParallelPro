#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(){
    omp_set_num_threads(5);
    #pragma omp parallel
    {
        printf("hello world!");
    }
}
