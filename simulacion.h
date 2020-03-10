#ifndef __SIMULACION_H__
#define __SIMULACION_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "abb.h"
#include "cola.h"

#define MAX_NOMBRE 200


typedef struct casa{
	char nombre[MAX_NOMBRE];
	lista_t* personas;
	size_t cantidad_personas;
	int factor_nacimiento;
	int factor_envejecimiento;
}casa_t;

typedef struct persona{
	char nombre[MAX_NOMBRE];
	size_t edad;
}persona_t;

/*Pre: Debe recibir un puntero a una casa_t no nulo.
 *Post: Destructor de casas_t. Libera la memoria almacenada dentro
 *		de una variable del tipo casa_t.
 */
void destruir_casa(void* elemento);

/*Pre: La funcion debe recibir dos punteros a datos del tipo casa_t no nulos.
 *Post: Se retornara 0 en caso de que los nombres de las casas sean iguales, 1 si el
 *		nombre de la primer casa es mayor al de la segunda o -1 si el nombre de la primer es menor
 *   	que el de la segunda.
 */
int comparar_casas(void* casa1, void* casa2);

/*Pre: Debe recibir un puntero a dos estructuras de datos, un abb y una cola, no nulos.
 *	   y un entero positivo mayor a 0 representando la cantidad de anios a simular		
 *Post: Simulara los años pedidos para cada casa dentro del arbol, y si una  casa se 
 *		extingue la agregara la encolara en la cola recibida. Imprimira la casa que
 * 		queda en el trono del hierro luego de simular los anios pedidos si es que queda alguna 
 *		en el arbol. Sino se imprimira que ninguna casa se encuentra en el trono.
 *		Ademas retornara -1 en caso de haber algun error posible por falta de memoria
 *		o 0 si no hubo ningun problema al simular.  
 */
int iniciar_simulacion(abb_t* casas, cola_t* casas_extintas, size_t anios);

/*Pre: Debe recibir un puntero no nulo a un arbol binario de busqueda.
 *Post: Agregara las casas  pedidas por el usuario al arbol con todos sus integrantes.
 *	   Si dicha casa ya existe, se agregaran las personas nuevas a la casa repetida y devolvera
 *	   0. En caso de error retornara -1;	 
 */
int agregar_casas_arbol(abb_t* casas);

/*Pre: Debe recibir un puntero no nulo a un arbol binario de busqueda.
 *Post: Listara las casas no extintas dentro del arbol segun la cantidad
 *	    de integrantes en orden descendente.
 */
void listar_casas(abb_t* casas);

/*Pre: Debe recibir un puntero a una cola no nulo.
 *Post:	Imprimira por pantalla las casas extintas, en el orden en que fueron 
 *		desapareciendo.
 */
void mostrar_casas_extintas(cola_t* casas_extintas);


/*Pre: Debe recibir un puntero a un abb el cual contiene elementos casa_t
 *	   y un puntero a una cola_t, ambos no nulos.	
 *Post: Destruira el arbol de casas y la cola de casas extintas,
 *		liberando toda la memoria almacenada por estos
 */
void destruir_simulacion(abb_t* casas, cola_t* casas_extintas);

/*Pre: Debe recibir un puntero a un achivo/stream no nulo.
 *Post: Leera una linea de dicho archivo y la retornara
 */	
char* leer_linea(FILE* archivo);

#endif /* __SIMULACION_H__ */