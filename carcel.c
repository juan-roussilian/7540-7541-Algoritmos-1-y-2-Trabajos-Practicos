#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "carcel.h"

#define COMANDO_PERDONABLES "perdonables"
#define COMANDO_LIBERAR "liberar"
#define COMANDO_ACTUALIZAR "actualizar"
#define COMANDO_MOSTRAR_LIB "mostrar_liberados"
#define COMANDO_AYUDA "ayuda"
#define CONDUCTA_BUENA 'B'
#define CONDUCTA_REGULAR 'R'
#define CONDUCTA_MALA 'M'
#define CODIGO_LIBERADOS "liberados_"
#define EXTENSION_TXT ".txt"
#define RETORNO_EXITOSO 0
#define ERROR_ARCHIVOS -1

/*Pre: La funcion debe recibir un puntero a un archivo binario abierto a modo lectura, y un puntero a un tipo de dato preso_t
 *Post: La funcion leera la cantidad de bytes equivalente a una variable del tipo preso_t, y lo almacenara en el parametro
 *		preso_t recibido
 */
void leer_preso_bin (FILE* archivo, preso_t *preso){
	fread (preso, sizeof(preso_t), 1, archivo);
}

/*Pre: La funcion debe recibir un puntero a un archivo abierto binario abierto a modo escritura
 *     , y una variable del tipo preso_t la cual debe tener sus campos inicializados.
 *Post: La funcion escribira esa variable recibida dentro del archivo recibido como puntero. Si el parametro
 *		tiene alguno de sus campos no inicializados, ese campo se escribira como basura dentro del archivo.
 */	
void escribir_preso_bin(FILE* archivo_destino, preso_t preso){
	fwrite (&preso, sizeof(preso_t), 1, archivo_destino);
}

/*Pre: La funcion recibe un puntero a un archivo abierto de texto a modo escritura, y una variable del tipo preso_t la cual debe tener
 *	   su campo nombre completo.
 *Post: La funcion escribira el campo nombre de la variable recibida dentro del archivo de texto.
 */
void escribir_nombre_preso_txt (FILE* archivo_destino, preso_t preso){
	fprintf(archivo_destino, "%s\n", preso.nombre); 
}

/*Pre: La funcion debe recibir un puntero a un archivo de texto abierto a modo lectura, y un string  que debe tener tamano maximo
	   200 caracteres.
 *Post: Leera  un nombre de reclusos dentro del archivo, y lo almacenara en el string recibido. Devuelve a su vez la cantidad
 *		de nombres leidos
 */
int leer_nombre_preso_txt (FILE* archivo, char nombre[MAX_NOMBRE]){
	return fscanf(archivo, "%[^\n]\n", nombre);
}

/*Pre: La funcion debe recibir dos variables del tipo preso_t con sus campos nombre inicializados.
 *Post: Devolvera un numero mayor a cero si el nombre del primer preso es mayor alfabeticamente al del segundo
 *		un numero menor a cero si el nombre del primero es menor al del segundo, y 0 si ambos strings
 *		son iguales.
 */
int comparar_presos(preso_t preso_1, preso_t preso_2){
	int comparacion = strcmp (preso_1.nombre, preso_2.nombre);
	return comparacion;
}

/*Pre: La funcion debe ecibir dos punteros a archivos binarios abiertos a modo lectura y un tercer puntero a un archivo de texto
 *		   abierto a modo escritura.
 *Post: La funcion realizara una diferencia simetrica entre ambos archivos binarios, y el campo nombre de los presos
 *		que no tengan en comun ambos archivos se escribira en el archivo de texto.
 */
void diferencia_simetrica_crucio_imperius (FILE* presos_crucio, FILE* presos_imperius, FILE* presos_perdonables){
 	
 	preso_t preso_1, preso_2;

 	leer_preso_bin ( presos_crucio, &preso_1);
 	leer_preso_bin ( presos_imperius, &preso_2);

  	while ( (!feof(presos_crucio)) && (!feof(presos_imperius)) ){
  		
  		if (comparar_presos (preso_1, preso_2) == 0 ){
  			leer_preso_bin (presos_crucio, &preso_1);
  			leer_preso_bin (presos_imperius, &preso_2);
  		}
  		else if (comparar_presos (preso_1, preso_2) < 0){
  			escribir_preso_bin (presos_perdonables, preso_1);
  			leer_preso_bin (presos_crucio, &preso_1);
  		}
  		else {
  			escribir_preso_bin (presos_perdonables, preso_2);
  			leer_preso_bin (presos_imperius, &preso_2);
  		}
 	}

 	while (!feof(presos_crucio)){
 		escribir_preso_bin (presos_perdonables, preso_1);
  		leer_preso_bin (presos_crucio, &preso_1);	
 	}

 	while (!feof(presos_imperius)){
 		escribir_preso_bin (presos_perdonables, preso_2);
  		leer_preso_bin (presos_imperius, &preso_2);
 	}
}

