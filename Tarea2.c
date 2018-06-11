/*
 ============================================================================
 Name        : Tarea2.c
 Author      : José Isaac Gallegos Velica
 Version     : 04/06/2018
 Description :
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	//Declaración de varibles
	float Pi=0, inicio, fin;
	unsigned long long i;

	inicio=clock();//Captura el tiempo de inicico

	i=50000000000;
	while(i){
		if((i&1)==0)			//pregunta si es par
			Pi-=(float)4/(2*i-1);
		else
			Pi+=(float)4/(2*i-1);
		i--;
	}

	fin=clock();//Captura el tiempo de finalizado
	printf("\nPi = %0.10f", Pi);	//impirime pi
	printf("\nTiempo de ejecución: %f segundos", (fin-inicio)/(float)CLOCKS_PER_SEC); //imprime el tiempo

}

