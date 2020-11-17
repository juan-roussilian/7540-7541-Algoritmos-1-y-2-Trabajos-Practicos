
#include "copa.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>


#define DISTANCIA_MIN_ENTRE_PERSONA_COPA 10
#define MAX_OBJETOS 12
#define VIDA_MAX 50
#define VIDA_QUE_MUESTRA_COPA 15
#define SIN_VIDA 0
#define VIDA_POCIONES 15
#define CANTIDAD_POCIONES 3
#define DANIO_ESCGREGUTO 20
#define DANIO_ACROMANTULA 10
#define DANIO_BOGGART 15
#define DANIO_POR_PASO 3
#define CODIGO_JUGADOR 'J'
#define CODIGO_RIVAL 'G'
#define CODIGO_POCION 'P'
#define CODIGO_ESFINGE 'F'
#define CODIGO_RIDIKKULUS 'R'
#define CODIGO_IMPEDIMENTA 'I'
#define CODIGO_BOGGART 'B'
#define CODIGO_ACROMANTULA 'A'
#define CODIGO_ESCREGUTO 'E'
#define INTENTOS_DIRECC 4
#define CODIGO_COPA 'C'


/*
 * Devolverá una coordenada aleatoria dentro del rango TAMANIOxTAMANIO.
 * No valida que dicha coordenada coincida con un pasillo ni que exista 
 * otro objeto en esa posición.
 */
coordenada_t posicion_aleatoria(){
 	
 	coordenada_t posicion;
 	posicion.fil = (rand())%TAMANIO;
 	posicion.col = (rand())%TAMANIO;

 	return posicion;
 }

/* La funcion recibe un coordenada a buscar dentro de  un vector de coordenadas que se recibe con su tope, el cual debe ser mayor o igual a 0
 *y busca esa coordenada dentro del vector de posiciones.
 *	Si encuentra una coordenada igual dentro del vector, significa que esta ocupada y por lo tanto devuelve true. Si no esta ocupada, devuelve false.
 */

bool posicion_ocupada (coordenada_t comparacion, coordenada_t posiciones[MAX_OBJETOS], int* tope_posiciones){
	bool esta_ocupada = false;
	for (int i=0; i<(*tope_posiciones);i++){
		if (posiciones[i].fil == comparacion.fil && posiciones[i].col == comparacion.col){
			esta_ocupada =true;
		}		
	} 
	return esta_ocupada;
}

/*  La funcion recibe el laberinto original con las paredes, el vector de obstaculos del juego y su tope como referencia ya que se modificara,
 *  el vector de posiciones ocupadas el cual se inicializo previamente y su tope, tambien como referencia ya modificara. y por ultimo recibe
 *  el danio y el codigo del obstaculo que se quiere inicializar.
 *  Al finalizar, la funcion habra posicionado dicho obstaculo aleatoriamente, en una posicion libre en la que no haya paredes ni otros
 *	elementos. Se posicionara el obstaculo, dentro del vector de obstaculos con su respectivo danio y codigo, y se agregara su posicion
 *  al vector de posicines para que en proximas inicializaciones dicha posicion figure como ocupada 	
 */

void inicializar_obstaculo (char laberinto_original [TAMANIO][TAMANIO], obstaculo_t obstaculos[TOTAL_OBSTACULOS], int* tope_obstaculos,
                              coordenada_t posiciones[MAX_OBJETOS], int* tope_posiciones, char codigo_obstaculo, int danio_obstaculo){
 
obstaculos[(*tope_obstaculos)].codigo = codigo_obstaculo;
obstaculos[(*tope_obstaculos)].danio = danio_obstaculo;

	do {
      obstaculos[(*tope_obstaculos)].posicion.fil = posicion_aleatoria().fil;
      obstaculos[(*tope_obstaculos)].posicion.col = posicion_aleatoria().col;
	}
	while (laberinto_original[obstaculos[(*tope_obstaculos)].posicion.fil][obstaculos[(*tope_obstaculos)].posicion.col]== '#' || 
		   posicion_ocupada (obstaculos[(*tope_obstaculos)].posicion, posiciones, tope_posiciones));

	posiciones[(*tope_posiciones)].fil = obstaculos[(*tope_obstaculos)].posicion.fil;
	posiciones[(*tope_posiciones)].col = obstaculos[(*tope_obstaculos)].posicion.col;

(*tope_obstaculos)++;
(*tope_posiciones)++;
}


