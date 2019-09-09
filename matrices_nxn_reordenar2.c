//Reacomodo de Información de Matrices NxN
#include <stdio.h>
int main() {
	int aux,auxf,auxc,n,f,c,i,j,tmp; //variables filas&columnas
	
	printf("\n--------------------------------------------------\n");
	printf("\nIngrese n para Matriz (0): ");
	scanf("%d",&n);
	printf("\n--------------------------------------------------\n");
	
	int A[n][n];
/*---------------------------------------------------------------------------------------*/
    printf("\nMatriz(0) Columna Izq. a Derecha. y Fila Arriba a Abajo\n\n");
	tmp=0;
    //Generar Datos y Estructura Matriz A m=fila n=columna
	tmp=0;
	for (f=1; f<=n; f++){
		for (c=1; c<=n; c++) {
			tmp=tmp+1;
			A[f][c]=tmp;
			printf("%i \t",A[f][c]);
			}
			printf("\n");			
	}
/*---------------------------------------------------------------------------------------*/
	printf("\nMatriz(1) Columna Derecha a Izq. y Fila Arriba a Abajo\n\n");
    i=0;j=0;c=n;
	for (f=1; f<=n; f++){		//filas de arriba a abajo
        i++;
		for (c=n; c>n/2; c--){	//columnas de derecha a izquierda solo mitad de N
			j++;
			auxf=A[i][j];		//extremo izquierdo
			auxc=A[f][c];		//extremo derecho
			A[f][c]=auxf;		//intercambio extremo izquierdo
			A[i][j]=auxc;		//intercambio extremo derecho
		}
       j=0; 
	}
	for (f=1; f<=n; f++){	//Impresion Matriz(1)
		for (c=1; c<=n; c++){
			printf("%i \t",A[f][c]);
		}
	printf("\n");
	}
/*---------------------------------------------------------------------------------------*/
    printf("\nMatriz (2) Fila de Abajo hacia Arriba y Columna Derecha a Izq.\n\n");
	for (f=1; f<=n;f++){
        for (c=f; c<=n;c++){
            aux = A[f][c];
            A[f][c] = A[c][f];
            A[c][f] = aux;
        }
    }
	i=0;j=0;c=n;
	for (f=1; f<=n; f++){		//filas de arriba a abajo
        i++;
		for (c=n; c>n/2; c--){ //intercambio de extremos y columnas interiores
			j++;
			auxf=A[i][j];
			auxc=A[f][c];
			A[f][c]=auxf;
			A[i][j]=auxc;
		}
       j=0; 
	}
    for (f=1; f<=n; f++){	//Impresion Matriz(2)
		for (c=1; c<=n; c++){
			printf("%i \t",A[f][c]);
		}
	printf("\n");
	}
/*---------------------------------------------------------------------------------------*/	
	printf("\nMatriz (3) Fila de Abajo hacia Arriba y Columna Izq. a Derecha.\n\n");
    for (f=1; f<=n;f++){
        for (c=f; c<=n;c++){
            aux = A[f][c];
            A[f][c] = A[c][f];
            A[c][f] = aux;
        }
    }
	i=0;j=0;c=n;
	for (f=1; f<=n; f++){		//filas de arriba a abajo
        i++;
		for (c=n; c>n/2; c--){	//intercambio de extremos y columnas interiores
			j++;
			auxf=A[i][j];
			auxc=A[f][c];
			A[f][c]=auxf;
			A[i][j]=auxc;
		}
       j=0; 
	}
    for (f=1; f<=n; f++){	//Impresion Matriz(3)
		for (c=1; c<=n; c++){
			printf("%i \t",A[f][c]);
		}
	printf("\n");
	}
/*---------------------------------------------------------------------------------------*/	
	printf("\nMatriz (4) Fila de Arriba hacia Abajo y Columna Izq. a Derecha.\n\n");
	for (f=1; f<=n;f++){
        for (c=f; c<=n;c++){
            aux = A[f][c];
            A[f][c] = A[c][f];
            A[c][f] = aux;
        }
    }
	i=0;j=0;c=n;
	for (f=1; f<=n; f++){		//filas de arriba a abajo
        i++;
		for (c=n; c>n/2; c--){	//intercambio de extremos y columnas interiores
			j++;
			auxf=A[i][j];
			auxc=A[f][c];
			A[f][c]=auxf;
			A[i][j]=auxc;
		}
       j=0; 
	}
    for (f=1; f<=n; f++){	//Impresion Matriz(4)
		for (c=1; c<=n; c++){
			printf("%i \t",A[f][c]);
		}
	printf("\n");
	}
}
