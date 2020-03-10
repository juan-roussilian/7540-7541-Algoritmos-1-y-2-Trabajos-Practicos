#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "carcel.h"

#define COMANDO_PERDONABLES "perdonables"
#define COMANDO_LIBERAR "liberar"
#define COMANDO_ACTUALIZAR "actualizar"
#define COMANDO_MOSTRAR_LIB "mostrar_liberados"
#define TRES_ARGUMENTOS 3
#define CINCO_ARGUMENTOS 5


int main (int argc, char *argv[]){

	if (argc == TRES_ARGUMENTOS){
		
		if ( strcmp(argv[1], COMANDO_PERDONABLES) == 0){
		 	 if (generar_archivo_perdonables(argv[2])){
		 	 	printf("Hubo un error al generar el archivo perdonables. \n");
		 	 	return 0;
		 	 }
		}
		else if (strcmp (argv[1], COMANDO_ACTUALIZAR) == 0){
			 int fecha  = atoi (argv [2]);

			 if (actualizar_archivos (fecha, argv [2])){
			 	printf("Hubo un error al actualizar archivos. \n"); 
			 }
		}
		else if (strcmp (argv[1], COMANDO_MOSTRAR_LIB) == 0){
			if (mostrar_presos_liberados(argv[2])){
				printf("Hubo un error al mostrar presos liberados. \n");
			}
		}
	}

	else if (argc == CINCO_ARGUMENTOS){
		
		if ( strcmp (argv[1], COMANDO_LIBERAR)  == 0) { 
			int fecha = atoi (argv [3]);
			if (liberar_presos (argv [2], fecha, argv[3], *argv[4]) ){
				printf("Hubo un error al liberar a los presos. \n");
			}
		}
	}	

	else {
		mostrar_ayuda();
	} 

	return 0;
}