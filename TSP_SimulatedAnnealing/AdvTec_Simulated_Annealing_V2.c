/*Traveling Salesman Problem + Simulated*/
//Instance Sources: http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsp/index.html
//Profile: http://linkedin.com/in/alfredopea
//Alfredo Peña Ramos /PHD Student

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int n;
int indexBestSol=0;
int* Fitness;
int* alive;
int** population;
int** instance;
int *selectedPos,*selectedElement;
int PopulationSize=50;

int** DynamicMemory2D(int n, int m);
int CalculateFitness(int i);
void CreatePermutations(int i);
void SimAnnealing(int i);

int main(int args,char** arg){
    //put files in same code directory, if you want to add more instances to evaluate just modify array
    char files[1][25] = {"swiss42.tsp"};
    for (int list = 0; list < 1; list++){

        FILE *file = fopen(files[list], "r");
        long start, end; 
        int i,j,temp;
        
        //Change it, if you want permanent Permutations Values
        //srand(128);

        if(file == NULL){
            printf("Read Error");
        } 
        fscanf(file,"%d",&n);
        
        //Allocate Dynamic Memory 1D, 2D Arrays.
        Fitness = (int*)malloc(PopulationSize*sizeof(int));
        
        instance = DynamicMemory2D(n,n);
        population = DynamicMemory2D(PopulationSize,n);
        
        //Read Instance
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                fscanf(file,"%d",&instance[i][j]);
            }
        }
        fclose(file);

        //Clear Array
        for (i = 0; i < PopulationSize; i++){
            Fitness[i] = 0;
        }

        start = clock();

        //Create Population
            for (i = 0; i < PopulationSize; i++){
                CreatePermutations(i);
                Fitness[i] = CalculateFitness(i);
                SimAnnealing(i);
                if (Fitness[i] < Fitness[indexBestSol]){
                    indexBestSol = i;
                }
            }

    //Print Simulated Annealing Algorithm       
  
        printf("Fitness: %i\n",Fitness[indexBestSol]);
        printf("Solution: ");
        for (j = 0; j < n-1; j++){
            printf("%i, ",population[indexBestSol][j]);
        }
        printf("%i\n",population[indexBestSol][j]);

        end = clock();
        double time = end - start;

        printf("--------------------------------------------------------------------------------------------------------------------\n");
        printf("\n  Instance: [%s]  Best Solution: [%i]  Exec Time: %f\n", files[list],Fitness[indexBestSol],(time)/CLOCKS_PER_SEC);
        printf("\n-------------------------------------------------------------------------------------------------------------------\n");
    }
    system("pause");
}

void CreatePermutations(int i){
    int x,y,k,r,temp;
    int Random[n];
        for (k = 0; k < n; k++) {  // fill
            Random[k] = k;
        }
        for (k = 0; k < n-1; k++) {  //shuffle
            r = rand() % (n-k)+k;
            temp = Random[k];
            Random[k] = Random[r];
            Random[r] = temp;
        }
        for (y = 0; y < n; y++){    //insert
            population[i][y] = Random[y];
        }
}

//Calculate Fitness Population
int CalculateFitness(int i){
    int j, summcol;
    summcol = 0;
    for (j = 0; j < n-1; j++){
        summcol += instance[population[i][j]][population[i][j+1]];
    }
    summcol += instance[population[i][n-1]][population[i][0]];
    return(summcol);
}

//Simulated Annealing Algorithm
void SimAnnealing(int i){
    int j, Lold, Lnew, temp;
    double alpha = 0.5, T;

    for(j = 2; j < n-2;j++){
        for(T = 999999; T > 0.0037252866; T *= alpha){

            Lold =  instance[population[i][j-2]][population[i][j-1]];
            Lold +=  instance[population[i][j-1]][population[i][j]];
            Lold +=  instance[population[i][j]][population[i][(j+1)%n]];
            
            Lnew = instance[population[i][j-2]][population[i][j]];
            Lnew += instance[population[i][j]][population[i][j-1]];
            Lnew += instance[population[i][j-1]][population[i][(j+1)%n]];

            if(Lnew < Lold){
                Fitness[i] = Fitness[i] - Lold + Lnew;
                temp = population[i][j-1];
                population[i][j-1] = population[i][j];
                population[i][j] = temp;
            }
            else{
                if (exp(-1*(Lnew-Lold)/T) > (rand() / (double)RAND_MAX)){
                    Fitness[i] = Fitness[i] - Lold + Lnew;
                    temp = population[i][j-1];
                    population[i][j-1] = population[i][j];
                    population[i][j] = temp;
                }
            }
        }
    }
}

//Reserve Memory for 2D Arrays used in Voids - Black Magic
int** DynamicMemory2D(int n, int m){
    int **aux;
    int i;
    aux = (int**)malloc(n*sizeof(int*));
    for(int i = 0; i < n; i++){
        aux[i] = (int*)malloc(m*sizeof(int));
    }
  return(aux);
}