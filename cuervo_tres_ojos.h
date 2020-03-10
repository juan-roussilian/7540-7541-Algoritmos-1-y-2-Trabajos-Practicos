#ifndef __CUERVO_TRES_OJOS_H__
#define __CUERVO_TRES_OJOS_H__

#define MAX_NOMBRE 50
#define MAX_DESCRIPCION 600

typedef struct vision {
    char protagonista[MAX_NOMBRE];
    char casa_protagonista[MAX_NOMBRE];
    char descripcion[MAX_DESCRIPCION];
    char epoca; // P - pasado, F - futuro
} vision_t;

typedef struct cuervo_tres_ojos {
    char nombre[MAX_NOMBRE];
    vision_t* visiones_del_pasado;
    vision_t* visiones_del_futuro;
    int cantidad_visiones_pasado;
    int cantidad_visiones_futuro;
} cuervo_tres_ojos_t;

typedef struct cuervo_aprendiz {
    char nombre[MAX_NOMBRE];
    vision_t* visiones_adquiridas;
    int cantidad_visiones;
} cuervo_aprendiz_t;

/*
 * Recibe el nombre del cuervo a invocar.
 * Creará la estructura cuervo_tres_ojos, reservando la memoria necesaria.
 * Devolverá la estructura con los topes de las visiones inicializados en 0.
 * En caso de no poder invocar al cuervo, devolverá NULL.
 */
cuervo_tres_ojos_t* invocar_cuervo(char* nombre);

/*
 * Recibe el nombre del aprendiz a invocar.
 * Creará la estructura cuervo_aprendiz, reservando la memoria necesaria.
 * Devolverá la estructura con el tope de las visiones inicializado en 0.
 * En caso de no poder invocar al aprendiz, devolverá NULL.
 */
cuervo_aprendiz_t* invocar_aprendiz(char* nombre);

/*
 * Agrega una vision al vector de visiones correspondiente.
 * Reservando la memoria necesaria para ella.
 * Devolverá 0 si pudo agregarla o -1 si no pudo.
 */
int agregar_vision(cuervo_tres_ojos_t* cuervo, vision_t vision);

/*
 * Transmitirá al aprendiz las visiones del pasado y del futuro del cuervo que sean 
 * transmisibles de acuerdo a la función recibida como parámetro.
 * En caso de que la visión a transmitir ya sea conocida por el aprendiz (repetida), 
 * no se agrega a las visiones del mismo.
 * Devolverá 0 si se transmitieron con eso, -1 en caso contrario
 */
int transmitir_visiones(cuervo_tres_ojos_t* cuervo, cuervo_aprendiz_t* aprendiz, bool (*es_transmisible)(vision_t));

/*
 * Mostrará por pantalla las visiones adquiridas por el aprendiz.
 * Una visión se listará sólo si la función recibida como parámetro lo permite.
 */
void listar_visiones_transmitidas(cuervo_aprendiz_t aprendiz, bool (*es_listable)(vision_t));

/*
 * Destruirá la estructura del cuervo, liberando la memoria reservada para él y sus visiones.
 * Devolverá  si pudo liberar lamemoria o -1 si no pudo.
 */
int destruir_cuervo(cuervo_tres_ojos_t* cuervo);

/*
 * Destruirá la estructura del aprendiz, liberando la memoria reservada para él y sus visiones.
 * Devolverá  si pudo liberar lamemoria o -1 si no pudo.
 */
int destruir_aprendiz(cuervo_aprendiz_t* aprendiz);

#endif /*__CUERVO_TRES_OJOS_H__*/