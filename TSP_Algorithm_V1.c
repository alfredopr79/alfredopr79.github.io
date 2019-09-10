/*Pruebas del Algoritmo Traveling Salesman Problem con instancias reales Version 1.0*/
//Fuente instancias: http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsp/index.html
//Info TSP: http://www.math.uwaterloo.ca/tsp/

#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 4096 //sobrado a futuro lectura de 150x150

int main(){
    FILE *testFile = fopen("/workdir/swiss42.tsp", "r"); //apuntador al path de instancia
    char buffer[BUFFER_SIZE]; //buffer de 4096 bits (en caso de instancia de mayor tamaño)
    char *delim = " "; //apuntador al delimitador(un espacio) para lectura del Token
    char *Token;  //apuntador del Token que detecta el primer caracter que no es delimitador
    int i,j,jb,k,x,y,m,n,r,temp,aux_c,count,flag; //variables para recorrer arreglos y backup de info
    // 1.-almacenar el Token como entero 2.-arreglo con enteros de la instancia nxn
    int intToken,TSPInteger[150][150]; 

    if(testFile == NULL){
        printf("Error de Lectura");
    } 
    else {
    //Recorrer archivo hasta fin de columna del array(\n) después salta la siguiente linea hasta EOF (NULL)
    i = 1;count=1;
     while(fgets(buffer, BUFFER_SIZE, testFile) != NULL){
        if (count == 8){ //Leer a partir de la ĺínea 8 - instancias tienen comentarios hasta esa linea
        aux_c=j;
        j = 1;
        Token = strtok(buffer, delim); //Buscamos el primer Token verificando delimitador (espacio)
        while(Token != NULL){ //mientras el último token sea diferente de Nullo -->recorremos la linea del txt   
            if(strcmp(Token,"EOF")==0){ //verificar si el ultimo Token tiene string "EOF"
                flag = 1;
            }
            if (flag!=1){//si es diferente a EOF metemos el Token al arreglo
                intToken=atoi(Token); //el Token cuyo valor es un string lo convertimos en entero
                TSPInteger[i][j] = intToken; //insertamos en arreglo el valor del Token como entero
                //printf("TSPInteger[%i][%i] - %i\n", i, j, TSPInteger[i][j]); //Solo pruebas
            j++;
            }
            Token = strtok(NULL, delim); //Buscamos si el ultimo valor de Token es Null
        }
        i++;
        }
        else
        {
            count++;
        }        
    }
    fclose(testFile);
    }

      
    //Generar Pila de Permutaciones
    m=i-1;n=aux_c-1; //ultimo ciclo quedó en width &lenght +1 por el ciclo while asi que resto -1
    int Random[j],arreglo[m][n];
    for(x=1;x<=m;x++){              // recorrer el arreglo bidimensional en filas
        for (k = 1; k <= n; k++) {  // llenar arreglo unidimensional
            Random[k] = k;
        }
        for (k = 1; k <= n; k++) {  // barajar arreglo unidimensional
            r = rand() % n+1;
            temp = Random[k];
            Random[k] = Random[r];
            Random[r] = temp;
        }
        for (y = 1; y <= n; y++) {  // recorrer columnas arreglo unidimensional
            arreglo[x][y]=Random[y];// insertar en columnas al arreglo bidimensional
        }
    }
    int distancia[m][n+1];//requiero que sea de una columna más el arreglo de distancia vs pila de permutaciones            
    for (x=1; x<=m; x++){   //Respaldo Permutaciones en arreglo de Distancias
        for (y=1; y<=n; y++){
            distancia[x][y]=arreglo[x][y];
	    }
    }
    //RECORREMOS PILA DE PERMUTACIONES Y SACAMOS COORDENADAS DE LA INSTANCIA CON SU RESPECTIVA FILA
    // ADEMÁS DE REALIZAR SUMATORIAS DE DICHAS DISTANCIAS
    printf("\n");
    int sumacol;
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
                //printf("TSPInteger[%i][%i]: %i: %i \n", x,y,TSPInteger[x][y], sumacol);
                }
                //printf("\n");
                distancia[i][0]=sumacol;//inserto en columna cero las Distancias de las Permutaciones
            }
    for (i=1; i<=n; i++){           //Imprimir TSP - Resultados
        for (j=1; j<=n; j++){
            printf("%i,", TSPInteger[i][j]);
	    }
        printf("\n");
    }  

    printf("\n|Dist.|Permutaciones|\n");    
    for (x=1; x<=n; x++){           //Imprimir TSP - Resultados
        for (y=0; y<=n; y++){
            printf("%i,", distancia[x][y]);
	    }
        printf("\n");
    }    
    return 0;
}