/*Pre: La funcion debe recibir dos strings, uno representado la fecha elegida por el usuario en formato aaaamm, y otro vacio. 
 *Post: La funcion concatenara la fecha recibida como parametro junto con el codigo previo y la extension requerida, para nombrar un
 *		archivo de texto, y almacenara el nuevo string dentro de la segunda variable recibida como parametro
 */
void nombrar_archivo_liberados (char fecha_str_argv[], char nombre_liberados_txt []){
	
	strcpy (nombre_liberados_txt, CODIGO_LIBERADOS);
	strcat (nombre_liberados_txt, fecha_str_argv);
	strcat (nombre_liberados_txt, EXTENSION_TXT);
}

int generar_archivo_perdonables (char nombre_perdonables []){
	
	FILE* presos_crucio = fopen("crucio.dat","r");

	if (presos_crucio == NULL){
		return ERROR_ARCHIVOS;
	}

	FILE* presos_imperius = fopen("imperius.dat","r");
	
	if (presos_imperius == NULL){
		fclose (presos_crucio);
		return ERROR_ARCHIVOS;
	}

	FILE* presos_perdonables = fopen (nombre_perdonables, "w");

	if (presos_perdonables == NULL){
		fclose (presos_crucio);
		fclose (presos_imperius);
		return ERROR_ARCHIVOS;
	}

	diferencia_simetrica_crucio_imperius (presos_crucio, presos_imperius, presos_perdonables);
	
	fclose (presos_imperius);
	fclose (presos_crucio);
	fclose (presos_perdonables);
	
	return RETORNO_EXITOSO;
}

/*Pre: La funcion debe recibir dos punteros a archivos, el primero siendo un archivo binario abierto a modo lectura,
 * 	   y el segundo debe ser un archivo de texto abierto a modo escritura. Ademas debe recibir un entero representando la fecha
 *	   en la que se quiere liberar a los presos que cumplan con el parametro conducta recibido en formato de caracter.
 *Post: La funcion escribira el nombre de los presos dentro del archivo binario cuya fecha de liberacion sea previa o igual a la
 *	    recibida como parametro, y que ademas cuya conducta sea mejor o igual a la recibida como parametro.
 */
void generar_liberados (FILE* perdonables, FILE* liberados, int fecha, char conducta){

	preso_t preso_liberable ;
	leer_preso_bin (perdonables, &preso_liberable);

	while (!feof(perdonables)){
		
		
		int fecha_preso = atoi(preso_liberable.fecha);

		switch (conducta){
			
			case CONDUCTA_BUENA:	
			if ( (fecha_preso <= fecha) && (preso_liberable.conducta == CONDUCTA_BUENA) ){
				escribir_nombre_preso_txt (liberados, preso_liberable);
			}
			break;
			
			case CONDUCTA_REGULAR:
			if	( (fecha_preso <= fecha) && (preso_liberable.conducta != CONDUCTA_MALA) ){
				escribir_nombre_preso_txt (liberados, preso_liberable);
			}
			break;

			case CONDUCTA_MALA:
			if	( fecha_preso <= fecha){
				escribir_nombre_preso_txt (liberados, preso_liberable);
			}
			break;
		}

		leer_preso_bin (perdonables, &preso_liberable);
	}
}


int liberar_presos (char nombre_perdonables [], int fecha, char fecha_str [], char conducta){
		
	char nombre_liberados_txt [MAX_NOMBRE];
	nombrar_archivo_liberados (fecha_str, nombre_liberados_txt);
	
	if(!fopen(nombre_liberados_txt,"r")){
		FILE* perdonables = fopen (nombre_perdonables, "r");
		if (perdonables == NULL){
			return ERROR_ARCHIVOS;
		}
	
		FILE* liberados = fopen (nombre_liberados_txt, "w");
		if (liberados == NULL){
			fclose(perdonables);
			return ERROR_ARCHIVOS;
		}

		generar_liberados (perdonables, liberados, fecha, conducta);
		fclose (perdonables);
		fclose (liberados);

	}
	return RETORNO_EXITOSO;
}	

