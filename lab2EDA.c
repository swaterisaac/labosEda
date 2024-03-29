
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/*
 struct pixel:
 Un struct que guarda 3 enteros, para el ámbito de
 leer archivos de tuplas de 3.
 Las matrices serán punteros dobles de este struct
*/
struct pixel{
	int R;
	int G;
	int B;
}typedef pixel;
/*
struct CM:
Struct que incluye la matriz del struct pixel, sus filas y sus columnas. 
*/
struct conjuntoMatriz{
	pixel** matriz;
	int filas;
	int columnas;
}typedef CM;

/*
struct nodo:
Almacena un entero, y el puntero al nodo siguiente. En el caso de no tener siguiente, es NULL.

 */
struct nodo{
	int dato;
	struct nodo* sig;
}typedef nodo;


/*
Función constructora del TDA lista
 */
nodo* inicializar(){
    nodo* nodoR = NULL;
    return nodoR;
}

/* 
Función constructora del nodo. Recibe un entero para que tenga un valor.
*/
nodo* crearNodo(int valor){
  nodo* nodoCrear = (nodo*)malloc(sizeof(nodo));
  nodoCrear->dato = valor;
  nodoCrear->sig = NULL;
  return nodoCrear;
  }

/* 
insertar: Inserta ordenado a una lista enlazada (que ya esté ordenada).
entradas: puntero a nodo y el entero que se quiera agregar.
salida: el puntero a nodo con ese entero ubicado ordenadamente de menor a mayor.
*/
nodo* ingresar(nodo* nodoR,int datoAgregar){
  nodo* nuevoNodo = crearNodo(datoAgregar);
  nodo* aux = nodoR;
  nodo* aux2;
  if(nodoR == NULL){
      nodoR = crearNodo(datoAgregar);
      return nodoR;
    }
  if(aux->sig == NULL){
    if(aux->dato < datoAgregar){
      aux->sig = nuevoNodo;
      return nodoR;
      }
    nuevoNodo->sig = aux;
    nodoR = nuevoNodo;
    return nodoR;
    }
    if(aux->dato > datoAgregar){
    nuevoNodo->sig = aux;
    nodoR = nuevoNodo;
    return nodoR;
    }
  while(aux->sig != NULL){
    if(aux->dato > datoAgregar){
      nuevoNodo->sig = aux;
      aux2->sig = nuevoNodo;
      return nodoR;
      }
    aux2 = aux;
    aux = aux->sig;
    }
    if(aux->dato > datoAgregar){
      nuevoNodo->sig = aux;
      aux2->sig = nuevoNodo;
      return nodoR;
      }
  aux->sig = nuevoNodo;
  return nodoR;
}


/*  

Funciones estadísticas para listas enlazadas:
promedio
encontrarMenor
encontrarMayor
desvEst
mediana
Entrada: Una lista enlazada (puntero a nodo)
salida: Número (float o entero, dependiendo), dandonos el resultado pedido.


*/
float promedio(nodo* lista){
	float prom = 0.0;
	int cont = 0;
	nodo* aux = lista;
	while(aux != NULL){
		cont += 1;
		prom += aux->dato;
		aux = aux->sig;
	}
	
	return prom/cont;
}

int encontrarMenor(nodo*lista){
	int menor = lista->dato;
	nodo* aux = lista;
	while(aux != NULL){
		if(aux->dato < menor){
			menor = aux->dato;
		}
		aux = aux->sig;
	}
	return menor;
}

int encontrarMayor(nodo*lista){
	int mayor = lista->dato;
	nodo* aux = lista;
	while(aux != NULL){
		if(aux->dato > mayor){
			mayor = aux->dato;
		}
		aux = aux->sig;
	}
	return mayor;
}
float desvEst(nodo* lista){
	float desv = 0;
	int cont = 0;
	float datoAux;
	float prom = promedio(lista);
	nodo* aux = lista;
	while(aux != NULL){
		desv += pow((aux->dato - prom),2);
		cont += 1;
		aux = aux->sig;
	}
	return sqrt(desv/cont);
}