/*  La funcion recibe el laberinto original con las paredes, el vector de ayudas del juego y su tope como referencia ya que se modificara,
 *  el vector de posiciones ocupadas el cual se inicializo previamente y su tope, tambien como referencia ya modificara. y por ultimo recibe
 *  la vida a recuperar y el codigo de la ayuda que se quiere inicializar.
 *  Al finalizar, la funcion habra posicionado dicha ayuda aleatoriamente, en una posicion libre en la que no haya paredes ni otros
 *	elementos. Se posicionara la ayuda, dentro del vector de obstaculos con su respectivo danio y codigo, y se agregara su posicion
 *  al vector de posicines para que en proximas inicializaciones dicha posicion figure como ocupada. 	
 */

void inicializar_ayuda (char laberinto_original [TAMANIO][TAMANIO], ayuda_t ayudas[TOTAL_AYUDAS], int* tope_ayudas, 
	                    coordenada_t posiciones[MAX_OBJETOS], int* tope_posiciones, char codigo_ayuda, int vida_ayuda){

ayudas[(*tope_ayudas)].codigo = codigo_ayuda;
ayudas[(*tope_ayudas)].vida_a_recuperar = vida_ayuda;

	do {
      ayudas[(*tope_ayudas)].posicion.fil = posicion_aleatoria().fil;
      ayudas[(*tope_ayudas)].posicion.col = posicion_aleatoria().col;
	}
	while (laberinto_original[ayudas[(*tope_ayudas)].posicion.fil][ayudas[(*tope_ayudas)].posicion.col]== '#' ||
		    posicion_ocupada (ayudas[(*tope_ayudas)].posicion, posiciones, tope_posiciones));
	
	posiciones[(*tope_posiciones)].fil = ayudas[(*tope_ayudas)].posicion.fil;
	posiciones[(*tope_posiciones)].col = ayudas[(*tope_ayudas)].posicion.col;

	(*tope_ayudas)++;
	(*tope_posiciones)++;
}

/* La funcion recibe una variable coordenada_t la cual sera asignada una posicion aleatoria,dentro del laberinto
 * revisando antes si esta posicion asignada esta ocupada (si es el caso, esta en el vector posiciones el cual tambien recibe con su tope)
 * o si hay una pared en dicha posicion.
 */
void asignar_posicion_aleatoria (char laberinto_original[TAMANIO][TAMANIO],coordenada_t* posicion_comparable, 
	                             coordenada_t posiciones[MAX_OBJETOS], int* tope_posiciones){
 
 do {
	 posicion_comparable->fil = posicion_aleatoria().fil;
	 posicion_comparable->col = posicion_aleatoria().col;
  }
	while(laberinto_original[posicion_comparable->fil][posicion_comparable->col] == '#' ||
	       posicion_ocupada (*posicion_comparable, posiciones, tope_posiciones));
}


void inicializar_copa (juego_t* juego, coordenada_t posiciones[MAX_OBJETOS],int* tope_posiciones){
	
	juego->copa.codigo = CODIGO_COPA;
	asignar_posicion_aleatoria (juego->laberinto_original, &(juego->copa.posicion),posiciones, tope_posiciones);
	
	
	posiciones[(*tope_posiciones)].fil=juego->copa.posicion.fil;
	posiciones[(*tope_posiciones)].col=juego->copa.posicion.col;
	(*tope_posiciones)++;
}	
/* 
 *La funcion recibe al juego como referencia, con un vector de posiciones ocupadas a llenar,junto a su tope
 * el cual se modificara. inicializara al escreguto en una posicion aleatoria, e inicializara sus campos
 */
void inicializar_escreguto (juego_t* juego, coordenada_t posiciones[MAX_OBJETOS],int* tope_posiciones){
 
  inicializar_obstaculo (juego->laberinto_original, juego->obstaculos, &(juego->tope_obstaculos), posiciones, tope_posiciones, CODIGO_ESCREGUTO,
 	                        DANIO_ESCGREGUTO);
}

/* 
 *La funcion recibe al juego como referencia, con un vector de posiciones ocupadas a llenar,junto a su tope
 * el cual se modificara. inicializara al acromantula en una posicion aleatoria, e inicializara sus campos
 */

void inicializar_acromantula(juego_t* juego, coordenada_t posiciones[MAX_OBJETOS],int* tope_posiciones){
	
 inicializar_obstaculo (juego->laberinto_original, juego->obstaculos, &(juego->tope_obstaculos), posiciones, tope_posiciones, CODIGO_ACROMANTULA,
	                       DANIO_ACROMANTULA);
}

