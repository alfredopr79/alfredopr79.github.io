/*Create Permutation and Combination of 2^n binary values*/
//My Profile: http://linkedin.com/in/alfredopea
//Alfredo Peña Ramos /PHD Student

#include <stdio.h>
#include <time.h>
#include <math.h>

int m,n;

void CreatePermutations(int i);

int main(int args,char** arg){
    
    long start, end; 
    int i,j;
    
    printf ("Input n Value where 2^n:");
    scanf("%i",&m);

    n = pow(2,m);   //Calculate Permutations

    start = clock();

    //Create Population
    for (i = 0; i < n; i++){
        CreatePermutations(i);
        printf("\n");
    }
    
    end = clock();
    double time = end - start;

    printf("Exec Time: %f\n",(time)/CLOCKS_PER_SEC);
    system("pause");
}
//Population using binary values of 2^n combinations
void CreatePermutations(int i){
    int j;
    int array[m];
    
    for (int j = m-1; j >= 0; j--){
         //array[j]=(i / (1 << j)) % 2;
         printf("%i",array[j]=(i / (1 << j)) % 2);
    }
}