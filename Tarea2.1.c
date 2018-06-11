/*
 ============================================================================
 Name        : Tarea2.1.c
 Author      : José Isaac Gallegos Velica
 Version     : 04/06/2018
 Description :
 ============================================================================
 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NHILOS 2
typedef struct{
	long long p;
	float suma;
	int nhilos;
}argumento;
DWORD WINAPI SerieGregoryLeibniz(void*);
float SumaDeHilos(argumento array[]);
int main(){
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	int nhilos=1;
	float  inicio, fin;
	long long repeticiones;
	repeticiones=50000000000;

	inicio=clock();
	HANDLE *hilos;
	hilos=(HANDLE*)malloc(sizeof(HANDLE)*nhilos);
	argumento *array;
	array=(argumento*)malloc(sizeof(argumento)*nhilos);
	for(int i=0; i<nhilos; i++){
		array[i].p=repeticiones-i;
		array[i].suma=0;
		array[i].nhilos=nhilos;
		hilos[i]=CreateThread(NULL, 0,SerieGregoryLeibniz,	(void *)&(array[i]),0,NULL);
	}
	for(int i=0;i<nhilos;i++)
		WaitForSingleObject(hilos[i], INFINITE);
	fin=clock();
	printf("\nPi = %0.10f", SumaDeHilos(array));
	printf("\nTiempo de ejecución: %f segundos", (fin-inicio)/(float)CLOCKS_PER_SEC);
}
DWORD WINAPI SerieGregoryLeibniz(void *arg){
	argumento *p=arg;
	while(p->p>0){
			if(((p->p)&1)==0)
				(p->suma)-=(float)4/(2*(p->p)-1);
			else
				(p->suma)+=(float)4/(2*(p->p)-1);
			p->p-=p->nhilos;
		}
	return 0;
}
float SumaDeHilos(argumento array[]){
	float suma=0;
	for(int i=0;i<array->nhilos;i++){
		suma+=array[i].suma;
	}
	return suma;
}

