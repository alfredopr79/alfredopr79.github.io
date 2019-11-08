#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, j, k;
    i = 10;
    j = 1;
    k = 5;

    if (i > j && i > k)
    {
        printf("i es mayor que j y k \n");
        if (i == 10)
        {
          printf("el valor de i es igual a: %d \n",i);  
        }
    }
    
  system("pause");
}