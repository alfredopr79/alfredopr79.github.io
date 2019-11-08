#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, j, k;
    i = 20;
    j = 10;
    k = 5;

    if (i > j && i > k)
    {
        printf("i es mayor que j y k");
    }
    else{
        if (k > j && j > i)
        {
            printf("k es mayor que j e i \n");
        }
        else{
            if (j > i && j > k){
                printf("j es mayor que k e i \n");
            }
            else{
                printf("i,j,k son iguales \n");
            }
        }
    }
    
  system("pause");
}