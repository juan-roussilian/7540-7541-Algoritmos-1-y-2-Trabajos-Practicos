#include "simulacion.h"
#include <string.h>

#define INICIAR_SIMULACION 'S'
#define AGREGAR_CASA 'A'
#define LISTAR_CASAS 'L'
#define CASAS_EXTINTAS 'E'
#define FINALIZAR_PROG 'Q'
#define EXITO 0
#define ERROR -1

/*Pre: No se debe cumplir ninguna precondicion para esta funcion.
 *Post: Se le pedira al usuario la cantidad de años que quiere simular y
 *      se retornaran.
 */
size_t pedir_anios_a_simular(){
	
	char* linea = NULL;
	int anios = -1;
	int  leidos = 0;
	
	printf("\nCuantos años se quieren simular?\n");
	
	while( (!linea) || (leidos != 1) || (anios < 0) ){
		
		printf("Ingresar solo numeros positivos para los años: ");
		linea = leer_linea(stdin);
		if(linea){
			leidos = sscanf(linea, "%i", &anios);
		}	
	}
	printf("Simulando %i años\n",anios);
	return (size_t)anios;
}

/*Pre: No se debe cumplir ninguna precondicion para esta funcion.
 *Post: Se imprimiran por pantalla los los comandos que puede ingresar
 *		el usuario para usar la simulacion y se le explicara que hace cada uno
 */
void mostrar_comandos(){

	printf("\nSimulacion Juego de Tronos -- Utilize alguno de los siguientes comandos para iniciar:\n");
	printf("\n    S: Iniciar simulacion.\n");
	printf("\n    A: Agregar una casa al arbol.\n");
	printf("\n    L: Listar casas.\n");
	printf("\n    E: Mostrar casas extintas.\n");
	printf("\n    Q: Finalizar el programa.\n\n");
}	
      
int main(){
	abb_t* casas = arbol_crear(comparar_casas, destruir_casa);
	cola_t* casas_extintas = cola_crear();
	size_t anios;
	char* comando_ingresado = NULL;
	bool hay_error = false;
	mostrar_comandos();
	
	do{	
		printf("\nIngrese un comando deseado: ");
		comando_ingresado = leer_linea(stdin);
		switch(comando_ingresado[0]){
				
			case INICIAR_SIMULACION:
				anios = pedir_anios_a_simular();
				hay_error = (iniciar_simulacion(casas, casas_extintas, anios) == ERROR? true:false);
			break;
			
			case AGREGAR_CASA:
				hay_error = (agregar_casas_arbol(casas) == ERROR? true:false);
			break;

			case LISTAR_CASAS:
				listar_casas(casas);
			break;

			case CASAS_EXTINTAS:
				mostrar_casas_extintas(casas_extintas);
			break;

			case FINALIZAR_PROG:
			break;

			default:
				printf("\nComando inexistente. Utilizar los comandos mencionados.\n");
			break;
		}	
	}while( (comando_ingresado[0] != FINALIZAR_PROG) && (!hay_error) );
	
	if(hay_error){
		printf("Hubo un error al simular. Revisar que el archivo a ser leido se encuentre en el directorio del programa,");
		printf(" que el formato del archivo sea correcto, y que no falte memoria.\n");
	}
	destruir_simulacion(casas, casas_extintas);

		
	return 0;
}	