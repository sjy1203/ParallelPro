#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int valid(char borad[9][9],int x,int  y){
    int i,j;
    //column
    for(i=0;i<9;i++){
        if(i!=x && borad[i][y]==borad[x][y])
            return 0;
    }
    //row
    for(j=0;j<9;j++){
        if(j!=y && borad[x][j]==borad[x][y])
        {
            return 0;
        }
    }
    //subbox
    int subX,subY;
    subX = x/3;
    subY = y/3;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if((i+3*subX)!=x && (j+3*subY)!=y &&borad[i+3*subX][j+3*subY] == borad[x][y])
                return 0;
        }
    }
    return 1;
}
int solver(char borad[9][9],int x,int y){
    int i,j;
    int idxX,idxY;
    for(i=x;i<9;i++)
        for(j=0;j<9;j++){
            if(borad[i][j]==0){
                idxX = i;
                idxY = j;
                goto next;
            }
        }
    return 1;
next:
    for(i=1;i<=9;i++){
        borad[idxX][idxY] = i;
        if(valid(borad,idxX,idxY)){
            if(solver(borad,idxX,idxY)){
                return 1;
            }
        }
        borad[idxX][idxY] = 0;
    }
    return 0;
}
int find_solution(char borad[9][9]){
    int i,j;
    int idxX,idxY;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(borad[i][j]==0)
            {
                idxX = i;
                idxY = j;
                goto next;
            }
        }
    }
next :
    for(i=1;i<=9;i++){
        borad[idxX][idxY] = i;
        if(valid(borad,idxX,idxY)){
            //next layer
            if(solver(borad,idxX,idxY)){
                return 1;
            }
        }
    }
    return 0;
}
int main(int argc,char **argv){
    char borad[9][9] = {
        0,0,7,6,0,0,9,0,0,
        0,6,0,0,0,0,0,5,0,
        0,0,5,0,3,7,0,0,1,
        0,8,9,3,0,0,0,0,5,
        4,0,0,0,1,0,0,0,7,
        3,0,0,0,0,4,8,2,0,
        5,0,0,9,7,0,6,0,0,
        0,4,0,0,0,0,0,7,0,
        0,0,3,0,0,6,5,0,0
    };
    clock_t start = clock();
    int res = find_solution(borad);
    printf("time = %.16f\n",(double)(clock()-start)/1000);
    int i,j;
    if(res==0){
        printf("no answ");
        return 1;
    }
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            printf("%d ",borad[i][j]);
        }
        printf("\n");
    }
    return 0;
}
