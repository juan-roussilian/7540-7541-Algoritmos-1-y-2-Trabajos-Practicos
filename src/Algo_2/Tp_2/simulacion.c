#include "simulacion.h"
#include <string.h>

#define EXITO 0
#define ERROR -1
#define MAX_LINEA 500
#define MAX_CASAS 500
#define FORMATO_CASAS	"C;%[^;];%i;%i"
#define FORMATO_PERSONAS "I;%[^;];%zu"
#define FORMATO_CORRECTO_CASAS 3
#define FORMATO_CORRECTO_PERSONAS 2
#define CARACTER_CASA 'C'
#define CARACTER_PERSONA 'I'
#define MAX_EDAD 60

extern char* strdup(const char*);

int comparar_casas(void* casa1, void*casa2){
	
	int resultado = -1;
	casa_t* casa_1 = (casa_t*)casa1;
	casa_t* casa_2 = (casa_t*)casa2;
	
	if(strcmp(casa_1->nombre, casa_2->nombre) == 0){
		resultado = 0;
	}
	else if(strcmp(casa_1->nombre, casa_2->nombre) == 1){
		resultado = 1;
	}
	return resultado;
}

void destruir_casa(void* elemento){
	
	if(elemento){
		
		casa_t* casa_borrar = (casa_t*)elemento;
		lista_iterador_t* iterador = lista_iterador_crear(casa_borrar->personas);
		persona_t* persona_aux = NULL;
		
		while(lista_iterador_tiene_siguiente(iterador)){
			persona_aux = lista_iterador_siguiente(iterador);
			free(persona_aux);
		}
		lista_iterador_destruir(iterador);
		lista_destruir(casa_borrar->personas);
		free(casa_borrar->nombre);
	}	
}

/*Pre: La funcion debe recibir un array de punteros a datos casa_t no nulo y
 *     dos enteros los cuales representan las posiciones a intercambiar dentro del array
 *Post:	Se intercambiaran los elementos de las posiiciones recibidas dentro del array.
 */
void swap_casas(casa_t** vector_casas, int i, int j){

	casa_t* aux = vector_casas[i];
	vector_casas[i] = vector_casas[j];
	vector_casas[j] = aux;
}

/*Pre: Debe recibir un array de punteros a tipos de dato casa_t no nulo y un entero
 *	   representando el tamanio del array	
 *Post: Ordenara el array de casas descendentemente mediante el metodo Bubble sort,
 *		utilizando la cantidad de personas de cada casa como campo clave para comparar
 *		y ordenar.
 */
void ordenar_casas_descendentemente(casa_t* vector_casas[], int tope){
	
	for(int i = 1; i<tope; i++){
		for(int j = 0; j<tope-i; j++){
			if( (vector_casas[j]->cantidad_personas) < (vector_casas[j+1]->cantidad_personas) ){
				swap_casas(vector_casas, j, (j+1));
			}
		}
	}
}

/*Pre: La funcion debe recibir un  puntero a un abb no nulo.
 *Post: Se imprimira por pantalla cual es la casa con mas personas no extinta
 *		dentro del arbol. En caso de que no haya ninguna casa no extinta, se 
 *		imprimira que no queda ninguna casa viva.
 */
void imprimir_casa_en_el_trono(abb_t* casas){
	
	if(casas){
		if(!arbol_vacio(casas)){
			casa_t* vector_casas[MAX_CASAS];
			int tope = arbol_recorrido_preorden(casas, (void**)vector_casas, MAX_CASAS);
			if( (0 < tope) && (tope < MAX_CASAS) ){
				ordenar_casas_descendentemente(vector_casas, tope);
			}
			printf("La casa en el trono es: %s\n", vector_casas[0]->nombre);
		}
		else {
			printf("No quedo ninguna casa en pie. El trono no tiene dueño.\n");
		}
	}	
}

/*Pre: La funcion debe recibir punteros a un abb, una cola, y a un tipo de dato
 *	   casa_t no nulos. 
 *Post: Se eliminara del arbol la casa recibida como puntero, y se agregara el nombre
 *		de dicha casa a la cola de casas extintas.
 */
void extinguir_casa(abb_t* casas, casa_t* casa, cola_t* casas_extintas){
	
	cola_encolar(casas_extintas, strdup(casa->nombre));
	arbol_borrar(casas, casa);
}

/*Pre: La funcion debe recibir un puntero a un archivo no nulo.
 *Post: Se creara un tipo de dato persona_t inicializando su edad en 0
 *		y su nombre leyendo un nombre del archivo recibido. En caso
 *		de llegar al fin del archivo, la persona pasara a llamarse 
 *      "Persona Sin Nombre"
 */