/* 
 *La funcion recibe al juego como referencia, con un vector de posiciones ocupadas a llenar,junto a su tope
 * el cual se modificara. inicializara al boggart  en una posicion aleatoria, e inicializara sus campos
 */

void inicializar_boggart (juego_t* juego, coordenada_t posiciones[MAX_OBJETOS],int* tope_posiciones){
	
 inicializar_obstaculo (juego->laberinto_original, juego->obstaculos, &(juego->tope_obstaculos), posiciones, tope_posiciones, CODIGO_BOGGART, 
		                  DANIO_BOGGART);
}

/* 
 *La funcion recibe al juego como referencia, con un vector de posiciones ocupadas a llenar,junto a su tope
 * el cual se modificara. inicializara a la ayuda impedimenta en una posicion aleatoria, e inicializara sus campos
 */

void inicializar_impedimenta (juego_t* juego, coordenada_t posiciones[MAX_OBJETOS],int* tope_posiciones){
	
	inicializar_ayuda (juego->laberinto_original, juego->ayudas, &(juego->tope_ayudas),posiciones, tope_posiciones, CODIGO_IMPEDIMENTA, 0);
}

/* 
 *La funcion recibe al juego como referencia, con un vector de posiciones ocupadas a llenar,junto a su tope
 * el cual se modificara. inicializara a la ayuda ridikkulus en una posicion aleatoria, e inicializara sus campos
 */

void inicializar_ridikkulus(juego_t* juego, coordenada_t posiciones[MAX_OBJETOS], int* tope_posiciones){
	
	inicializar_ayuda (juego->laberinto_original, juego->ayudas, &(juego->tope_ayudas),posiciones, tope_posiciones, CODIGO_RIDIKKULUS, 0);
}


/* 
 *La funcion recibe al juego como referencia, con un vector de posiciones ocupadas a llenar,junto a su tope
 * el cual se modificara. inicializara a una pocion en una posicion aleatoria, e inicializara sus campos
 */

void inicializar_pocion(juego_t* juego, coordenada_t posiciones[MAX_OBJETOS], int* tope_posiciones){
	
	inicializar_ayuda (juego->laberinto_original, juego->ayudas, &(juego->tope_ayudas),posiciones, tope_posiciones, 
		               CODIGO_POCION, VIDA_POCIONES);
}


/* 
 *La funcion recibe al juego como referencia, con un vector de posiciones ocupadas a llenar,junto a su tope
 * el cual se modificara. inicializara a la esfinge en una posicion aleatoria, e inicializara sus campos
 */

void inicializar_esfinge(juego_t* juego, coordenada_t posiciones[MAX_OBJETOS], int* tope_posiciones){
	
	inicializar_ayuda (juego->laberinto_original, juego->ayudas, &(juego->tope_ayudas),posiciones, tope_posiciones, CODIGO_ESFINGE, 0);
}

/* 
 *La funcion recibe al juego como referencia, con un vector de posiciones ocupadas a llenar,junto a su tope
 * el cual se modificara. inicializara al rival en una posicion aleatoria, la cual debe tener una distancia
 * manhattan mayor a 10 con respecto a la copa, e inicializara sus campos.
 */

void inicializar_rival(juego_t* juego, coordenada_t posiciones[MAX_OBJETOS], int* tope_posiciones){
	
	juego->rival.codigo = CODIGO_RIVAL;
	juego->rival.direccion = 'd';
	juego->rival.cantidad_pasos = 0;

	do {
	  asignar_posicion_aleatoria (juego->laberinto_original, &(juego->rival.posicion),posiciones, tope_posiciones);
	}
	while ( ( (abs(juego->copa.posicion.fil - juego->rival.posicion.fil) ) + ( abs(juego->copa.posicion.col - juego->rival.posicion.col) ) )
	           < DISTANCIA_MIN_ENTRE_PERSONA_COPA);	

	posiciones[(*tope_posiciones)].fil=juego->rival.posicion.fil;
	posiciones[(*tope_posiciones)].col=juego->rival.posicion.col;
	(*tope_posiciones)++;
}

/* 
 *La funcion recibe al juego como referencia, con un vector de posiciones ocupadas a llenar,junto a su tope
 * el cual se modificara. inicializara al jugador en una posicion aleatoria, la cual debe tener una distancia
 * manhattan mayor a 10 con respecto a la copa, e inicializara sus campos.
 */

