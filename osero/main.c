// TODO コンパイルの時にちゃんと"-lm"付けろよ
#include <stdio.h>
#include <math.h>

#define N 4
#define BLACK 1
#define WHITE -1
#define NOTHING 0
#define CANPUT 2

// set q table 64*64 each in q value

double c = sqrt(2.0);
int bord[N][N] = {{0}};
int can_put_bord[N][N] = {{0}};
int skip=0;

double ucb1(int n, int w, double nn){
    return w/n+c*sqrt(log(nn)/n);
}

/* double selection(){ */
/*     return q+ucb; */
/* } */

void print(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(bord[i][j]==0) printf("□  ");
            else printf("%s ", bord[i][j]==BLACK ? "● " : "○ ");
        }
        puts("");
    }
}

int canPut(int x, int y, int color){
    if(bord[x][y]!=NOTHING) return 0;
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            if(0<=x+i && x+i<N && 0<=y+j && y+j<N && bord[x+i][y+j]==-1*color){
                for(int k=x+i*2, l=y+j*2; 0<=k && k<N && 0<=l && l<N; k+=i,l+=j){
                    if(bord[k][l]==color) return 2;
                }
            }
        }
    }
    return 0;
}

int turnOver(int x, int y, int color){
    if(can_put_bord[x][y]!=2){
        puts("ERROR:cant put here");
        return -1*color;
    }else{
        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                if(0<=x+i && x+i<N && 0<=y+j && y+j<N && bord[x+i][y+j]==-1*color){
                    for(int k=x+i*2, l=y+j*2; 0<=k && k<N && 0<=l && l<N && bord[k][l]!=NOTHING; k+=i,l+=j){
                        if(bord[k][l]==color){
                            while(bord[k-i][l-j]==-1*color){
                                bord[k-i][l-j]=color;
                                k-=i;
                                l-=j;
                            }
                            bord[x][y]=color;
                            break;
                        }
                    }
                }
            }
        }
        return color;
    }
}

int game(int color){
    if(skip==0) skip=1;
    else skip=2;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            can_put_bord[i][j] = canPut(i,j,color);
            if(can_put_bord[i][j]==2) skip=0;
            printf("%d ", can_put_bord[i][j]);
        }
        puts("");
    }
    if(skip!=2){
        if(skip==1){
            puts("skip!");
            game(-1*color);
        }else{
            printf("%sの番\n", color == BLACK ? "黒" : "白");
            print();
            puts("Input x y");
            int x,y;
            scanf("%d", &x);
            scanf("%d", &y);
            color = turnOver(x,y,color);
            game(-1*color);
        }
    }else{
        int black=0,white=0;
        print();
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(bord[i][j]==BLACK) black++;
                else if(bord[i][j]==WHITE) white++;
            }
        }
        printf("BLACK:%d, WHITE:%d, ", black, white);
        if(black==white) puts("Draw.");
        else printf("%s Win.\n", black>white?"BLACK":"WHITE");
        return 0;
    }
}

int main(void){
    int color;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++) bord[N/2-i][N/2-j] = i==j ? BLACK : WHITE;
    }
    puts("どっち 1:BLACK, -1:WHITE");
    scanf("%d", &color);
    game(color);
    return 0;
}