persona_t* crear_persona_nacida(FILE* nombres){
	
	char* linea = NULL;
	persona_t* persona = calloc(1,sizeof(persona_t));
	
	if(persona){
		if(nombres){
			linea = leer_linea(nombres);
			if(linea){
				strcpy(persona->nombre, linea);
			}	
		}
		else{
			
			strcpy(persona->nombre, "Persona sin Nombre");
		}
	}
	return persona;
}

/*Pre: La funcion debe recibir un puntero a un tipo de dato casa_t no nulo
 *
 *Post: Se agregaran las personas que deban nacer al finalizar un anio de simulacion segun el
 *		el factor de nacimiento de dicha casa
 */
int agregar_nacidos(casa_t* casa){
	
	int  i = 0, resultado = ERROR;
	if(casa){
		
		size_t nacidos = (casa->cantidad_personas/(size_t)casa->factor_nacimiento);
		int pude_insertar = EXITO;
		bool pudo_nacer_persona = true;
		FILE* nombres = fopen("nombres_simulacion.txt" ,"r");

		while( (i < nacidos) && (pudo_nacer_persona) && (pude_insertar == EXITO) ){
			persona_t* persona_nacida  = crear_persona_nacida(nombres);
		
			if(persona_nacida){
				
				pude_insertar = lista_insertar(casa->personas,persona_nacida);		
				if(pude_insertar == EXITO){
					casa->cantidad_personas++;
				}
				i++;
			}
			else{
				pudo_nacer_persona = false;
			}	
		}
		if(i == nacidos){
			resultado = EXITO;
		}
		if(nombres){
			fclose(nombres);
		}	
	}
	return resultado;
}	

/*Pre: Se debe recibir un puntero a un tipo de dato casa_t no nulo.
 *Post:	Se simulara un anio dentro de dicha casa, aumentando la edad de sus habitantes
 *		segun el factor de envejecimiento de la casa. Si los habitantes mueren seran removidos
 *		de la lista de personas, y tambien se agregaran los que nacen segun el factor de nacimiento
 *		Devuelve 0 en caso de poder agregar y eliminar a los habitantes, o -1 en caso de error por
 *		falta de memoria.
 */
int simular_un_anio(casa_t* casa){
	
	int resultado = EXITO;
	
	if(casa){
		
		lista_iterador_t* iter = lista_iterador_crear(casa->personas);
		lista_t* lista_aux = lista_crear();
	
		while(lista_iterador_tiene_siguiente(iter)){
				
			persona_t* persona_aux = lista_iterador_siguiente(iter);
			persona_aux->edad += (size_t)(casa->factor_envejecimiento);
						
			if(persona_aux->edad >= MAX_EDAD){
				free(persona_aux);
			}
			else{
				resultado = lista_insertar(lista_aux, persona_aux);
			}
		}
		lista_iterador_destruir(iter);
		lista_destruir(casa->personas);
		casa->personas = lista_aux;
		casa->cantidad_personas = lista_elementos(casa->personas);
		resultado  = agregar_nacidos(casa);	
	}
	return resultado;
}


int iniciar_simulacion(abb_t* casas, cola_t* casas_extintas, size_t anios){
	
	int resultado = EXITO;
	
	if((casas) && (casas_extintas)){
		casa_t* vector_casas[MAX_CASAS]; 
		int tope = arbol_recorrido_preorden(casas, (void**)vector_casas, MAX_CASAS);
		
		if( (0 < tope) && (tope < MAX_CASAS) ){
			
			for(int i = 0; i<tope; i++){
				
				for(int j = 0; j < anios; j++){
					simular_un_anio(vector_casas[i]);			
				}
				if(vector_casas[i]->cantidad_personas == 0){
					extinguir_casa(casas, vector_casas[i], casas_extintas);
				}		
			}
		}	
	}
	imprimir_casa_en_el_trono(casas);	
	return resultado;
} 

/*Pre: La funcion debe recibir un puntero a un archivo no nulo.
 *Post: Leera una linea del archivo recibido, y la retornara. En caso de llegar al fin
 *		Del archivo retorna NULL.
 */
char* leer_linea(FILE* archivo){

  static char linea[MAX_LINEA];

  char* string_aux  = fgets(linea, MAX_LINEA, archivo);
  
  if(string_aux){
  	linea[strlen(linea)-1] = 0;
  }
  else{
  	return  NULL;
  }                                         
  return linea;                             
}             

/*Pre: Se debe recibir un String no nulo, con el formato especifico que representa
 *	   a una casa dentro de un archivo de texto.
 *Post: Se creara y se retornara un puntero a una variable casa_t con los campos 
 *		inicializados en los datos provistos por el string.	
 */
casa_t* crear_casa(char* linea){
	
	casa_t* casa = NULL;
	int leidos;
	
	if(linea){		
		
		casa = calloc(1,sizeof(casa_t));
		
		if(casa){
			leidos = sscanf(linea, FORMATO_CASAS, casa->nombre, &(casa->factor_envejecimiento), &(casa->factor_nacimiento));
			casa->personas = lista_crear();
			casa->cantidad_personas = 0;
		}	
		if(leidos != FORMATO_CORRECTO_CASAS){
			free(casa);
			casa = NULL;
		}
	}
	return casa;
}