float mediana(nodo* lista){
	nodo* aux1 = lista;
	nodo* aux2 = lista;
	while(aux1 != NULL){
		if(aux2 == NULL){//par
			return (aux1->dato + aux1->dato)/2;
		}
		if(aux2->sig == NULL){//impar
			return aux1->dato;
		}
		aux2 = (aux2->sig)->sig;
		aux1 = aux1->sig;
	}
}
/*
leerMatriz: Función que lee un archivo de la forma:
<numColumnas> <numFilas>
a11 a12 a13 ... a1n
a21 a22 a23 ... a2n
.
.
am1 am2 am3 ... amn

con aij siendo tuplas de 3 de la forma <r,g,b>

Retorna un conjunto matriz (struct CM)
Entrada: Una cadena de carácteres indicando el nombre del archivo
Salida: Un conjunto de matriz, que representa el archivo leido. 
*/
CM leerMatriz(char* nombreArchivo){
	FILE* archivo = fopen(nombreArchivo,"r");
	if(archivo == NULL){
		printf("No existe archivo\n");
		exit(1);
	}
	
	CM matrizCompleta;
	int fila,columna;
	pixel pixRel;
	fscanf(archivo,"%d",&columna);
	fscanf(archivo,"%d",&fila);
	matrizCompleta.filas = fila;
	matrizCompleta.columnas = columna;
	
	matrizCompleta.matriz = (pixel**)malloc(sizeof(pixel*) * fila);
	for(int i = 0; i < fila; i++){
		pixel* filas = (pixel*)malloc(sizeof(pixel) * columna); 
		for(int j = 0; j < columna; j++){
			fscanf(archivo,"%d,%d,%d",&pixRel.R,&pixRel.G,&pixRel.B);
			filas[j] = pixRel;
		}
		matrizCompleta.matriz[i] = filas;
	}
	fclose(archivo);
	return matrizCompleta;
}
/*
imprimirMatriz: Funcion que muestra en pantalla una matriz.
Entrada: Conjunto matriz (CM)
Salida: Ninguna.
Función solo usada para debug. 
*/
void imprimirMatriz(CM matriz){
	for(int i = 0; i < matriz.filas;i++){
		for(int j = 0; j < matriz.columnas; j++){
			printf("%d,%d,%d  ",matriz.matriz[i][j].R,matriz.matriz[i][j].G,matriz.matriz[i][j].B);
		}
		printf("\n");
	}
	return;
}