/*Pre: La funcion debe recibir un puntero a un archivo de texto abierto a modo lectura, representando los presos liberados en
 *	   determinada fecha y dos punteros a dos archivos binarios abiertos tambien a modo lectura, que representan
 *     todos los presos que realizaron el maleficio crucio e imperius
 *Post: La funcion actualizara los archivos binarios, eliminando de ellos los presos cuyo campo nombre aparezca dentro 
 *		del archivo de presos liberados.
 */
int generar_actualizados (FILE* liberados, FILE* crucio, FILE* imperius){

	FILE* crucio_aux = fopen("crucio_aux.dat", "w");
	if(crucio_aux == NULL){
		return ERROR_ARCHIVOS;
	}

	FILE* imperius_aux = fopen("imperius_aux.dat", "w");
	if (imperius_aux == NULL){
		return ERROR_ARCHIVOS;
	}
	
	preso_t preso_crucio;
	preso_t preso_imperius;
	char preso_libre [MAX_NOMBRE];
	int leidos = leer_nombre_preso_txt (liberados, preso_libre);

	leer_preso_bin (crucio, &preso_crucio);
	leer_preso_bin (imperius, &preso_imperius);
	
	
	while ( (!feof (crucio)) && (!feof (imperius)) && (leidos > 0) ){
		
		if (comparar_presos(preso_crucio, preso_imperius) == 0){
			escribir_preso_bin (crucio_aux, preso_crucio);
			escribir_preso_bin (imperius_aux, preso_imperius);
			leer_preso_bin (crucio, &preso_crucio);
			leer_preso_bin (imperius, &preso_imperius);
		}
		else if (comparar_presos(preso_crucio, preso_imperius) < 0){
				if (strcmp (preso_crucio.nombre, preso_libre) == 0){
					leer_preso_bin (crucio, &preso_crucio);
					leidos = leer_nombre_preso_txt (liberados, preso_libre);
				}
				else if (strcmp (preso_crucio.nombre, preso_libre) < 0){
					escribir_preso_bin (crucio_aux, preso_crucio);
					leer_preso_bin (crucio, &preso_crucio);
				}
				else{
					leidos = leer_nombre_preso_txt (liberados, preso_libre);
				} 
		}
		else {
			if (strcmp (preso_imperius.nombre, preso_libre) == 0){
				leer_preso_bin (imperius, &preso_imperius);
				leidos = leer_nombre_preso_txt (liberados, preso_libre);
			}
			else if (strcmp (preso_imperius.nombre, preso_libre) < 0){
				escribir_preso_bin (imperius_aux, preso_imperius);
				leer_preso_bin (imperius, &preso_imperius);
			}
			else{
				leidos = leer_nombre_preso_txt (liberados, preso_libre);
			} 	
		}
	}
	
	while ( (!feof(crucio)) && (leidos > 0) ){
		if (strcmp (preso_crucio.nombre, preso_libre) == 0){
			leer_preso_bin (crucio, &preso_crucio);
			leidos = leer_nombre_preso_txt (liberados, preso_libre);
		}
		else if (strcmp (preso_crucio.nombre, preso_libre) < 0){
			escribir_preso_bin (crucio_aux, preso_crucio);
			leer_preso_bin (crucio, &preso_crucio);
		}
		else{
			leidos = leer_nombre_preso_txt (liberados, preso_libre);
		} 

	}
	while ( (!feof(imperius)) && (leidos > 0) ){
		if (strcmp (preso_imperius.nombre, preso_libre) == 0){
			leer_preso_bin (imperius, &preso_imperius);
			leidos = leer_nombre_preso_txt (liberados, preso_libre);
		}
		else if (strcmp (preso_imperius.nombre, preso_libre) < 0){
			escribir_preso_bin (imperius_aux, preso_imperius);
			leer_preso_bin (imperius, &preso_imperius);
		}
		else{
			leidos = leer_nombre_preso_txt (liberados, preso_libre);
		} 
	}
	while (!feof(crucio)){
		
		escribir_preso_bin (crucio_aux, preso_crucio);
		leer_preso_bin (crucio, &preso_crucio);
	}
	while (!feof(imperius)){
		
		escribir_preso_bin (imperius_aux, preso_imperius);
		leer_preso_bin (imperius, &preso_imperius);
	}

	fclose (crucio_aux);
	fclose (imperius_aux);
	return RETORNO_EXITOSO;
}

