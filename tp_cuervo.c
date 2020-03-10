#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cuervo_tres_ojos.h"


#define ERROR_VISIONES_FORMATO "El formato de las visiones es incompatible"
#define ERROR_VISIONES "Hubo un error al acceder al archivo de visiones"
#define ERROR_MEMORIA "No hay mas memoria dinamica disponible. Terminando el programa"
#define ERROR_PUNTERO "se ha tratado de liberar un puntero que es nulo, reintentar con un puntero valido"
#define NOMBRE_CUERVO_ANTIGUO "Brynden"
#define NOMBRE_CUERVO_APRENDIZ "Bran"
#define FORMATO "%[^;];%[^;];%[^;];%c\n"
#define MAX_NOMBRE 50
#define RETORNO_FALLIDO -1
#define ERROR_FORMATO -2
#define RETORNO_EXITOSO 0
#define FIN_DE_ARCHIVO -1
#define FORMATO_CORRECTO 4

/*PRE: La funcion debe recibir un puntero a un archivo de texto abierto a modo lectura el cual debe 
 *	    contener visiones con el formato correcto, y un puntero a una variable del tipo vision_t	
 *POST: La funcion leera una vision del archivo, y asignara los datos de esta a los campos de la variable vision recibida 
 *		Si pudo leer una vision correctamente, devolvera 4	
 *		Si el formato leido del archivo es incorrecto, devolvera -2. 
 *		Si el archivo llego a su fin, devolvera -1
 */

int leer_vision (FILE* visiones, vision_t* vision_leida){	 
	
	int leidos = fscanf(visiones, FORMATO, vision_leida->protagonista,vision_leida->casa_protagonista, 
						vision_leida->descripcion, &(vision_leida->epoca) );
   	
   	if (leidos != FORMATO_CORRECTO && leidos != FIN_DE_ARCHIVO ) {
   		printf("%s\n", ERROR_VISIONES_FORMATO);
   		return ERROR_FORMATO;
   	}

    return leidos;
}

/*	PRE: La funcion debe recibir un puntero  a un archivo de texto abierto a modo lectura, el cual
 *		 debe contener visiones en el formato correcto, y un puntero a una variable del tipo cuervo_tres_ojos_t
 *		 con sus campos inicializados				
 *	POST: La funcion devolvera 0 si pudo cargar todas las visiones dentro del cuervo_tres_ojos_t sin tener
 *		  problemas por falta de memoria dinamica. Si los tuvo retornara -1, y si hay un problema en el 	
 *		  formato del archivo de visiones, devolvera -2 		
 */

int cargar_visiones (FILE* visiones, cuervo_tres_ojos_t* cuervo){
	
	int espacio_heap = 0;
	vision_t vision;
	int leidos = leer_vision (visiones, &vision);

	while ( (leidos > 0) && (espacio_heap == 0) ){

		espacio_heap = agregar_vision(cuervo, vision);
		leidos = leer_vision (visiones, &vision);
	}

	if (leidos == ERROR_FORMATO){
		return RETORNO_FALLIDO;
	}
	return espacio_heap;
}

/* PRE: La funcion debe recibir una variable vision_t con sus campos inicializados
 * POST: La funcion devolvera true si el protagonista de dicha vision es Jon Snow
 *		 o false en caso contrario	
 */

bool vision_jon (vision_t vision){
	return (strcmp(vision.protagonista,"Jon Snow") == 0); 
}

/* PRE: La funcion debe recibir una variable vision_t con sus campos inicializados
 * POST: La funcion devolvera true si la protagonista de dicha vision es Daenerys Targaryen
 *		 o false en caso contrario	
 */

bool vision_daenerys (vision_t vision){
	return (strcmp(vision.protagonista,"Daenerys Targaryen") == 0);
}

/* PRE: La funcion debe recibir una variable vision_t con sus campos inicializados
 * POST: La funcion devolvera true si el/la protagonista de dicha vision pertenece a la casa Stark
 *		 o false en caso contrario	
 */

bool vision_casa_stark (vision_t vision){
	return (strcmp(vision.casa_protagonista,"Stark") == 0);
}


int main(){
	
	char nombre_cuervo_viejo [MAX_NOMBRE];
	char nombre_cuervo_nuevo [MAX_NOMBRE];

	strcpy (nombre_cuervo_viejo, NOMBRE_CUERVO_ANTIGUO);
	strcpy (nombre_cuervo_nuevo, NOMBRE_CUERVO_APRENDIZ);

	FILE* visiones = fopen ("visiones.txt", "r");
	
	if (visiones == NULL){
		
		fclose(visiones);
		printf("%s\n",ERROR_VISIONES);
		return 0;	
	}

	cuervo_tres_ojos_t* cuervo_viejo = invocar_cuervo(nombre_cuervo_viejo);
	if (cuervo_viejo == NULL){

		printf("%s\n", ERROR_MEMORIA);
		return 0;
	}

	cuervo_aprendiz_t* cuervo_nuevo = invocar_aprendiz(nombre_cuervo_nuevo);
	if (cuervo_nuevo == NULL){

		printf("%s\n",ERROR_MEMORIA);
		free (cuervo_viejo);
		return 0;
	}

	if (cargar_visiones (visiones, cuervo_viejo) == RETORNO_EXITOSO){
		
		if ( (transmitir_visiones(cuervo_viejo, cuervo_nuevo, vision_jon) == RETORNO_EXITOSO) && 
		 	 (transmitir_visiones(cuervo_viejo, cuervo_nuevo, vision_daenerys) == RETORNO_EXITOSO) &&	
			 (transmitir_visiones(cuervo_viejo, cuervo_nuevo, vision_casa_stark) == RETORNO_EXITOSO) ){

			listar_visiones_transmitidas(*cuervo_nuevo, vision_casa_stark);
		}	
	}
		
	fclose (visiones);			
	
	if (destruir_cuervo(cuervo_viejo) == RETORNO_FALLIDO){
		printf("Al liberar cuervo %s\n", ERROR_PUNTERO );
	}
	
	if (destruir_aprendiz(cuervo_nuevo) == RETORNO_FALLIDO){
		printf(" Al liberar aprendiz %s\n", ERROR_PUNTERO);
	}

	return 0;
	
}