void inicializar_jugador(juego_t* juego, coordenada_t posiciones[MAX_OBJETOS], int* tope_posiciones){
	juego->jugador.codigo = CODIGO_JUGADOR;
	juego->jugador.vida = VIDA_MAX;
	juego->jugador.tope_ayudas =0;

	do {
	asignar_posicion_aleatoria (juego->laberinto_original, &(juego->jugador.posicion),posiciones, tope_posiciones);
	}
	while ( ( (abs(juego->copa.posicion.fil - juego->jugador.posicion.fil) ) + ( abs(juego->copa.posicion.col - juego->jugador.posicion.col) ) ) < DISTANCIA_MIN_ENTRE_PERSONA_COPA);	
	
	posiciones[(*tope_posiciones)].fil=juego->jugador.posicion.fil;
	posiciones[(*tope_posiciones)].col=juego->jugador.posicion.col;
	(*tope_posiciones)++;

}
/*
 * Inicializará todas las estructuras con los valores correspondientes,
 * creará el laberinto, posicionará todos los elementos, etc.
 */

void inicializar_laberinto(juego_t* juego){
	coordenada_t posiciones [MAX_OBJETOS];
	int tope_posiciones =0;
	
	juego->tope_obstaculos =0;
	juego->tope_ayudas = 0;
	
	inicializar_copa(juego, posiciones, &tope_posiciones);
	
	inicializar_escreguto(juego,posiciones, &tope_posiciones);
	
	inicializar_acromantula(juego,posiciones, &tope_posiciones);
	
	inicializar_boggart(juego, posiciones, &tope_posiciones);
	
	inicializar_impedimenta(juego, posiciones, &tope_posiciones);
	
	inicializar_ridikkulus(juego, posiciones, &tope_posiciones);
	
	for (int numero_pocion=0; numero_pocion<CANTIDAD_POCIONES; numero_pocion++){
		
		inicializar_pocion(juego, posiciones, &tope_posiciones);
	}
	
	inicializar_esfinge(juego, posiciones, &tope_posiciones);
	
	inicializar_rival(juego,posiciones, &tope_posiciones);
	
	inicializar_jugador(juego,posiciones, &tope_posiciones);
}	
	

/*
 * Moverá el jugador hacia la dirección especificada.
 * Dicho movimiento es válido.
 */

        
void mover_jugador(jugador_t* jugador, char direccion){
	
	if (direccion == 'w'){
		jugador->posicion.fil -= 1;
	} 
	else if (direccion == 's'){
		jugador->posicion.fil += 1;
	}
	else if (direccion == 'a'){
		jugador->posicion.col -= 1;
	}
	else if (direccion == 'd'){
		jugador->posicion.col += 1;
	}



}
/*
 * La funcion recibe una fila y una columna que deben estar dentro del rango 0<= x < 15 debido a que deben estar dentro del laberinto
 * y a su vez recibe una direccion fila y direccion columna, las cuales representan la direccion en la que se quiere mover el jugador
 * el modulo de la suma de estas dos ultimas variables debe ser igual a uno ya que el jugador se puede mover un espacio por vez
 * La funcion revisa si la direccion en la que se espera que se mueva el jugador esta dentro del laberinto y devuelve true, si lo esta. y 
 * false si no 
 */

bool esta_dentro_laberinto (int fil, int col, int direccion_fil, int direccion_col ){
	
	bool esta = false;
	
 if ( ( col + direccion_col < TAMANIO) || ( fil + direccion_fil < TAMANIO ) || ( fil + direccion_fil  >= 0) ||  ( col + direccion_col >=0 ) ){
	 esta = true;
  }
	return esta;
}

/*
 * La funcion recibe una fila y una columna que deben estar dentro del rango 0<= x < 15 debido a que deben estar dentro del laberinto
 * y a su vez recibe una direccion fila y direccion columna, las cuales representan la direccion en la que se quiere mover el jugador
 * el modulo de la suma de estas dos ultimas variables debe ser igual a uno ya que el jugador se puede mover un espacio por vez
 * La funcion revisa si en la direccion en la que se quiere mover el jugador hay una pared. Devuelve True si la hay, y false si noS
 */

bool hay_pared (int fil, int col, int direccion_fil, int direccion_col, char laberinto_original [TAMANIO][TAMANIO]){
	bool la_hay =false;
	
	if ( (laberinto_original [fil + direccion_fil][col + direccion_col]) == '#') {
	 
		 la_hay = true;	
	}
	return la_hay;
} 



/*
 * Moverá el rival a la próxima posición.
 */
