#include <stdio.h>


const int EDAD_MIN = 17;
const int INTEL_MIN = 0;
const int INTEL_MAX = 10;
const int FUERZA_MIN = 0;
const int FUERZA_MAX = 10;
#define MAGIA_BUENA  'B' 
#define MAGIA_REGULAR 'R'
#define MAGIA_MALA 'M'

/* Pre-Condiciones: El usuario debe responder a la pregunta de la funcion ingresando una sola tecla
   Post-Condiciones: La funcion lograra identificar lo que el usuario desea y llevar a cabo una accion en base a ese deseo */

void preguntar_primer_ingreso (char *respuesta_usuario){
	
	printf("\n Desea ingresar un alumno? (N para NO, cualquier otra tecla para SI) \n");
 
  scanf(" %c", respuesta_usuario);
}

/* Pre-Condiciones: El usuario debe responder a la pregunta de la funcion ingresando una sola tecla
   Post-Condiciones: La funcion lograra identificar lo que el usuario desea y llevar a cabo una accion en base a ese deseo */


void preguntar_otro_ingreso (char *respuesta_usuario){
	
	printf("\n Desea ingresar otro alumno? (N para NO, cualquier otra tecla para SI) \n");
 
    scanf(" %c", respuesta_usuario);
}
/* Pre-Condiciones: -El usuario debe ingresar SOLO numeros positivos para la edad ya que no existe edad negativa
/*					-El usuario debe ingresar los datos indicados en el orden en el que se piden
/*					-El usuario debe responder utilizando los rangos de valores indicados
/*  
/*   Post-condiciones	-El procedimiento lograra un exitosa asignacion de los datos pedidos a las variables del alumno ingresado */				
void pedir_datos (int *edad_ingresada, int *intel_ingresada, int *fuerza_ingresada, char *capacidad_m_ingresada){
	
	printf("\n Ingrese edad del alumno \n");

  	scanf(" %i",edad_ingresada);

  		if ( (*edad_ingresada) >= EDAD_MIN){
  			
  			printf("\n Ingrese inteligencia del alumno (del 0 al 10) \n");
  			scanf ("%i",intel_ingresada);
  			
  			while (	(*intel_ingresada > INTEL_MAX) || (*intel_ingresada < INTEL_MIN)	){
  				
  				printf("\n Por favor, reingresar inteligencia del alumno, de 0 a 10 \n");
  				scanf ("%i",intel_ingresada);
  			}
  			printf("\n Ingrese fuerza del alumno (del 0 al 10) \n ");
  			scanf ("%i",fuerza_ingresada); 

  			while ( (*fuerza_ingresada > FUERZA_MAX) || (*fuerza_ingresada < FUERZA_MIN)){

  				printf("\n Por favor, reingresar fuerza del alumno, de 0 a 10 \n");
  				scanf ("%i",fuerza_ingresada);
  			}
			printf("\n Ingrese la capacidad magica del alumno (B-Buena,R-Regular,M-mala) \n ");
			scanf (" %c", capacidad_m_ingresada);

			while (  ( (*capacidad_m_ingresada) != MAGIA_BUENA) && ( (*capacidad_m_ingresada) != MAGIA_MALA) && ( (*capacidad_m_ingresada) != MAGIA_REGULAR)  ) {
				
				printf("\n Por favor, reingresar capacidad magica del alumno, utilizando las teclas B, R o M \n ");
				
				scanf (" %c", capacidad_m_ingresada);
			}
        }
}
/*Pre-Condiciones: -El usuario debera cumplir las precondiciones del procedimiento "pedir_datos"
  Post-Conciciones: -El procedimiento (de ser invocado) asignara los datos del alumno recientemente ingresados
  					 a los datos del campeon, siendo este posicionado como nuevo campeon*/

 void asignar_datos_nuevo_campeon (int *intel_campeon, int *fuerza_campeon, char *capacidad_m_campeon, int *numero_campeon, int intel_ingresada, int fuerza_ingresada, char capacidad_m_ingresada, int contador){

		*intel_campeon = intel_ingresada;
		*fuerza_campeon = fuerza_ingresada;
		*capacidad_m_campeon = capacidad_m_ingresada;
		*numero_campeon = contador;
	}
