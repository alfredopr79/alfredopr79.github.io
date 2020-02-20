/*Create Permutation and Combination of 2^n binary values*/
//My Profile: http://linkedin.com/in/alfredopea
//Alfredo Peña Ramos /PHD Student

#include <stdio.h>
#include <time.h>
#include <math.h>

int n;
int m;

int** DynamicMemory2D(int n, int m);
int** population;
void CreatePermutations(int i);

int main(int args,char** arg){
    
    long start, end; 
    int i,j;
    
    printf ("Input n Value where 2^n:");
    scanf("%i",&m);

    n = pow(2,m);   //Calculate Array Rows
    
    //Allocate Dynamic Memory 2D Arrays.
    population = DynamicMemory2D(n,m);
    start = clock();

    //Create Population
    for (i = 0; i < n; i++){
        CreatePermutations(i);
        //printf("\n");
    }
    
    end = clock();
    double time = end - start;

    //Print Section
/*    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            printf("%i,", population[i][j]);
        }
    printf("\n");
    }*/
    printf("Exec Time: %f\n",(time)/CLOCKS_PER_SEC);
    system("pause");
}
//Population using binary values of 2^n combinations
void CreatePermutations(int i){
    int j;
    
    for (j = 0; j < m; j++){
         (i / (1 << j)) % 2;
        //printf("%i,", (i / (1 << j)) % 2);
    }
}

//Reserve Memory for 2D Arrays used in Voids
int** DynamicMemory2D(int n, int m){
    int **aux;
    int i;
    aux = (int**)malloc(n*sizeof(int*));
    for(int i = 0; i < n; i++){
        aux[i] = (int*)malloc(m*sizeof(int));
    }
  return(aux);
}