void mover_rival(juego_t* juego){
  
  bool se_movio = false;
  
  if (juego->rival.direccion == 'd'){

  	  while ( (juego->rival.cantidad_pasos < INTENTOS_DIRECC) && !(se_movio)){
	 
	 	    (juego->rival.cantidad_pasos)++;
	 
	 	    if (esta_dentro_laberinto( juego->rival.posicion.fil , juego->rival.posicion.col, 0, 1) && 
	 	        !hay_pared( juego->rival.posicion.fil, juego->rival.posicion.col, 0, 1, juego->laberinto_original) ) {
		 
		        se_movio=true;
		        juego->rival.posicion.col += 1; 
	        }
        }
        if (juego->rival.cantidad_pasos == INTENTOS_DIRECC){
  		    juego->rival.direccion = 's';
  		    juego->rival.cantidad_pasos =0;
        }
    }    
  
    if (juego->rival.direccion == 's'){

  	    while ( (juego->rival.cantidad_pasos < INTENTOS_DIRECC) && !(se_movio)){
	 
	 	    (juego->rival.cantidad_pasos)++;
	 
	 	    if (esta_dentro_laberinto( juego->rival.posicion.fil , juego->rival.posicion.col, 1, 0) && 
	 	        !hay_pared( juego->rival.posicion.fil, juego->rival.posicion.col, 1, 0, juego->laberinto_original) ){
		 
		          se_movio=true;
		          juego->rival.posicion.fil += 1; 
	        }
         }
        if (juego->rival.cantidad_pasos == INTENTOS_DIRECC){
  		   juego->rival.direccion = 'a';
  		   juego->rival.cantidad_pasos =0;
        }
    }   
   if (juego->rival.direccion == 'a'){

  	  while ( (juego->rival.cantidad_pasos < INTENTOS_DIRECC) && !(se_movio)){
	 
	 	  (juego->rival.cantidad_pasos)++;
	 
	 	  if (esta_dentro_laberinto( juego->rival.posicion.fil , juego->rival.posicion.col, 0, -1) && 
	 	     !hay_pared( juego->rival.posicion.fil, juego->rival.posicion.col, 0, -1, juego->laberinto_original) ){
		 
		     se_movio=true;
		     juego->rival.posicion.col -= 1; 
	        }
        }
        if (juego->rival.cantidad_pasos == INTENTOS_DIRECC){
  		   juego->rival.direccion = 'w';
  		   juego->rival.cantidad_pasos =0;
        }
    }   
    if (juego->rival.direccion == 'w'){

  	 while ( (juego->rival.cantidad_pasos < INTENTOS_DIRECC) && !(se_movio)){
	 
	 	 (juego->rival.cantidad_pasos)++;
	 
	 	   if (esta_dentro_laberinto( juego->rival.posicion.fil , juego->rival.posicion.col, -1, 0) && 
	 	       !hay_pared( juego->rival.posicion.fil, juego->rival.posicion.col, -1, 0, juego->laberinto_original) ){
		 
		       se_movio=true;
		       juego->rival.posicion.fil -= 1; 
	        }
        }
     
      if (juego->rival.cantidad_pasos == INTENTOS_DIRECC){
  		  juego->rival.direccion = 'd';
  		  juego->rival.cantidad_pasos =0;
  	    }	
    }
}




/*La funcion recibe una coordenada valida dentro del laberinto, y que no coincide con una pared, y el juego.
 *Si la coordenada que se le envio coincide con un obstaculo o una ayuda, devuelve el codigo de ese elemento
 *Si la coordenada que se le envio no coincide con la de otro elemento, se devuelve el caracter 'Z'
 */
char piso_objeto (coordenada_t coordenada_revisar, juego_t juego){
	char objeto_pisado = 'Z';
	
	for (int i=0; i<juego.tope_obstaculos; i++){
		if (coordenada_revisar.fil == juego.obstaculos[i].posicion.fil && coordenada_revisar.col == juego.obstaculos[i].posicion.col){
			objeto_pisado = juego.obstaculos[i].codigo;
		}
	}
	for (int j=0; j<juego.tope_ayudas;j++){
		if (coordenada_revisar.fil == juego.ayudas[j].posicion.fil && coordenada_revisar.col == juego.ayudas[j].posicion.col){
			objeto_pisado = juego.ayudas[j].codigo;
		}
	}


	return objeto_pisado;
}

/* La funcion recibe al registro del jugador, y un caracter que representa el codigo de 
 * la ayuda buscada, el cual esta dentro de los caracteres definidos para cada ayuda
 * Busca dentro del vector ayudas del jugador y si encuentra una ayuda con el mismo codigo,  
 * devuelve true, sino devuelve false, ya que el jugador no posee dicha ayuda
 */