/*Pre-Conciciones: -El usuario debera cumplir las precondiciones del procedimiento "pedir_datos" 
  Post-Condiciones: -El procedimiento comparara los datos del alumno ingresados con los del campeon actual y en el caso 
                     de que el recientemente ingresado tenga mejores atributos, invocara al procedimiento "asignar_datos_nuevo_campeon*/

void  elegir_campeon (int *intel_campeon, int *fuerza_campeon, char *capacidad_m_campeon, int *numero_campeon, int intel_ingresada, int fuerza_ingresada, char capacidad_m_ingresada, int contador){
	
	if (*intel_campeon < intel_ingresada){
		
		asignar_datos_nuevo_campeon	(intel_campeon, fuerza_campeon, capacidad_m_campeon, numero_campeon, intel_ingresada, fuerza_ingresada, capacidad_m_ingresada, contador);
	}
	
	else if (   (*intel_campeon == intel_ingresada) && (*fuerza_campeon < fuerza_ingresada)  ){
		
    	asignar_datos_nuevo_campeon	(intel_campeon, fuerza_campeon, capacidad_m_campeon, numero_campeon, intel_ingresada, fuerza_ingresada, capacidad_m_ingresada, contador);
    }
	
	else if ( (*intel_campeon == intel_ingresada) && (*fuerza_campeon == fuerza_ingresada) ){
		
		switch (capacidad_m_ingresada){

			case 'B': 
				
				if (  *capacidad_m_campeon != MAGIA_BUENA){
						
					asignar_datos_nuevo_campeon (intel_campeon, fuerza_campeon, capacidad_m_campeon, numero_campeon, intel_ingresada, fuerza_ingresada, capacidad_m_ingresada, contador);
				}
			break;
			
			case 'R': 

				if (*capacidad_m_campeon == MAGIA_MALA){

					asignar_datos_nuevo_campeon (intel_campeon, fuerza_campeon, capacidad_m_campeon, numero_campeon, intel_ingresada, fuerza_ingresada, capacidad_m_ingresada, contador);
				}
			break;	
		}					
	}			 
}
				
/*Pre-Condiciones: -El usuario debera haber ingresado todos los datos de la manera en la que se le fue indicada
  Post-Condiciones: -La funcion imprimira por pantalla (si lo hay) al campeon, por su numero de orden en el que fue ingresado
                    -Si no hay campeon, la funcion lo imprimira por pantalla*/

void imprimir_campeon (int numero_campeon){
	if (numero_campeon > 0){

  		printf("\n El campeón es el número %i :) \n", numero_campeon);
  		}
  
  else
	printf("\n No hay campeón :( \n");
  		}
  

/*Pre-Condiciones: -Para que la funcion "sumar_contador" sea invocada, el usuario debe ingresar al menos
					un alumno
  Post-Condiciones: - La funcion le suma uno a la variable contador, la cual como indica su nombre lleva la cuenta de los alumnos ingresados */


void sumar_contador (int *contador){

	(*contador) ++ ;
}
				
/*Pre-Condiciones: -Para que el programa funcione correctamente, se deben cumplir todas las precondiciones de las funciones
                    que este mismo utiliza
  Post-Condiciones: - El programa recibira alumnos ingresados (si se desean ingresar), y decidira cual de ellos es el mas apto para ser campeon y representar
                     a  su escuela en el torneo de los tres magos */                  


int main () {

	char capacidad_m_ingresada , capacidad_m_campeon = 'M' ;
	char respuesta_usuario;
	int  edad_ingresada; 
	int  intel_ingresada= -2, fuerza_ingresada= -2; 
	int  intel_campeon = -1 , fuerza_campeon=0;
	int  contador = 0 , numero_campeon = 0;


 	preguntar_primer_ingreso (&respuesta_usuario);
  


	while (respuesta_usuario != 'N'){
  		
  		sumar_contador (&contador);

  		pedir_datos (&edad_ingresada, &intel_ingresada, &fuerza_ingresada, &capacidad_m_ingresada);


  		elegir_campeon (&intel_campeon, &fuerza_campeon, &capacidad_m_campeon, &numero_campeon, intel_ingresada, fuerza_ingresada, capacidad_m_ingresada, contador);

  			
  	  	preguntar_otro_ingreso (&respuesta_usuario);		
  	}

       

	imprimir_campeon (numero_campeon);
    
  
 return 0;
}



