#ifndef __CARCEL_H__
#define __CARCEL_H__

#define MAX_NOMBRE 200
#define MAX_FECHA 7

typedef struct preso{
	char nombre [MAX_NOMBRE];
	unsigned int edad;
	char conducta;
	unsigned int pabellon;
	unsigned int celda;
	char fecha [MAX_FECHA];
	int maldicion_realizada;
} preso_t;

	
 /*Pre:  La funcion debe recibir un string de caracteres que representa el nombre que el usuario  desea llamar a su archivo perdonables
  * 	 Debe haber dentro del mismo directorio del archivo dos archivos binarios llamados crucio.dat e imperius.dat que representan
  *		 los presos que realizaron dichos maleficios	
  *Post: Se generara un archivo binario con el nombre elegido por el usuario el cual dentro contendra a los presos que pueden
  * 	 ser "perdonados" por haber realizado solo uno de los maleficios
  */
int generar_archivo_perdonables ( char nombre_perdonables []);

/*Pre: Se debe haber ejecutado el comando perdonables con anterioridad al menos una vez, para que dentro del mismo directorio se encuentre 
 *	   el archivo perdonables.dat, y debe recibir como parametro un string con el nombre exacto (con su extension) con el que se decidio
 *	   llamarlo. Ademas debe recibir una fecha en formato string y entero, la cual debe estar en formato aaaamm y debe ser positiva.
 *	   Debe recibir por ultimo un caracter representando la conducta minima requerida para liberar presos, el cual debe ser B, R o M, 
 *	   o de otra forma no funcionara
 *Post: Se creara un archivo de texto el cual incluya a los reclusos que fueron liberados, cumpliendo las condiciones elegidas por el usuario,
 *		Tanto su fecha de liberacion, como su conducta
 */
int liberar_presos (char nombre_perdonables [], int fecha, char fecha_str [], char conducta);

/*Pre: Se debe haber ejecutado exitosamente el comando liberar ya que es necesario que exista un archivo de liberados dentro del mismo
 *     directorio. Recibe un string de fecha positiva en formato aaaamm y esa fecha debe coincidir con la de algun archivo de liberados
 *	   ya generado 
 *Post: Actualizara los archivos de crucio.dat e imperius.dat, eliminando de estos los reclusos que ya se liberaron
 */

int actualizar_archivos (int fecha, char fecha_str[]);

/*Pre: Se debe haber ejecutado exitosamente el comando liberar ya que es necesario que exista un archivo de liberados dentro del mismo
 *     directorio. Recibe un string de fecha positiva en formato aaaamm y esa fecha debe coincidir con la de algun archivo de liberados
 *	   ya generado 

 *Post: Mostrara por pantalla todos los reclusos que fueron liberados en una determinada fecha, elegida por el usuario.
 */
int mostrar_presos_liberados (char fecha_str[]);

/*Pre: Debido a que no recibe ningun parametro, no es necesario cumplir condiciones para esta funcion
 *Post:	Le mostrara al usuario la lista de comandos ejecutables dentro del programa, y le especificara
 *		que hace cada uno
 */
void mostrar_ayuda ();




#endif /* __LABERINTO_H__ */