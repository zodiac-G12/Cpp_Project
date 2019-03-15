/*/////////////////////////////////////////////////////////////////////////////

    This is a program of error detection and error correction for input message
     in hamming code.

    Please enter a number of '0' or '1' as a space delimiter and execute. 
    (ex) 「$ 0 0 0 1 0 0 0\n」

*//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h> // atoi() function

#define MAX 10 // Hamming Code MAX 
#define M 3 // Some Integer -> (K,N) is determined
#define K 4 // Message Length
#define N M+K // Block Length


int c[MAX][MAX] = {{0}}; // Hamming Code(C)
int i_m[M][M] = {{0}}; // Identity Matrix(I_m)
int y[N] = {0}; // Receive Message
int syndrome[M] = {0}; // Syndrome(if(zero matrix) => clear; else => error)
int i, j, flag; // Counter

int p[3][4] =  {{1, 1, 1, 0}, // Partity Check Matrix
                {0, 1, 1, 1}, // (Information Check Bits Associated Matrix)
                {1, 1, 0, 1}};


/* Making Two Identity Matrix(i_m and i_k) */

void make_i_mat(void){
    for(i = 0; i < M; i++) for(j = 0; j < M; j++){if(i == j) i_m[i][j] = 1;}
}


/* Making Hamming Code(n,k) */

void make_h_code(void){
    for(i = 0; i < M; i++){for(j = 0; j < K; j++) c[i][j] = p[i][j];}
    for(i = 0; i < M; i++){for(j = K; j < N; j++) c[i][j] = i_m[i][j-K];}
    printf("Hamming Code C:\n");
    for(i = 0; i < M; i++){for(j = 0; j < N; j++){printf("%d ",c[i][j]);}printf("\n");}
}


/* Error Detection */

int error_detection(void){
    for(i = 0; i < M; i++){
        for(j = 0; j < N; j++) syndrome[i] ^= y[j] ^ c[M - 1 - i][j];
    }
    for(i = 0; i < M && syndrome[i] == 0; i++);
    if(i != M){printf("Error.\n"); return 1;}
    else{printf("Clear.\n"); return 0;}
}


/* Error Correction */

void error_correction(){
    for(i = 0, flag = 0; i < N && flag != M; i++){
        for(j = 0; j < M; j++){if(c[j][i] == y[j]) flag++;}
    } printf("The %d bit is in correct.\n", i);
    for(j = 0; j < N; j++){
        if(j == i - 1) y[j] = ~y[j] & 1;
        printf("%d ", y[j]);
    } printf("\n");
}


/* Main Function */

int main(void){
    char buf[100];
    long tmp;

    make_i_mat();
    make_h_code();
   
    printf("Please input Message.\n");
    fgets(buf, 100, stdin);
    for(i = 0, j = 0; i < 98 && j < N; i++){
        if(buf[i] != '0' && buf[i] != '1' && buf[i] != ' '){printf("Input Error.\n"); return -1;}
        else if(buf[i] == '0' || buf[i] == '1'){
            y[j++] = atoi(&buf[i]);
            if(buf[i+1] != ' ' && buf[i+1] != '\n'){printf("Input Error.\n"); return -1;}
        }
    }

    if(error_detection() == 1) error_correction();

    return 0;
}