void imprimirListaEnlazada(nodo* L){
	if(L == NULL){
		printf("NULL");
		return;
	}
	while(L != NULL){
		printf("%d   ",L->dato);
		L = L->sig;
	}
	printf("\n");

	return;
}
/*
comparadorPixel: Función que compara dos struct de pixel (si son iguales o no)
Entradas: Dos pixel
Salida: Un número entero.
0 indicando que son distintos
1 indicando que son iguales 
*/
int comparadorPixel(pixel px1, pixel px2){
	if(px1.R == px2.R && px1.G == px2.G && px1.B == px2.B)
		return 1;
	return 0;
}
/*
buscarMatriz: Funcion que recibe dos conjunto matriz, y nos dice si una está incluida en la otra
inclinadas con los ángulos 0,90,180,270.
Muestra las veces que está incluida una en la otra por pantalla.
Entradas: Dos conjunto matriz, con la condicion de que matriz1 tiene que tener mayor orden que matriz2.
Salida: Ninguna.
*/
nodo* buscarMatriz(CM matriz1,CM matriz2){
	nodo* nodoR = inicializar();
	if(matriz1.filas < matriz2.filas || matriz1.columnas < matriz2.columnas){
		printf("La matriz 2 es más grande que la 1.\n");
		return nodoR;
	}
	int similitud;
	int verif;
	
	for(int i = 0; i < matriz1.filas; i++){
		for(int j = 0; j < matriz1.columnas;j++){
			//Para 0 grados
			if(comparadorPixel(matriz2.matriz[0][0],matriz1.matriz[i][j]) == 1 && ((matriz1.filas - i - matriz2.filas) >= 0) && ((matriz1.columnas - j - matriz2.columnas) >= 0)){
				verif = 0;
				similitud = 0;
				for(int k = 0;k < matriz2.filas && verif == 0;k++){
					for(int w = 0;w < matriz2.columnas && verif == 0;w++){
						if(comparadorPixel(matriz2.matriz[k][w],matriz1.matriz[k+i][w+j]) == 0){
							verif = 1;
						}
						else{
							similitud += 1;	
						}
					}
				}
				nodoR = ingresar(nodoR,similitud);
			}
			//Para 90 grados
			if(comparadorPixel(matriz2.matriz[matriz2.filas - 1][0], matriz1.matriz[i][j]) == 1 && ((matriz1.filas - i - matriz2.columnas) >= 0) && ((matriz1.columnas  - j - matriz2.filas) >= 0)){
				verif = 0;
				similitud = 0;
				for(int k = (matriz2.filas - 1); k >= 0 && verif == 0; k--){
					for(int w = 0; w < matriz2.columnas && verif == 0; w++){
						if(comparadorPixel(matriz2.matriz[k][w],matriz1.matriz[w+i][matriz2.filas - 1 - k + j]) == 0){
							verif = 1;
						}
						else{
							similitud += 1;	
						}
					}
				}
				nodoR = ingresar(nodoR,similitud);
			}

			//Para 180 grados
			if(comparadorPixel(matriz2.matriz[matriz2.filas - 1][matriz2.columnas - 1], matriz1.matriz[i][j]) == 1 && ((matriz1.filas - i - matriz2.filas) >= 0) && ((matriz1.columnas - j - matriz2.columnas) >= 0)){
				verif = 0;
				similitud = 0;
				for(int k = (matriz2.filas - 1); k >= 0 && verif == 0; k-- ){
					for(int w = (matriz2.columnas - 1); w >= 0 && verif == 0; w--){
						if(comparadorPixel(matriz2.matriz[k][w],matriz1.matriz[matriz2.filas - 1 - k + i][matriz2.columnas - 1 - w + j]) == 0){
							verif = 1;
						}
						else{
							similitud += 1;	
						}
					}
				}
				nodoR = ingresar(nodoR,similitud);
			}
			//Para 270 grados
			if(comparadorPixel(matriz2.matriz[0][matriz2.columnas - 1],matriz1.matriz[i][j]) == 1 && ((matriz1.filas - i - matriz2.columnas) >= 0) && ((matriz1.columnas - j - matriz2.filas) >= 0)){
				verif = 0;
				similitud = 0;
				for(int k = 0; k < matriz2.filas && verif == 0;k++){
					for(int w = (matriz2.columnas - 1); w >= 0 && verif == 0; w--){
						if(comparadorPixel(matriz2.matriz[k][w],matriz1.matriz[matriz2.columnas - 1 - w + i][k+j]) == 0){
							verif = 1;
						}
						else{
							similitud += 1;	
						}
						
					}
				}
				nodoR = ingresar(nodoR,similitud);
			}
		}
	}
	return nodoR;
}
/*
Bloque principal 
*/
int main(){
	char nombre1[30];
	char nombre2[30];
	printf("Ingresa nombre del archivo de la imagen: ");
	scanf("%s",nombre1);
	printf("\nIngresa nombre del archivo de buscar: ");
	scanf("%s",nombre2);
	printf("\n");
	strcat(nombre1,".in");
	strcat(nombre2,".in");
	clock_t inicio = clock();




	CM matriz1 = leerMatriz(nombre1);
	CM matriz2 = leerMatriz(nombre2);
	nodo* L = buscarMatriz(matriz1,matriz2);
	imprimirListaEnlazada(L);
	FILE* archivo = fopen("datos.out","w");
	fprintf(archivo,"La media es: %f\n",promedio(L));
	fprintf(archivo,"El dato menor es: %d\n",encontrarMenor(L));
	fprintf(archivo,"El dato mayor es: %d\n",encontrarMayor(L));
	fprintf(archivo,"La desviacion es: %f\n",desvEst(L));
	fprintf(archivo,"La mediana es: %f\n",mediana(L));
	fclose(archivo);



	clock_t fin = clock();
	double time_taken = (double)(fin-inicio)/CLOCKS_PER_SEC;
	
	printf("Se demora %f segundos en ejecutar\n",time_taken);

	return 0;
}