bool jugador_tiene_ayuda (jugador_t jugador, char codigo_ayuda){
	
	bool la_tiene = false;
	
	for (int i=0; i<jugador.tope_ayudas; i++){
		if (jugador.ayudas[i].codigo == codigo_ayuda){
			la_tiene = true;
		}
	}
	return la_tiene;

}

/* La funcion recibe el vector de obstaculos dentro del juego, con su respectivo tope,
 * el cual lo recibe como referencia ya que al eliminar un objeto, debera decrementar el tope	
 * tambien recibe la coordenada de posicion actual del jugador la cual es valida dentro del laberinto
 * La funcion buscara el obstaculo sobre el cual el jugador este parado y lo eliminara del vector de
 * obstaculos del juego, intercambiando este obstaculo por el ultimo del vector, y como se menciono
 * antes, decrementando el tope. El obstaculo se elimina ya que este interactuo con el jugador
 */

void eliminar_obstaculo_juego (obstaculo_t obstaculos [TOTAL_OBSTACULOS], int* tope_obstaculos, coordenada_t pos_jugador){
	
	for (int i=0;i<(*tope_obstaculos); i++){
		
		if (obstaculos[i].posicion.fil == pos_jugador.fil && obstaculos[i].posicion.col == pos_jugador.col){
			
			obstaculos[i].codigo = obstaculos[(*tope_obstaculos) -1].codigo;
			obstaculos[i].posicion.fil = obstaculos[(*tope_obstaculos) -1].posicion.fil;
			obstaculos[i].posicion.col = obstaculos[(*tope_obstaculos) -1].posicion.col;
			obstaculos[i].danio = obstaculos[(*tope_obstaculos) -1].danio;
			(*tope_obstaculos)--;
		}
	}			
}


/* Recibe el vector ayudas del juego, junto con su tope, y al jugador como referencia con sus determinados campos 
 * Busca dentro del vector ayudas del juego, la ayuda sobre la cual esta posicionado el jugador
 * y se la agrega al vector de ayudas del jugador campo por campo.
 */

void sumar_ayuda_jugador (ayuda_t ayudas_juego [TOTAL_AYUDAS], int tope_ayudas_juego, jugador_t* jugador){

	for (int i=0; i < tope_ayudas_juego; i++){
		if (ayudas_juego[i].posicion.fil == jugador->posicion.fil && ayudas_juego[i].posicion.col == jugador->posicion.col){
			
			jugador->ayudas[jugador->tope_ayudas].codigo = ayudas_juego[i].codigo;
			jugador->ayudas[jugador->tope_ayudas].posicion.fil = ayudas_juego[i].posicion.fil;
			jugador->ayudas[jugador->tope_ayudas].posicion.col = ayudas_juego[i].posicion.col;
			jugador->ayudas[jugador->tope_ayudas].vida_a_recuperar = ayudas_juego[i].vida_a_recuperar;
			(jugador->tope_ayudas)++;
		}
	}	

}

/* Recibe el vector de ayudas actuales dentro del laberinto junto con su tope pasado como referencia,
 * y la posicion actual  del jugador, la cual debe ser valida Dentro del laberinto.
 * Elimina la ayuda del juego sobre la que este esta parado, de la misma manera que lo hace la funcion
 * eliminar_obstaculo_juego.
 */

void eliminar_ayuda_juego (ayuda_t ayudas [TOTAL_AYUDAS], int* tope_ayudas, coordenada_t pos_jugador){
	
	for (int i=0;i < (*tope_ayudas); i++){
		
		if (ayudas[i].posicion.fil == pos_jugador.fil && ayudas[i].posicion.col == pos_jugador.col){
			
			ayudas[i].codigo = ayudas[(*tope_ayudas) -1].codigo;
			ayudas[i].posicion.fil = ayudas[(*tope_ayudas) -1].posicion.fil;
			ayudas[i].posicion.col = ayudas[(*tope_ayudas) -1].posicion.col;
			ayudas[i].vida_a_recuperar = ayudas[(*tope_ayudas) -1].vida_a_recuperar;
			(*tope_ayudas)--;
		}
	}			
}

/*	La funcion recibe al jugador,con sus campos inicializados y al vector de obstaculos dentro del juego con su tope
 * 	Busca dentro del vector de obstaculos cual es el objeto que esta en la misma posicion que el jugador y si este tiene la 
 *  ayuda que le permite no recibir el danio en su vector de ayudas, no pierde vida, si no la tiene, se le resta a su vida
 *  el danio que dicho obstaculo cause. En el caso de pararse sobre la acromantula, el jugador siemrpe recibe danio
 *	ya que no hay ayuda que lo defienda contra ese obstaculo
 */

