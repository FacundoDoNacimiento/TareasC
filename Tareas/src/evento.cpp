
#include "../include/evento.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 1 //////
///////////////////////////////////

struct rep_evento {
    /************ Parte 4.1 ************/
    /*Escriba el código a continuación */
    int id;
    char descripcion[MAX_DESCRIPCION];
    TFecha fecha;
    /****** Fin de parte Parte 4.1 *****/
};

TEvento crearTEvento(int id, const char descripcion[MAX_DESCRIPCION], TFecha fecha) {
    TEvento nuevoEvento = NULL;
    /************ Parte 4.2 ************/
    /*Escriba el código a continuación */
    nuevoEvento = new rep_evento;
    nuevoEvento->id=id;
    strcpy(nuevoEvento->descripcion, descripcion);
    nuevoEvento->fecha= fecha;
    /****** Fin de parte Parte 4.2 *****/
    return nuevoEvento;
}

void imprimirTEvento(TEvento evento) {  
    /************ Parte 4.3 ************/
    /*Escriba el código a continuación */
    printf("Evento %d: %s\n", evento->id, evento->descripcion);
    printf("Fecha: " ); //FECHA
    imprimirTFecha(fechaTEvento(evento));
    /****** Fin de parte Parte 4.3 *****/
}

void liberarTEvento(TEvento &evento) {
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    liberarTFecha(evento->fecha);
    delete evento;
    evento = NULL; 
    /****** Fin de parte Parte 4.4 *****/
}

int idTEvento(TEvento evento) {
    int res = 0;
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    if (evento != NULL ) {
        res = evento->id ;
    }
    /****** Fin de parte Parte 4.4 *****/
    return res;
}

TFecha fechaTEvento(TEvento evento) {
    TFecha fecha = NULL;
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    if (evento != NULL) {
        fecha = evento->fecha;
    }
    /****** Fin de parte Parte 4.4 *****/
    return fecha;
}

void posponerTEvento(TEvento &evento, int dias) {
    /************ Parte 4.5 ************/
    /*Escriba el código a continuación */
    if (dias > 0) {
        TFecha aux = fechaTEvento(evento);
        aumentarTFecha(aux,dias);
    }
    /****** Fin de parte Parte 4.5 *****/
}


/////////////////////////////////
////// FIN CÓDIGO TAREA 1 //////
/////////////////////////////////

/*-----------------------------*/

///////////////////////////
////// FUNCION NUEVA //////
///////////////////////////

// Retorna una copia del evento
TEvento copiarTEvento(TEvento evento) {
    TEvento eventoNuevo = NULL;
    if (evento != NULL){
        eventoNuevo = new rep_evento;
        eventoNuevo->id = idTEvento(evento);
        eventoNuevo->fecha = copiarTFecha (evento->fecha); 
        strcpy(eventoNuevo->descripcion, evento->descripcion);
    }
    return eventoNuevo;
}
