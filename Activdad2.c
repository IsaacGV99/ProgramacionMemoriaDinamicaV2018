/*
 ============================================================================
 Name        : Activdad2.c
 Author      : José Isaac Gallegos Velica
 Version     : 23/05/2018
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int expediente;
	char nombre[100];
	int carrera;
	int edad;
}Alumno;
Alumno registrar();
void imprimir(int n_alumnos, Alumno *parray);
void eliminar(Alumno *parray, int n_alumnos, int balumno);
int ebuscar(Alumno *parray, int n_alumnos);
int nbuscar(Alumno *parray, int n_alumnos);
int leernombre(char *cad, int n) ;

int main()
{
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	char menu;
	int n_alumnos=0, buscar;
	Alumno array[20];
	Alumno* parray;
	parray=array;
	do{
		printf("MENU\n");
		printf("\t[a] Registrar nuevo alumno\n");
		printf("\t[b] Imprimir datos\n");
		printf("\t[c] Eliminar alumno\n");
		printf("\t[d] Buscar alumno\n");
		printf("\t[f] Salir\n");
		scanf("%s", &menu);
		switch(menu)
		{
			case 'a':
				*(parray+n_alumnos)=registrar();
				n_alumnos++;break;
			case 'b':
				imprimir(n_alumnos, parray);break;
			case 'c':
				eliminar(parray, n_alumnos, ebuscar(parray,n_alumnos));
				n_alumnos--;break;
			case 'd':
				printf("BUSCAR ALUMNO\n");
				printf("\t[0]Por expediente\n\t[1]Por nombre\n");
				scanf("%d", &buscar);
				if(buscar)
					imprimir(1,(parray+nbuscar(parray, n_alumnos)));
				else
					imprimir(1,(parray+ebuscar(parray, n_alumnos)));
				break;
			default: break;
		}
	}while(menu!='f');
	return EXIT_SUCCESS;
}
Alumno registrar()
{
	Alumno a1;
	printf("REGISTRAR\n");
	printf("\tNombre: ");
	leernombre(a1.nombre,100);
	printf("\tExpediente: ");
	scanf("%d", &a1.expediente);
	printf("\tCarrera: ");
	scanf("%d", &a1.carrera);
	printf("\tEdad: ");
	scanf("%d", &a1.edad);


	return a1;
}
void imprimir(int n_alumnos, Alumno *parray)
{
	printf("DATOS REGISTRADOS\n\n");
	for(int i=0; i<n_alumnos;i++)
	{
		printf("\tExpediente: %d\n", parray[i].expediente);
		printf("\tNombre: %s\n", parray[i].nombre);
		printf("\tCarrera: %d\n", parray[i].carrera);
		printf("\tEdad: %d\n\n", parray[i].edad);
	}
}
void eliminar(Alumno *parray, int n_alumnos, int balumno)
{
	for(int i=balumno;i<n_alumnos-1;i++)
		parray[i]=parray[i+1];
}
int ebuscar(Alumno *parray, int n_alumnos)
{
	int expediente, valido=0, balumno;
	do
	{
	printf("Ingrese el expediente: ");
	scanf("%d", &expediente);
	for(int i=0; i<n_alumnos; i++)
	{
		if(expediente==parray[i].expediente)
		{
			valido=1;
			balumno=i;
		}
	}
	if(valido)
		printf("Expediente invalido\n");
	}while(valido);
	return balumno;
}
int nbuscar(Alumno *parray, int n_alumnos)
{
	int valido=0, balumno;
	char nombre[100];
	do
	{
	printf("Ingrese el nombre: ");
	gets(nombre);
	for(int i=0; i<n_alumnos; i++)
	{
		if(nombre==parray[i].nombre)
		{
			valido=1;
			balumno=i;
		}
	}
	if(valido)
		printf("Nombre invalido\n");
	}while(valido);
	return balumno;
}
int leernombre(char *cad, int n) {
    int i, c;
    c=getchar();
    if (c == EOF)
    {
        cad[0] = '\0';
        return 0;
    }
    if (c == '\n')
        i = 0;
    else
    {
        cad[0] = c;
        i = 1;
    }
    for (; i < n-1 && (c=getchar())!=EOF && c!='\n'; i++)
       cad[i] = c;

    cad[i] = '\0';
    if (c != '\n' && c != EOF)
        while ((c = getchar()) != '\n' && c != EOF);

    return 1;
}