void restar_danio_jugador (jugador_t* jugador, obstaculo_t obstaculos[TOTAL_OBSTACULOS], int tope_obstaculos){
	char codigo_obs;
	for(int i=0; i<tope_obstaculos; i++){
		if (obstaculos[i].posicion.col == jugador->posicion.col && obstaculos[i].posicion.fil == jugador->posicion.fil){
			codigo_obs = obstaculos[i].codigo;
		}
	}
	if (codigo_obs == 'E' && !(jugador_tiene_ayuda(*jugador, CODIGO_IMPEDIMENTA) ) ){
		jugador->vida -= DANIO_ESCGREGUTO;
	} 
	else if (codigo_obs == 'B' && !(jugador_tiene_ayuda(*jugador, CODIGO_RIDIKKULUS) ) ){
		jugador->vida -= DANIO_BOGGART;
	}	
	else if (codigo_obs == 'A'){
		jugador->vida -= DANIO_ACROMANTULA; 
	}	
}	

/*
 * Actualizará el juego. Restará vida si el jugador está sobre un obstáculo 
 * o lo eliminará si cuenta con el hechizo, aprenderá hechizos y todo lo 
 * que pueda suceder luego de un turno.
 */

void actualizar_juego(juego_t* juego){
	juego->jugador.vida -= DANIO_POR_PASO;
	
	if(juego->jugador.vida > SIN_VIDA){
		
		switch (piso_objeto(juego->jugador.posicion, *juego ) ){
			
			case CODIGO_POCION:
			
			juego->jugador.vida += VIDA_POCIONES;
			
			if (juego->jugador.vida > VIDA_MAX){
				juego->jugador.vida = VIDA_MAX;
			}

			eliminar_ayuda_juego(juego->ayudas, &(juego->tope_ayudas), juego->jugador.posicion);
			break;
			
			case CODIGO_ESFINGE:
			case CODIGO_IMPEDIMENTA:
			case CODIGO_RIDIKKULUS:
			
			sumar_ayuda_jugador(juego->ayudas, juego->tope_ayudas, &(juego->jugador));
			eliminar_ayuda_juego(juego->ayudas, &(juego->tope_ayudas), juego->jugador.posicion);
			
			break;
			
			case CODIGO_ESCREGUTO:
			case CODIGO_BOGGART:
			case CODIGO_ACROMANTULA:
			
			restar_danio_jugador(&(juego->jugador), juego->obstaculos, juego->tope_obstaculos);
			eliminar_obstaculo_juego(juego->obstaculos,&(juego->tope_obstaculos), juego->jugador.posicion);
			
			break;
		}	

	}
}	

/*
 * Devolverá el estado del juego, 1 ganado, 0 en curso, -1 perdido.
 */
int estado_juego(juego_t juego){

	int estado = 0;

	if (  (juego.jugador.posicion.fil == juego.copa.posicion.fil) && (juego.jugador.posicion.col == juego.copa.posicion.col) && 
		  (juego.jugador.vida > SIN_VIDA) ){
	estado = 1;
	}

	else if (juego.jugador.vida <= SIN_VIDA){
	estado = -1;
	}

	else if ( (juego.rival.posicion.fil == juego.copa.posicion.fil) && (juego.rival.posicion.col == juego.copa.posicion.col) ){
		
		if ( (juego.jugador.posicion.fil != juego.copa.posicion.fil ) || (juego.jugador.posicion.col != juego.copa.posicion.col) ){
			estado = -1;
		}
	}

	return estado;
	
}



/*
 *La funcion recibe una matriz, y una posicion fila y una posicion columna, y un codigo en forma de caracter.
 *Dicha funcion asignara en la posicion fila/columna de la matriz recibida, el caracter del codigo recibido.
 */

void posicionar_laberinto_usuario (char laberinto_usuario[TAMANIO][TAMANIO], int fil, int col, char codigo ){
	laberinto_usuario[fil][col]= codigo;
}

/*
 *La funcion recibe una matriz 
 *Al finalizar, la funcion habra inicializado dicha matriz con espacios vacios en todas sus posiciones
 */

void limpiar_laberinto_usuario (char laberinto_usuario [TAMANIO][TAMANIO]){
	for (int i=0; i < TAMANIO; i++){
		for (int j=0; j < TAMANIO; j++){
			laberinto_usuario[i][j] = ' ';
		}
	}
}

