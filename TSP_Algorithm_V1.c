/*Pruebas del Algoritmo Traveling Salesman Problem con instancias reales Version 1.0*/
//Fuente instancias: http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsp/index.html
//Info TSP: http://www.math.uwaterloo.ca/tsp/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define BUFFER_SIZE 512

int main(){
    FILE *archivo = fopen("C:\\Workdir\\swiss42.tsp", "r"); 
    char buffer[BUFFER_SIZE]; 
    char delim[] = " "; 
    char *Token;
    long start, end; 
    int i,j,jb,k,x,y,m,n,r,temp,aux_c,average,sumweigh,size,padre1,padre2,hijo,cont,ITER_SIN_MEJORA;
    int intToken,instancia[150][150];
    const int MAX_ITER_SIN_MEJORA = 10;

    srand(128);

    start = clock();

    if(archivo == NULL){
        printf("Error de Lectura");
    } 
    else {
    //Recorrer archivo hasta fin de columna del array(\n) después salta la siguiente linea hasta NULL
        i = 1;
        while(fgets(buffer, BUFFER_SIZE, archivo) != NULL){
            aux_c=j;
            j = 1;
            Token = strtok(buffer, delim); 
            while(Token != NULL){    
                intToken=atoi(Token);
                instancia[i][j] = intToken;
                j++;
                Token = strtok(NULL, delim);
                }
        i++;
        }        
    }
    fclose(archivo);

//Generar Pila de Permutaciones
    m=i-1;n=aux_c-1; //ultimo ciclo quedó en width &lenght +1 por el ciclo while asi que resto -1
    int Random[j],poblacion[m][n];
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
        for (y = 1; y <= n; y++) {  // recorrer columnas poblacion unidimensional
            poblacion[x][y]=Random[y];
        }
    }
    
//Recorrer Arcos de Permutaciones y realizar sumatoria para el calculo de Distancias (Fitness)
    printf("\n");
    
    int sumacol;
    int alive[m][1];
    int distancia[m][1];
    memset(alive, 0, sizeof(alive)); //inicializo con ceros
  
    for (i=1; i<=n; i++){
        sumacol=0;
        for (j=1; j<=n; j++) {
            jb=j+1;
            x=poblacion[i][j];
            if(jb>n){
                    y=poblacion[i][1];
            }
            else{
                y=poblacion[i][jb];
            }
            sumacol+=instancia[x][y];
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
//Detección de Hijos Muertos y Selección de Padres - Los más fuertes Torneo Binario
    ITER_SIN_MEJORA=0;
    do{
        ITER_SIN_MEJORA++;
        for (i = 1; i <= n; i++){   //Recorrer Población
                if (alive[i][0] == 0){ //Encontrar un muerto
                    hijo = i;
                    do{             //Busco padres
                        padre1 = rand() % n+1;
                    }while(alive[padre1][0] == 0);
                    cont = 0;
                    do{
                        padre2 = rand() % n+1;
                        cont++;
                    }while((alive[padre2][0] == 0 || padre1 == padre2) && (cont < n/2));
//Cruza de Padre1 y Padre2, el resultante sustituye al hijo seleccionado si Peso es mejor que el muerto
                }
        }
    }while(ITER_SIN_MEJORA < MAX_ITER_SIN_MEJORA);

//Seccion de Impresion de: archivo, Permutaciones, Minimo/Promedio, Poblacion Viva.
    printf("--------------------------------------------------------------------------------------\n");
    printf("                           Contenido de archivo\n"); 
    printf("\n------------------------------------------------------------------------------------\n");
    for (i=1; i<=m; i++){           //TSP - Contenido archivo
        for (j=1; j<=n; j++){
            printf("%i,", instancia[i][j]);
	    }
        printf("\n");
    }
    printf("--------------------------------------------------------------------------------------------\n");
    printf("\n Col1 (Vivos), Col2 (Peso) mas Permutaciones || Distancia Minima: [%i] & Promedio: [%i]\n", size, average);
    printf("\n------------------------------------------------------------------------------------------\n");
    for (i=1; i<=m; i++){
        printf("%i , ", alive[i][1]);
        printf("%i , ", distancia[i][0]);
        for (j=1; j<=n; j++){
            printf("%i, ",poblacion[i][j]);
	    }
        printf("\n");
    }   
    end = clock();
    printf("Total Time: %f\n",((end-start))/CLOCKS_PER_SEC);
    system("pause");
}
