#include <stdio.h>

#define N 4

int main(void){
    FILE *fp;
    
    fp = fopen("table.txt", "w");
    if(!fp){
        puts("File open failure");
        return -1;
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fprintf(fp, "(%d %d)", i, j);
        }
        fputc('\n', fp);
    }

    fclose(fp);
    return 0;
}