/*Pre: Se debe recibir un String no nulo, con el formato especifico que representa
 *	   a una persona dentro de un archivo de texto.
 *Post: Se creara y se retornara un puntero a una variable persona_t con los campos 
 *		inicializados en los datos provistos por el string.	
 */
persona_t* crear_persona(char* linea){

	persona_t* persona = NULL;
	int leidos;
	
	if(linea){		
		persona = calloc(1,sizeof(persona_t));
		
		if(persona){
			leidos = sscanf(linea, FORMATO_PERSONAS, persona->nombre, &(persona->edad));
		}	
		if(leidos != FORMATO_CORRECTO_PERSONAS){
			free(persona);
			persona = NULL;
		}
	}
	return persona;
}

/*Pre: La funcion debe recibir un puntero a un abb y un puntero a un archivo no nulos.
 *Post: Se insertaran las casas y personas del archivo dentro del arbol. Se retornara 
 *		-1 en caso de no haber memoria suficiente para almacenar a todas las casas y personas
 *		o 0 si se dispone de suficiente memoria y se almaceno con exito dentro del arbol
 */
int cargar_arbol(abb_t* casas, FILE* archivo){
	int resultado = ERROR;
	
	if( (casas) && (archivo) ){
		char* linea = NULL;
		casa_t* casa = NULL;
		casa_t* casa_aux = NULL;
		persona_t* persona = NULL;
		resultado = EXITO;
		linea = leer_linea(archivo);
		while( (linea) && (resultado == EXITO) ){
			
			if(linea[0] == CARACTER_CASA){
				casa = crear_casa(linea);
				if(casa){
					casa_aux = casa;
					if(arbol_buscar(casas, casa) == NULL){
						resultado = arbol_insertar(casas, casa_aux);
					}
					else{
						casa = arbol_buscar(casas, casa);
						destruir_casa(casa_aux);
					}
				}				
			}
			else if(linea[0] == CARACTER_PERSONA && (casa)){
				persona = crear_persona(linea);
				if(persona){									
					resultado = lista_insertar(casa->personas, persona);
					casa->cantidad_personas++;
				}	
			}
			linea = leer_linea(archivo); 
		}
	}
	return resultado;
}

int agregar_casas_arbol(abb_t* casas){
	
	int resultado = ERROR;
	char* linea = NULL;

	printf("\nIngrese un nombre de archivo: ");
	linea = leer_linea(stdin);
    FILE* archivo = fopen(linea, "r");

  	while(!archivo){
  		printf("Archivo no encontrado. Ingrese otro nombre de archivo valido: ");
  		linea = leer_linea(stdin);
  		archivo =fopen(linea, "r");
  	}

    printf("Archivo ingresado: %s\n", linea);
    resultado = cargar_arbol(casas, archivo);
    fclose(archivo);
  
    return resultado;  
}


void listar_casas(abb_t* casas){
	
	if(casas){
		printf("\n%s\n",(arbol_vacio(casas)?"No hay ninguna casa con integrantes vivos":"Casas con mas personas:"));
		
		if(!arbol_vacio(casas)){
			
			casa_t* vector_casas[MAX_CASAS];		
			
			int tope = arbol_recorrido_preorden(casas, (void**)vector_casas, MAX_CASAS);
	
			if(tope > 1){
				ordenar_casas_descendentemente(vector_casas, tope);
			}
			for(int i = 0; i < tope; i++){
				printf("-%s\n", vector_casas[i]->nombre);
			}	
		}
	}	
}

void mostrar_casas_extintas(cola_t* casas_extintas){
		
	char* casa_extinta = NULL; 	
	printf("\n%s\n", (cola_vacia(casas_extintas)? "No se extingio ninguna casa":"Casas extintas en orden de desaparicion:"));
	
	while(!cola_vacia(casas_extintas)){
		
		casa_extinta = (char*)cola_primero(casas_extintas);
		printf("-%s\n", casa_extinta);
		free(casa_extinta);
		cola_desencolar(casas_extintas);
	}
}

/*Pre: Debe recibir un puntero a estructura cola no nulo.
 *Post: Liberara la memoria almacenada por la cola y los strings
 *		dentro de ella.
 */
void destruir_casas_extintas(cola_t* casas_extintas){
	
	if(casas_extintas){

		while(!cola_vacia(casas_extintas)) {
			free((char*)cola_primero(casas_extintas));
			cola_desencolar(casas_extintas);
		}
	free(casas_extintas);
	}
}

void destruir_simulacion(abb_t* casas, cola_t* casas_extintas){
	
	if(casas){
		arbol_destruir(casas);
	}
	if(casas_extintas){
		destruir_casas_extintas(casas_extintas);
	}	
}
