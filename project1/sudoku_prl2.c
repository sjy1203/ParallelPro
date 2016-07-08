#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omp.h>

typedef struct _boardwrap{
    char board[9][9];
}boardWrap;

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


void solver(char board[9][9],int x,int y,int *res,boardWrap* boardRes){
    int i,j;
    int idxX,idxY;
    int tempRes[9]={0};boardWrap tempWrap[9];
    for(i=x;i<9;i++)
        for(j=0;j<9;j++){
            if(board[i][j]==0){
                idxX = i;
                idxY = j;
                goto next;
            }
        }
    *res = 1;
    memcpy(*(boardRes->board),*board,sizeof(struct _boardwrap));
    return;
next:
    #pragma omp parallel for num_threads(9)
    for(i=1;i<=9;i++){
        printf("pid:%d start\n",omp_get_thread_num());
        board[idxX][idxY] = i;
        if(valid(board,idxX,idxY)){
            solver(board,idxX,idxY,tempRes+i-1,tempWrap+i-1);
        }
        board[idxX][idxY] = 0;
    }
    for (i=0; i<9; i++) {
        if(tempRes[i]==1){
            memcpy(*(boardRes->board),tempWrap+i,sizeof(struct _boardwrap));
            *res = 1;
            return ;
        }
    }
    *res = 0;
    return ;
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
    int res;boardWrap boardW;
    solver(borad,0,0,&res,&boardW);
    int m,k;
    for(m=0;m<9;m++){
        for(k=0;k<9;k++){
            printf("%d ",boardW.board[m][k]);
        }
        printf("\n");
    }
     return 0;
}
