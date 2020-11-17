#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cuervo_tres_ojos.h"

#define ERROR_FORMATO "Se ha encontrado un error en el formato del archivo"
#define ERROR_CAPACIDAD "No se pudo ejecutar el programa con exito debido a la falta de memoria dinamica"
#define RETORNO_FALLIDO -1
#define RETORNO_EXITOSO 0
#define VISION_PASADA 'P'
#define	VISION_FUTURA 'F'


/*PRE: La funcion debe recibir una variable del tipo vision_t con sus campos llenos y un puntero a una variable
 *	   del tipo cuervo_aprendiz_t, el cual no debe ser NULL.
 *
 *POST: La funcion devuelve true si la vision recibida ya esta dentro del vector de visiones_adquiridas del
 *		puntero cuervo_aprendiz_t recibido, y false si no lo esta.
 */

bool es_repetida (vision_t vision, cuervo_aprendiz_t* aprendiz){
	
	bool es_repetida = false;

	for (int i = 0; i < aprendiz->cantidad_visiones; i++){
		
		if (  (strcmp(vision.protagonista, aprendiz->visiones_adquiridas[i].protagonista) == 0) &&
		      (strcmp(vision.casa_protagonista, aprendiz->visiones_adquiridas[i].casa_protagonista) == 0 ) &&
		      (strcmp(vision.descripcion, aprendiz->visiones_adquiridas[i].descripcion)== 0) &&
		      (vision.epoca == aprendiz->visiones_adquiridas[i].epoca) ){

			es_repetida = true;
		}
	}
	return es_repetida;
}


cuervo_tres_ojos_t* invocar_cuervo(char* nombre){

	cuervo_tres_ojos_t* cuervo = malloc(sizeof(cuervo_tres_ojos_t));

	if (cuervo == NULL){

		printf("%s\n", ERROR_FORMATO);
		return cuervo;
	}
	
	cuervo->visiones_del_pasado = NULL;
	cuervo->visiones_del_futuro = NULL;
	strcpy(cuervo->nombre, nombre);
	cuervo->cantidad_visiones_pasado = 0;
	cuervo->cantidad_visiones_futuro = 0;

	return cuervo;
}

cuervo_aprendiz_t* invocar_aprendiz(char* nombre){

	cuervo_aprendiz_t* cuervito = malloc (sizeof(cuervo_aprendiz_t));
	
	if (cuervito == NULL){

		printf("%s\n", ERROR_FORMATO);
		return cuervito;
	}
	cuervito->visiones_adquiridas = NULL;
	strcpy (cuervito->nombre, nombre);
	cuervito->cantidad_visiones = 0;

	return cuervito;
}

int agregar_vision(cuervo_tres_ojos_t* cuervo, vision_t vision){
	
	void* puntero_auxiliar = NULL;
	
	if (vision.epoca == VISION_PASADA){
		
		cuervo->cantidad_visiones_pasado++;											
		puntero_auxiliar = realloc(cuervo->visiones_del_pasado, sizeof(vision_t) *(unsigned)(cuervo->cantidad_visiones_pasado) );	
		
		if (puntero_auxiliar == NULL){

			printf("%s\n", ERROR_CAPACIDAD );
		 	return RETORNO_FALLIDO;
		}

		cuervo->visiones_del_pasado = puntero_auxiliar;
		cuervo->visiones_del_pasado[ (cuervo->cantidad_visiones_pasado)- 1] = vision;
		
	}

	else if (vision.epoca == VISION_FUTURA){
		
		cuervo->cantidad_visiones_futuro++;
		puntero_auxiliar = realloc (cuervo->visiones_del_futuro, sizeof(vision_t) * (unsigned)(cuervo->cantidad_visiones_futuro) );

		if (puntero_auxiliar == NULL){

		 	printf("%s\n",ERROR_CAPACIDAD);
		 	return RETORNO_FALLIDO ;
		}

		cuervo->visiones_del_futuro = puntero_auxiliar;
		cuervo->visiones_del_futuro[(cuervo->cantidad_visiones_futuro)- 1] = vision;
	}	

	return RETORNO_EXITOSO;
}	


int transmitir_visiones(cuervo_tres_ojos_t* cuervo, cuervo_aprendiz_t* aprendiz, bool (*es_transmisible)(vision_t)){
	
	void* puntero_auxiliar = NULL;
	
	for	(int i = 0; i < cuervo->cantidad_visiones_futuro ; i++){
		
		if (es_transmisible(cuervo->visiones_del_futuro[i]) && !es_repetida(cuervo->visiones_del_futuro[i], aprendiz) ){
			
			aprendiz->cantidad_visiones++; 
			
			puntero_auxiliar = realloc(aprendiz->visiones_adquiridas, sizeof(vision_t) * (unsigned)(aprendiz->cantidad_visiones) );
			
			if (puntero_auxiliar == NULL){
				printf("%s\n", ERROR_CAPACIDAD);
				return RETORNO_FALLIDO;
			}
			aprendiz->visiones_adquiridas = puntero_auxiliar; 
			aprendiz->visiones_adquiridas[(aprendiz->cantidad_visiones)-1] = cuervo->visiones_del_futuro[i];
		}
	}

	for	(int i = 0; i < cuervo->cantidad_visiones_pasado; i++){
		
		if ( (es_transmisible(cuervo->visiones_del_pasado[i])) && (!es_repetida(cuervo->visiones_del_pasado[i], aprendiz)  ) ){
			
			aprendiz->cantidad_visiones++; 
			
			puntero_auxiliar = realloc(aprendiz->visiones_adquiridas, sizeof(vision_t) * (unsigned)(aprendiz->cantidad_visiones) );
			if (puntero_auxiliar == NULL){
				printf("%s\n", ERROR_CAPACIDAD);
				return RETORNO_FALLIDO;
			}
			aprendiz->visiones_adquiridas = puntero_auxiliar;
			aprendiz->visiones_adquiridas[(aprendiz->cantidad_visiones)-1] = cuervo->visiones_del_pasado[i];
		}
	}

	return RETORNO_EXITOSO;		
}
void listar_visiones_transmitidas(cuervo_aprendiz_t aprendiz, bool (*es_listable)(vision_t)){

	for (int i = 0; i < aprendiz.cantidad_visiones; i++){
		
		if (es_listable(aprendiz.visiones_adquiridas[i]) ){
			
			printf("Vision de %s de la casa %s. Descripcion: %s Epoca: %c \n", 
				   aprendiz.visiones_adquiridas[i].protagonista, 
			 	   aprendiz.visiones_adquiridas[i].casa_protagonista, 
				   aprendiz.visiones_adquiridas[i].descripcion, 
				   aprendiz.visiones_adquiridas[i].epoca);
		}
	}
}

int destruir_cuervo(cuervo_tres_ojos_t* cuervo){
	
	if (cuervo == NULL){
	
		return RETORNO_FALLIDO;
	}
	
	free(cuervo->visiones_del_futuro);
	free(cuervo->visiones_del_pasado);
	free(cuervo);

	return RETORNO_EXITOSO;
}


int destruir_aprendiz(cuervo_aprendiz_t* aprendiz){
	
	if (aprendiz == NULL){
	
		return RETORNO_FALLIDO;
	}

	free(aprendiz->visiones_adquiridas);
	free(aprendiz);

	return RETORNO_EXITOSO;
}
