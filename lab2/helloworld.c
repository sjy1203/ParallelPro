#include <stdio.h>
#include <stdlib.h>

int main(){
    #pragma omp parallel
    {
        printf("hello world!");
    }
}
