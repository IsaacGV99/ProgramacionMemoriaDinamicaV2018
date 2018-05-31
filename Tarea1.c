/*
 ============================================================================
 Name        : Tarea1.c
 Author      : José Isaac Gallegos Velica
 Version     : 28/05/2018
 Description : Este programa recibe dos listas que contienen no mas de 20 nombres
 	 	 	 	 profesores junto con su calificación (pueden repetirse).
 	 	 	 	 Los profesores son ordenados en otra lista de mayor a menor
 	 	 	 	 calificación, si hay un profesor repetido se promedian sus
 	 	 	 	 calificaciones.
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char nombre[15];
	float calificacion;
} Profesor;

float averageArray(Profesor arrayR[], int n);
void readArray(Profesor arr[], int *n);
void mergeArrays(Profesor arr1[] , int* n1, Profesor arr2[], int* n2, Profesor arrF[], int* nF);
void sortArray(Profesor arr[], int *n);
void printArray(Profesor arr[], int n);


int main(){
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	Profesor arr1[20];  //Primer arreglo
	Profesor arr2[20];  //Segundo arreglo
	Profesor arrF[40];  //Arreglo final, con elementos fusionados y ordenados
	int n1, n2; //Longitud de los arreglos
	int nF;
	readArray(arr1,&n1); //leer el primer arreglo
	readArray(arr2,&n2); //leer el segundo arreglo

	mergeArrays(arr1,&n1,arr2,&n2,arrF,&nF);  //Fusionar los dos arreglos en un tercer arreglo
	sortArray(arrF,&nF);  //Ordenar los elementos del tercer arreglo, recuerde que pueden existir profesores repetidos
	printArray(arrF,nF);   //Imprimir el resultado final

return 0;
}
float averageArray(Profesor arrayR[], int n){
	for(int k=1;k<n;k++)
		arrayR[0].calificacion+=arrayR[k].calificacion;
	arrayR[0].calificacion/=n;
	return(arrayR[0].calificacion);
}
void readArray(Profesor arr[], int *n){
	scanf("%d", n);
	for(int i=0;i<(*n);i++)
		scanf("%s %f", (arr[i].nombre), &(arr[i].calificacion));
}
void mergeArrays(Profesor arr1[] , int* n1, Profesor arr2[], int* n2, Profesor arrF[], int* nF){
	for(int i=0; i<*n1; i++)
		arrF[i]=arr1[i];
	for(int i=0; i<*n2; i++)
		arrF[*n1+i]=arr2[i];
	*nF=*n1+*n2;
}
void sortArray(Profesor arr[], int *n){
	//Algoritmo para eliminar repetidos
	for(int i=0;i<(*n-1);i++){
		int repetidos=1;
		Profesor arrayR[20];		//Arreglo que almacena las entradas repetidas de un mismo profesor
		arrayR[0]=arr[i];
		for(int j=i+1;j<*n;j++){
			if(strcmp(arr[i].nombre,arr[j].nombre)==0){			//Si se repite hacer:
				arrayR[repetidos]=arr[j];		//*Añadir al arreglo de repetidos
				repetidos++;
				for(int k=j;k<(*n-1);k++)		//*Recorrer los elementos despues del repetido
					arr[k]=arr[k+1];
				j--;
				--*n;							//*Restar 1 al total de elementos
			}
		}
		if(repetidos>1)				//Si hubo repetidos promediar la calificacion
			arr[i].calificacion=averageArray(arrayR,repetidos);
	}
	//Algoritmo para ordenar de mayor a menor, tipo ShellSort
	for (int inc=*n/2; inc>0;inc=(inc==2?1:(inc/2.2))){
		for(int i=inc;i<*n;i++){
			for(int j=i;
					j>=inc && arr[j-inc].calificacion<arr[j].calificacion;
					j-=inc){
				Profesor temp=arr[j];
				arr[j]=arr[j-inc];
				arr[j-inc]=temp;
			}
		}
	}
}
void printArray(Profesor arr[] , int n){
	for(int i=0;i<n;i++){
		printf("%s\t\t%0.2f\n", arr[i].nombre, arr[i].calificacion);
	}
}
