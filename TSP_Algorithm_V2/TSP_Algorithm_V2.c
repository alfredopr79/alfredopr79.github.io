/*Traveling Salesman Problem Algorithm 2.0*/
//Instance Sources: http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsp/index.html
//My Profile: http://linkedin.com/in/alfredopea
//Alfredo Peña Ramos /PHD Student

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int n;
int indexBestSol=0;
int* Fitness;
int* alive;
int** population;
int** instance;
int *selectedPos,*selectedElement;
int PopulationSize=100;
const int HERITAGE_PERCENTAGE = 70;
const float Mutagenic = 5;

int** DynamicMemory2D(int n, int m);
int CalculateFitness(int i);
int CalcAverageAlive();
void CreatePermutations(int i);
void Procreate(int parent1,int parent2, int son);
void TMNT(int son);

int main(int args,char** arg){
    
    char files[3][25] = {"swiss42.tsp","bavaria29.tsp","dutch11.tsp"};
    int list;
    for (list = 0; list < 3; list++){
        
        //Put instance files in the same Workplace Folder
        FILE *file = fopen(files[list], "r");
        long start, end; 
        int i,j,temp,average;
        int parent1,parent2,son,count;
        int BestFit,iterNoImprovement;
        
        const int MAX_ITER_NO_IMPROVEMENT = 10;
        
        //Change it, if you want different Permutations Values
        srand(128);

        if(file == NULL){
            printf("Read Error");
        } 
        fscanf(file,"%d",&n);
        
        //Allocate Dynamic Memory 1D, 2D Arrays.s
        Fitness = (int*)malloc(PopulationSize*sizeof(int));
        alive = (int*)malloc(PopulationSize*sizeof(int));
        selectedElement = (int*)malloc(n*sizeof(int));
        selectedPos = (int*)malloc(n*sizeof(int));
        
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
            alive[i] = 0;
        }

    start = clock();

    //Create Population
        for (i = 0; i < PopulationSize/2; i++){
            CreatePermutations(i);
            alive[i] = 1;
            Fitness[i] = CalculateFitness(i);
            if (Fitness[i] < Fitness[indexBestSol])
            {
                indexBestSol = i;
            }
        }

    //Binary Tournament - Find Best Parents to Procreate new Son who will replace Dead One (creepy)
        iterNoImprovement = 0;
        do{
            iterNoImprovement++;       
            for (i = 0; i < PopulationSize; i++){//Traveling trough Population
                if (alive[i] == 0){ //Find Dead Son
                    son = i;
                    //Looking for parents
                    do{
                        parent1 = rand() % PopulationSize;
                    }while(alive[parent1] == 0);
                    count = 0;
                    do{
                        parent2 = rand() % PopulationSize;
                        count++;
                    }while((alive[parent2] == 0 || parent1 == parent2) && (count < PopulationSize));
                    
                    //Procreate son using parent 1 and 2
                    Procreate(parent1,parent2,son);
                    
                    //Teenage Mutant Ninja Turtles - TMNT 
                    if (rand() % 100 < Mutagenic)
                    {//Just a little bit of Mutagenic
                        TMNT(son);
                    }
                    alive[son] = 1;
                    Fitness[son] = CalculateFitness(son);
                }
            }
            //Calculate Average of the Best Best of the Best
            
            average = CalcAverageAlive();
            for (i = 0; i < PopulationSize; i++){
                if (Fitness[i] > average){
                    alive[i] = 0;
                }
                else{
                    if (Fitness[i] < Fitness[indexBestSol])
                    {
                        indexBestSol = i;
                        iterNoImprovement = 0;
                        printf("Best: %i\n",Fitness[indexBestSol]);
                        printf("Sol: ");
                        for (j = 0; j < n-1; j++){
                            printf("%i, ",population[indexBestSol][j]);
                        }
                        printf("%i\n",population[indexBestSol][j]);
                    }
                }
            }
        }while(iterNoImprovement < MAX_ITER_NO_IMPROVEMENT);

    //Print Section
        printf("--------------------------------------------------------------------------------------------\n");
        printf("\n  instance: [%s]  Best Solution: [%i]  with  Mutagenic Percentage=[%1.0f]  \n", files[list],Fitness[indexBestSol], Mutagenic);
        printf("\n------------------------------------------------------------------------------------------\n");
        end = clock();
        double time = end - start;
        printf("Overall Time: %f\n\n",(time)/CLOCKS_PER_SEC);
    }
    system("pause");
}
//Create Population
void CreatePermutations(int i){
    int k,r,temp;
    for (k = 0; k < n; k++) {  // fill
        population[i][k] = k;
    }
    for (k = 0; k < n-1; k++) {  // shuffle & insert
        r = rand() % (n-k)+k;
        temp = population[i][k];
        population[i][k] = population[i][r];
        population[i][r] = temp;
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

//Create New Sons
void Procreate(int parent1,int parent2, int son){
    int temp,i,j;
    if (Fitness[parent2] < Fitness[parent1]){
        temp = parent1;
        parent1 = parent2;  //Swap Parents
        parent2 = temp;
    }
    for(i = 0; i < n; i++){//Clear Aux Arrays
        selectedPos[i] = 0;
        selectedElement[i] = 0;
    }
    //Parent1 Heritage = HERITAGE_PERCENTAGE
    for(i = 0; i < n; i++){
        if (rand()%100 < HERITAGE_PERCENTAGE){
            selectedPos[i] = 1;
            population[son][i] = population[parent1][i];
            selectedElement[population[parent1][i]] = 1;
        }
    }
    //Parent2 Heritage = (100% - HERITAGE_PERCENTAGE)
    j = 0;
    for (i = 0; i < n; i++){
        if (selectedPos[i] == 0){
            for ( ; j < n && selectedElement[population[parent2][j]] == 1;j++);
            population[son][i] = population[parent2][j];
            selectedElement[population[parent2][j]] = 1;
            j++;
        }
    }
}
//Calculate Average of Population Alive
int CalcAverageAlive(){
    int average;
    int count,j;
    average = 0;
    count = 0;
    for (j = 0; j < PopulationSize; j++){
        if (alive[j] == 1){
            average += Fitness[j];
            count++;
        }
    }
    average = average/count;
    return (average);
}
//TMNT - Cowabunga!!
void TMNT(int son){
    int temp;
    int r, i;
    
    for (i = 0; i < n*(Mutagenic/100); i++){
        r = rand() % (n - 1);
        
        temp = population[son][r];
        population[son][r] = population[son][r+1];
        population[son][r+1] = temp;
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