/*
 * La funcion recibe el laberinto original con las paredes, y un laberinto de las mismas dimensiones, el cual 
 * debe estar inicializado con espacios vacios en todas sus posiciones
 * La funcion copiara las paredes del laberinto original dentro de la segunda matriz que recibe
 */

void agregar_paredes_laberinto_usuario (char laberinto_original[TAMANIO][TAMANIO], char laberinto_usuario[TAMANIO][TAMANIO]){
	
	for (int i=0;i < TAMANIO;i++){
		for (int j=0;j < TAMANIO;j++){
 			if (laberinto_original [i][j]=='#'){
 				laberinto_usuario [i][j] = '#';
 			}
		}
	}
}
	
/*
 * Actualizará la matriz mostrada al usuario, con los elementos presentes 
 * en el juego.
 */

void actualizar_laberinto(juego_t juego, char laberinto_usuario[TAMANIO][TAMANIO]){
	
	limpiar_laberinto_usuario (laberinto_usuario);

	agregar_paredes_laberinto_usuario(juego.laberinto_original, laberinto_usuario);

	if (juego.jugador.vida <= VIDA_QUE_MUESTRA_COPA || jugador_tiene_ayuda( juego.jugador, CODIGO_ESFINGE) ){
		
		posicionar_laberinto_usuario (laberinto_usuario,juego.copa.posicion.fil, juego.copa.posicion.col, CODIGO_COPA);
	
	}
	
	for(int i=0; i<juego.tope_obstaculos; i++){
		
	  	posicionar_laberinto_usuario(laberinto_usuario, juego.obstaculos[i].posicion.fil, juego.obstaculos[i].posicion.col, 
	  		                         juego.obstaculos[i].codigo);
	}
	
	for (int j=0; j<juego.tope_ayudas; j++){
		
		posicionar_laberinto_usuario(laberinto_usuario, juego.ayudas[j].posicion.fil, juego.ayudas[j].posicion.col, juego.ayudas[j].codigo);
	}

	posicionar_laberinto_usuario (laberinto_usuario, juego.rival.posicion.fil, juego.rival.posicion.col, juego.rival.codigo);
	posicionar_laberinto_usuario (laberinto_usuario, juego.jugador.posicion.fil, juego.jugador.posicion.col, juego.jugador.codigo );
}



/*La funcion recibe la variable valido, y un int para la columna y para la fila a la que se quiere mover. 
 *siempre uno de los dos debe ser 0 ya que el jugador solo puede moverse en linea recta y sino se moveria en diagonal.
 *ademas en valor absoluto, el otro int debe ser igual a 1 ya que el jugador se mueve un casillero por vez.
 *La funcion revisa si la posicion a la que se quiere mover el jugador tiene una pared o esta fuera del laberinto 
 * y en base a eso retorna si es valido el movimiento, modificanto la variable valido por referencia
 */
void chequear_pared_jugador (bool* valido, int direccion_fil, int direccion_col, juego_t* juego){

	if ( ( (juego->laberinto_original[juego->jugador.posicion.fil + direccion_fil][juego->jugador.posicion.col+direccion_col]) == '#') || 
	   (!esta_dentro_laberinto (juego->jugador.posicion.fil, juego->jugador.posicion.col, direccion_fil, direccion_col) ) ){
		 

		(*valido) = false;	
	}
} 

/*                       
 * Determinará si el caracter ingresado es válido, esto es, es el caracter ‘a’ o 
 * ‘s’ o ‘d’ o ‘w’ y además el jugador puede moverse en esa dirección, o sea, 
 * hay pasillo.
 */


bool es_movimiento_valido (juego_t* juego, char tecla){
        
    bool valido = true;

        if (tecla =='a'){
         chequear_pared_jugador(&valido,0,-1,juego);
        }
        
        else if (tecla=='s'){
         chequear_pared_jugador(&valido,1,0,juego);
        } 
        
        else if (tecla=='d'){
         chequear_pared_jugador(&valido,0,1,juego);
        }
        
        else if (tecla =='w'){
         chequear_pared_jugador(&valido,-1,0,juego);    
        }
        
        else {
        	valido =false;
        }


    return valido;
}

/*
 * Mostrará el laberinto por pantalla.
 */

void mostrar_laberinto (char laberinto_usuario[TAMANIO][TAMANIO]){
 
 	for (int i =0; i<TAMANIO; i++){
    	for (int j=0; j<TAMANIO; j++){
         printf("%c ",laberinto_usuario [i][j]);
	    }
        printf("\n");       
    }
 }

 