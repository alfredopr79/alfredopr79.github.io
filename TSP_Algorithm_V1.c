/*Pruebas del Algoritmo Traveling Salesman Problem con instancias reales Version 1.0*/
//Fuente instancias: http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsp/index.html
//Info TSP: http://www.math.uwaterloo.ca/tsp/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define BUFFER_SIZE 512

int main(){
    FILE *instancia = fopen("C:\\Workdir\\swiss42.tsp", "r"); 
    char buffer[BUFFER_SIZE]; 
    char delim[] = " "; 
    char *Token;
    long start, end; 
    int i,j,jb,k,x,y,m,n,r,temp,aux_c,average,sumweigh,size; 

    int intToken,TSPInteger[150][150];
    srand(128);

    start = clock();

    if(instancia == NULL){
        printf("Error de Lectura");
    } 
    else {
    //Recorrer archivo hasta fin de columna del array(\n) después salta la siguiente linea hasta NULL
        i = 1;
        while(fgets(buffer, BUFFER_SIZE, instancia) != NULL){
            aux_c=j;
            j = 1;
            Token = strtok(buffer, delim); 
            while(Token != NULL){    
                intToken=atoi(Token);
                TSPInteger[i][j] = intToken;
                j++;
                Token = strtok(NULL, delim);
                }
        i++;
        }        
    }
    fclose(instancia);
//Generar Pila de Permutaciones
    m=i-1;n=aux_c-1; //ultimo ciclo quedó en width &lenght +1 por el ciclo while asi que resto -1
    int Random[j],arreglo[m][n];
    for(x=1;x<=m;x++){              
        for (k = 1; k <= n; k++) {  // llenar
            Random[k] = k;
        }
        for (k = 1; k <= n; k++) {  // barajar
            r = rand() % n+1;
            temp = Random[k];
            Random[k] = Random[r];
            Random[r] = temp;
        }
        for (y = 1; y <= n; y++) {  // recorrer columnas arreglo unidimensional
            arreglo[x][y]=Random[y];
        }
    }
    int distancia[m][n+1];  //Inserto Permutaciones en arreglo de Distancias
    for (x=1; x<=m; x++){ 
        for (y=1; y<=n; y++){
            distancia[x][y]=arreglo[x][y];
	    }
    }
//Recorrer Arcos de Permutaciones y realizar sumatoria para el calculo de Distancias (Fitness)
    printf("\n");
    int sumacol;
    int alive[m][1];
    memset(alive, 0, sizeof(alive));
    for (i=1; i<=n; i++){
        sumacol=0;
        for (j=1; j<=n; j++) {
            jb=j+1;
            x=arreglo[i][j];
            if(jb>n){
                    y=arreglo[i][1];
            }
            else{
                y=arreglo[i][jb];
            }
            sumacol+=TSPInteger[x][y];
        }
        distancia[i][0]=sumacol;
    }
    size=distancia[1][0];sumweigh=0;
    for (i=1; i<=n; i++){
        if(distancia[i][0] < size){ //Calcular la Mínima
            size=distancia[i][0];
        }
    }
    for (i=1; i<=n; i++){
        sumweigh+=distancia[i][0];  //Suma de Distancias de Permutaciones.
    }
    average=sumweigh / m;
    for (i=1; i<=m; i++){
        if (distancia[i][0] < average){
                alive[i][1]=1;
        }
    }
//Elaborar criterios de reproducción de población - Los más fuertes Torneo Binario



//Efectuar con Población Viva la eliminación de los pobladores con Fitness Bajo (Hasta el Final).
 /*   float survivors[m][n + 1];
    x=0;
    memset(survivors, 0, sizeof(survivors)); //Limpiar Arreglo con Ceros
    for (i=1; i<=m; i++){
            if(distancia[i][0] <= average){
                x++;
                for (j=0; j<=n; j++){
                    survivors[x][j] = distancia[i][j];
                }
            }
    }*/
//Seccion de Impresion de: Instancia, Permutaciones, Minimo/Promedio, Poblacion Viva.
    printf("--------------------------------------------------------------------------------------\n");
    printf("                           Contenido de Instancia\n"); 
    printf("\n------------------------------------------------------------------------------------\n");
    for (i=1; i<=m; i++){           //TSP - Contenido Instancia
        for (j=1; j<=n; j++){
            printf("%i,", TSPInteger[i][j]);
	    }
        printf("\n");
    }
    printf("--------------------------------------------------------------------------------------\n");
    printf("\n              Primera Columna (Distancias) mas Permutaciones|\n");
    printf("\n------------------------------------------------------------------------------------\n");
    for (i=1; i<=m; i++){
        printf("%i , ", alive[i][1]);
        for (j=0; j<=n; j++){
            printf("%i, ",distancia[i][j]);
	    }
        printf("\n");
    }
    printf("\n------------------------------------------------------------------------------------\n");
    printf("             Distancia Minima: [%i] & Promedio: [%i]\n", size, average); //TSP - Minimos y Fitness
    printf("\n------------------------------------------------------------------------------------\n");
   
    end = clock();
    printf("Total Time: %f\n",((end-start))/CLOCKS_PER_SEC);
    system("pause");
}
