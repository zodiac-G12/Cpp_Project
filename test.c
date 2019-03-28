#include <stdio.h>

int main(void){
    int i;
    int l;

    scanf("%d", &l);
    int array[l];

    for(i = 0; i < l; i++) array[i] = 0;

    for(i = 0; i < l; i++) printf("%d ", array[i]);
    puts("");

    return 0;
}
