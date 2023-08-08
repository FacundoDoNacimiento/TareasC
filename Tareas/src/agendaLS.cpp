#include "../include/agendaLS.h"

struct rep_agendaLS {
    TEvento evento ;
    TAgendaLS sig ;
};

TAgendaLS crearAgendaLS() {
    TAgendaLS ptr = NULL;
    return ptr;
}

void agregarEnAgendaLS(TAgendaLS &agenda, TEvento evento) {
    TAgendaLS nuevo = new rep_agendaLS;
    nuevo->evento = evento; //cambio por copiarEvento
    if ((agenda == NULL) || (compararTFechas(fechaTEvento(evento),fechaTEvento(agenda->evento)) != 1)){
        nuevo->sig = agenda;
        agenda = nuevo;
    } else {
        TAgendaLS iter = agenda;
        while ((iter->sig != NULL) && (compararTFechas(fechaTEvento(evento),fechaTEvento(iter->sig->evento)) == 1)){
            iter = iter->sig;  
        }
        nuevo->sig = iter->sig;
        iter->sig = nuevo;
    }
}


void imprimirAgendaLS(TAgendaLS agenda) {
    TAgendaLS iter = agenda;
    while (iter !=NULL){
        imprimirTEvento(iter->evento);
        iter = iter->sig;
    }
    //delete iter;
}

void liberarAgendaLS(TAgendaLS &agenda) {
    while (agenda != NULL){
        TAgendaLS aBorrar = agenda;
        agenda = agenda->sig;
        liberarTEvento(aBorrar->evento);
        delete aBorrar;
    }
    delete agenda;
    agenda = NULL; /*Agregado recien*/
}

bool esVaciaAgendaLS(TAgendaLS agenda){
     return (agenda == NULL);
}

TAgendaLS copiarAgendaLS(TAgendaLS agenda){

    TAgendaLS res, copia;
    if (esVaciaAgendaLS(agenda)){
        return NULL;
    }else{
        res = new rep_agendaLS;        
        res->evento = copiarTEvento(agenda->evento);
        res->sig = NULL;
        copia = res;
        agenda = agenda->sig;
        while (agenda != NULL){
            TAgendaLS aux = new rep_agendaLS;
            aux->sig = NULL;
            aux->evento = copiarTEvento(agenda->evento);
            res->sig = aux;
            res = res->sig;
            agenda = agenda->sig;
        }
        return copia;
    }

}


bool estaEnAgendaLS(TAgendaLS agenda, int id) {
    bool aux = false;
    if (!(esVaciaAgendaLS(agenda))){
        while ((agenda != NULL) && (!(aux)) ){
            aux = (idTEvento(agenda->evento) == id);
            agenda = agenda->sig;
        }
    }
    return aux;   
}

TEvento obtenerDeAgendaLS(TAgendaLS agenda, int id) {
    TEvento evento = NULL;
    bool aux = false;
    while ((agenda != NULL) && (!(aux))){
        if (idTEvento(agenda->evento) == id){
            evento = agenda->evento;
            aux = true;
        }
        agenda = agenda->sig;
    }
    return evento;
}


void posponerEnAgendaLS(TAgendaLS &agenda, int id, nat n) {
    TEvento eventoAPosponer = obtenerDeAgendaLS(agenda,id);
    posponerTEvento(eventoAPosponer,n);
    TAgendaLS iter = agenda;
    TAgendaLS aux = iter;
    bool p = true;
    if (idTEvento(agenda->evento) == id){
        agenda = agenda->sig;
        aux->sig = NULL;
        iter = agenda;
    }else{
        while (idTEvento(iter->sig->evento) != id){
            iter = iter->sig;
        }
        aux = iter->sig;
        if (aux->sig != NULL){
            if (compararTFechas(fechaTEvento(aux->evento),fechaTEvento(aux->sig->evento)) != 1){
                p = false;
            }else{
                p = true;
            }
        }if (p){
            iter->sig = aux->sig;
            aux->sig = NULL;
            iter = iter->sig;
        }
    }
    if (p){
        while ((iter->sig != NULL) && (compararTFechas(fechaTEvento(aux->evento),fechaTEvento(iter->sig->evento)) == 1 )){
            iter = iter->sig;
        }
        if (iter->sig != NULL){
            aux->sig = iter->sig;
            iter->sig = aux;
        }else{
            iter->sig = aux;
        }
    }
}

void imprimirEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    while (agenda != NULL){
        if (compararTFechas(fechaTEvento(agenda->evento),fecha) == 0 ){
            imprimirTEvento(agenda->evento);
        }
        agenda = agenda->sig;
    }
}

bool hayEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    while ((agenda != NULL) && ((compararTFechas(fechaTEvento(agenda->evento), fecha)) != 0)){
            agenda = agenda->sig;
        }
    return (agenda != NULL);
}

void removerDeAgendaLS(TAgendaLS &agenda, int id) {
    TAgendaLS aux;
    if (idTEvento(agenda->evento) == id){
        aux = agenda;
        agenda = agenda->sig;
        liberarTEvento(aux->evento);
        delete aux;
    }else{
        TAgendaLS iter = agenda;
        while ((iter->sig != NULL) && (idTEvento(iter->sig->evento) != id)){
            iter = iter->sig;
        }
        aux = iter->sig;
        if (iter->sig == NULL){
            iter->sig = NULL;
        }else{
            iter->sig = aux->sig;
        }
        aux->sig = NULL;
        liberarTEvento(aux->evento);
        delete aux;
    }
}


///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

TEvento primerEventoAgendaLS(TAgendaLS agenda){
    return agenda->evento;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