int actualizar_archivos (int fecha, char fecha_str[]){

	char nombre_liberados_txt [MAX_NOMBRE];
	nombrar_archivo_liberados (fecha_str, nombre_liberados_txt);
	int se_actualizo;
	FILE* liberados_rand = fopen (nombre_liberados_txt, "r");
	if (liberados_rand == NULL){
		fclose(liberados_rand);
		se_actualizo = ERROR_ARCHIVOS;
	}

	FILE* imperius = fopen("imperius.dat", "r");
	if (imperius == NULL){
		fclose(liberados_rand);
		se_actualizo = ERROR_ARCHIVOS;
	}

	FILE* crucio = fopen ("crucio.dat", "r");
	if (crucio == NULL){
		fclose(liberados_rand);
		fclose(imperius);
		se_actualizo = ERROR_ARCHIVOS;
	}

	se_actualizo = generar_actualizados (liberados_rand, crucio, imperius);
	fclose(liberados_rand);
	fclose(imperius);
	fclose(crucio);
	
	if (remove("crucio.dat"))
		se_actualizo = ERROR_ARCHIVOS;
	if (remove("imperius.dat"))
		se_actualizo = ERROR_ARCHIVOS;
	if (rename ("crucio_aux.dat","crucio.dat"))
		se_actualizo = ERROR_ARCHIVOS;
	if (rename("imperius_aux.dat","imperius.dat"))
		se_actualizo = ERROR_ARCHIVOS;
	
	return se_actualizo;
} 

/*Pre: La funcion debe recibir un puntero a un archivo de texto abierto a modo lectura el cual contendra los nombres de los
 *	   presos liberados en cierta fecha.
 *Post: La funcion imprimira por pantalla todos los nombres de los presos que aparezcan en el archivo recibido
 *	    y ademas imprimira la cantidad de nombres que imprimio
 */	
void imprimir_presos (FILE* liberados){
	
	char nombre_preso_liberado [MAX_NOMBRE];
	int leidos = leer_nombre_preso_txt (liberados, nombre_preso_liberado);
	int contador_liberados = 1;
	
	while (leidos > 0){
		printf("\n");
		printf("%i) %s\n", contador_liberados, nombre_preso_liberado);
		printf("\n");
		leidos = leer_nombre_preso_txt (liberados, nombre_preso_liberado);
		contador_liberados ++;
	}
	contador_liberados --;
	printf("[Se liberaron %i presos]\n", contador_liberados);
	printf("\n");
}

int mostrar_presos_liberados (char fecha_str[]){
	
	char nombre_archivo [MAX_NOMBRE];
	nombrar_archivo_liberados (fecha_str, nombre_archivo);
	
	FILE* liberados = fopen (nombre_archivo, "r");
		if (liberados == NULL){
		return ERROR_ARCHIVOS;
	}
	
	imprimir_presos (liberados);
	fclose(liberados);
	return RETORNO_EXITOSO;
}

void mostrar_ayuda (){
	
	printf("\n");
	
	printf("     / Para utilizar el programa, debe ingresar uno de los siguientes comandos luego de escribir ./azkaban : \n ");

	printf("\n");
	
	printf(" * '%s <nombre_archivo>' : Se creara un archivo con los presos a los cuales es posible perdonar,y \n" ,COMANDO_PERDONABLES); 
	printf(" se lo nombrara como el usuario desee \n");
	
	printf("\n");

	printf(" * '%s <nombre_archivo>.dat aaaamm X' : Se accedera al archivo generado por el comando perdonables, y se generara  \n",COMANDO_LIBERAR ); 
	printf("  un nuevo archivo con los presos cuya fecha de liberacion sea anterior o igual a la fecha ingresada por el usuario en formato aaaamm,\n");
	printf("  y que ademas su conducta sea mejor o igual que requerida por el usuario. La conducta se debe ingresar con un caracter que \n" );
	printf("  la represente, y estos deben ser: B- Buena > R - Regular > M - Mala. El archivo generado sera un archivo de texto llamado\n" );
	printf("  liberados_aaaamm, siendo aaaamm nuevamente la fecha ingresada por el usuario \n");

	printf("\n");

	printf(" * '%s aaaamm' : Se eliminaran de los archivos crucio e imperius los reclusos que han sido liberados\n ",COMANDO_ACTUALIZAR ); 
	printf("  en la fecha ingresada por el usuario, en formato aaaamm\n");	 

	printf("\n");

	printf(" * '%s aaaamm': Se mostraran los reclusos liberados en la fecha mensual ingresada por el usuario en formato aaaamm \n ",COMANDO_MOSTRAR_LIB );
	
	printf("\n");

	printf(" * '%s': Se mostrara nuevamente al usuario este mismo texto para asistirlo\n",COMANDO_AYUDA);
	printf("\n");
}

