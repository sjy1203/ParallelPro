#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omp.h>

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


typedef struct _boardwrap{
    char board[9][9];
}boardWrap;

void solver(char board[9][9],int x,int y,int *res,struct boardWrap* boardRes){
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
    *res = 1;
    memcpy(boardRes,*board,sizeof(struct boardWrap));
    return;
next:
    int tempRes[9];struct boardWrap tempWrap[9];
    #pragma omp parallel for firstprivate(borad)
    for(i=1;i<=9;i++){
        borad[idxX][idxY] = i;
        if(valid(borad,idxX,idxY)){
            solver(borad,idxX,idxY,tempRes+i-1,tempWrap+i-1);
        }
    }
    for (i=0; i<9; i++) {
        if(tempRes[i]==1){
            memcpy(boardRes,tempWrap+i,sizeof(struct boardWrap));
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
    int res;struct boardWrap boardW;
    solver(board,0,0,&res,&boardW);
    int m,k;
    for(m=0;m<9;m++){
        for(k=0;k<9;k++){
            printf("%d ",boradW.board[m][k]);
        }
        printf("\n");
    }
     return 0;
}
