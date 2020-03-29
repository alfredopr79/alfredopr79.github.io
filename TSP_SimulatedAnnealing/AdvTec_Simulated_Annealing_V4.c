/*Traveling Salesman Problem + Simulated Annealing*/
//Instance Sources: http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsp/index.html
//Profile: http://linkedin.com/in/alfredopea
//Alfredo Peña Ramos /PHD Student

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int n;//Reading Instance Size
int indexBestSol=0;//Index Best Solution(s)
int* Fitness;//Store Fitness of Solution(s)
int** sol;//Store Solution
int** instance;//Store Instance
double PopulationSize=1;//Change it if you want more solutions

int** DynamicMemory2D(int n, int m);
int CalculateFitness(int i);
void CreatePermutations(int i);
void StaticPermutation(int i);
void SimAnnealing(int i);

int main(int args,char** arg){
    //put files in same code directory, if you want to add more instances to evaluate just modify array


    FILE *file = fopen("29ciudades.txt", "r");
    long start, end; 
    int i,j,temp;

    //Change it, if you want permanent Permutations Values
    srand(128);

    if(file == NULL){
        printf("Read Error");
    } 
    fscanf(file,"%d",&n);
    
    //Allocate Dynamic Memory 1D, 2D Arrays.
    Fitness = (int*)malloc(PopulationSize*sizeof(int));
    
    instance = DynamicMemory2D(n,n);
    sol = DynamicMemory2D(PopulationSize,n);
    
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
            StaticPermutation(i);//Solution like 0,1,2,3...n
            Fitness[i] = CalculateFitness(i);
            SimAnnealing(i);
            if (Fitness[i] < Fitness[indexBestSol]){
                indexBestSol = i;
            }
        }
    end = clock();
    double time = end - start;

//Print Simulated Annealing Algorithm       
        
    for (i = 0; i < PopulationSize; i++){
        printf("Fitness: %i\n",Fitness[i]);
        printf("Solution: ");
        for (j = 0; j < n-1; j++){                
            printf("%i, ",sol[i][j]);
        }
        printf("%i\n",sol[i][j]);
    }
        printf("--------------------------------------------------------------------------------------------------------------------\n");
        printf("\n  Best Solution: [%i]  Exec Time: %f\n",Fitness[indexBestSol],(time)/CLOCKS_PER_SEC);
        printf("\n-------------------------------------------------------------------------------------------------------------------\n");
        system("pause");
}

void StaticPermutation(int i){//Permutation like 0,1,2,3...n
    int x,y,k,r,temp;
        for (y = 0; y < n; y++){    
            sol[i][y] = y;
        }
}

//Calculate Fitness Population
int CalculateFitness(int i){
    int j, summcol;
    summcol = 0;
    for (j = 0; j < n-1; j++){
        summcol += instance[sol[i][j]][sol[i][j+1]];
    }
    summcol += instance[sol[i][n-1]][sol[i][0]];
    return(summcol);
}

//Simulated Annealing Algorithm
void SimAnnealing(int i){
    int j, Lold, Lnew, temp; 
    double T;

    for(T=180; T > 1;){
        for(j = 2; j < n-2;j++){//If LinkNew better than LinkOld change with LinkNew
            
            double alpha = 0.98;
            T *= alpha;

            Lold =  instance[sol[i][j-2]][sol[i][j-1]];
            Lold +=  instance[sol[i][j-1]][sol[i][j]];
            Lold +=  instance[sol[i][j]][sol[i][(j+1)%n]];
            
            Lnew = instance[sol[i][j-2]][sol[i][j]];
            Lnew += instance[sol[i][j]][sol[i][j-1]];
            Lnew += instance[sol[i][j-1]][sol[i][(j+1)%n]];

            if(Lnew < Lold){
                Fitness[i] = Fitness[i] - Lold + Lnew;
                temp = sol[i][j-1];
                sol[i][j-1] = sol[i][j];
                sol[i][j] = temp;
            }
            else{//If LNew isn't better then apply Boltzman function

                double probability = (rand() / (double)RAND_MAX);
                double bolztman = exp(-(Lnew-Lold)/T);

                if (bolztman > probability){
                    Fitness[i] = Fitness[i] - Lold + Lnew;
                    temp = sol[i][j-1];
                    sol[i][j-1] = sol[i][j];
                    sol[i][j] = temp;
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