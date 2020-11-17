#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "copa.h"
#include "laberinto.h"
#define VIDA_MAX 50

/*
 * La funcion recibe un caracter como referencia ya que sera modificado
 * La funcion pregunta al usuario imprimiendo por pantalla si quiere iniciar una nueva partida y guarda su respuesta
 * en el caracter recibido.
 */

void preguntar_si_empezar (char *respuesta){
	printf("Presione S para iniciar nueva partida\n");
	scanf(" %c", respuesta);
}
/*
 * La funcion recibe un caracter como referencia ya que sera modificado
 * Esta funcion solo se encarga de leer el movimiento que desea hacer
 * el usuario en cada turno, y lo guarda dentro de movimiento_usuario.
 */

void leer_movimiento (char* movimiento_usuario){
	
	scanf (" %c", movimiento_usuario);
	printf("\n");
}

/* La funcion recibe como referencia un caracter que sera modificado
 * Esta funcion imprime por pantalla que el movimiento que el jugador envio
 * no es valido, y le pide que ingrese otro. Luego lo lee, y guarda ese movimiento
 * en la variable movimiento_usuario
 */

void movimiento_incorrecto (char* movimiento_usuario){
	printf("El Movimiento no es valido, por favor, elija otro movimiento utilizando las teclas: w, a ,s, d.\n");
	scanf (" %c", movimiento_usuario);
	printf("\n");
}

/*
 * La funcion se encarga de mostrar por pantalla la vida del usuario, por debajo
 * del laberinto, y para eso recibe todo el registro de juego.
 */

void mostrar_vida (juego_t juego){
	printf("      VIDA: %i / %i \n ", juego.jugador.vida, VIDA_MAX);
	printf("\n");
}

/*
 * La funcion recibe todo el registro del juego
 * La funcion imprime por pantalla el final del juego, invocando a la funcion estado juego
 * Si el jugador gano, imprime que gano, y si perdio, dependiendo de su vida, imprime que 
 * murio o que el rival llego a la copa antes.
 */

void mostrar_fin (juego_t juego){
	if (estado_juego(juego) == 1){
		printf("      Ganaste! la copa es tuya\n");
		printf("\n");
		printf("\n");
	}
	
	else if (estado_juego(juego) == -1 ){
		
		if (juego.jugador.vida <= 0){
			printf("      Moriste :( \n");
			printf("\n");
			printf("\n");
		}
		else {
			printf("      El rival agarro la copa \n");
			printf("\n");
			printf("\n");
		}
	}
}
int main (){

juego_t juego;
char movimiento_usuario;
char respuesta;
char laberinto_usuario [TAMANIO][TAMANIO];

srand((unsigned) time(NULL));
	
	do {
		
		preguntar_si_empezar (&respuesta);
		
		if (respuesta == 'S'){
			
			inicializar_paredes_laberinto(juego.laberinto_original);
					
			inicializar_laberinto(&juego);	

			printf("Para moverse, presione 'w' para subir, 's' para bajar, 'a' para ir hacia la izquierda, y 'd' para moverse hacia la derecha \n\n");

			do{
				actualizar_laberinto(juego, laberinto_usuario);

				mostrar_laberinto (laberinto_usuario);

				mostrar_vida (juego);
				
				leer_movimiento (&movimiento_usuario);
				
				while (!es_movimiento_valido(&juego, movimiento_usuario)){
					movimiento_incorrecto(&movimiento_usuario);
				}
				mover_jugador (&(juego.jugador), movimiento_usuario);

				mover_rival (&juego);

				actualizar_juego (&juego);

				mostrar_fin (juego);
		    }
			 
			 while ( (estado_juego(juego)) == 0);
		}
	}
	while (respuesta == 'S');

	return 0;
}	