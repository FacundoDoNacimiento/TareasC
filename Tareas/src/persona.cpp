#include "../include/persona.h"

struct rep_persona {
    nat id;
    nat edad;
    char nombre[100];
    TAgendaLS agenda;
};

TPersona crearTPersona(nat id, nat edad, const char nombre[100], TAgendaLS agenda) {
    TPersona persona = new rep_persona;
    persona->id = id;
    strcpy(persona->nombre, nombre);
    persona->edad = edad;
    persona->agenda = agenda;
    return persona;
}

void liberarTPersona(TPersona &persona) {
    liberarAgendaLS(persona->agenda);
    delete persona;
    persona = NULL;
}

//Imprime a la persona utilizando printf e imprimeAgendaLS
void imprimirTPersona(TPersona persona) {
    printf("Persona %d: %s, %d años\n", persona->id, persona->nombre,persona->edad);
    imprimirAgendaLS(persona->agenda);
}

nat idTPersona(TPersona persona) {
    if (persona != NULL){
        return persona->id;
    }else{
        return 0;
    }
    
}

nat edadTPersona(TPersona persona) {
    if (persona != NULL){
        return persona->edad;
    }else{
        return 0;
    }
}

char* nombreTPersona(TPersona persona) {
    if (persona != NULL){
        return persona->nombre;
    }else{
        return NULL;
    }
}

TAgendaLS agendaTPersona(TPersona persona) {
    if (persona != NULL){
        return persona->agenda;
    }else{
        return NULL;
    }
}

void agregarEventoATPersona(TPersona &persona, TEvento evento) {
        agregarEnAgendaLS(persona->agenda, evento);
}

void posponerEventoEnTPersona(TPersona &persona, int id, nat n) {
    if (!(esVaciaAgendaLS(persona->agenda))){
        posponerEnAgendaLS(persona->agenda, persona->id, n);
    }
    
}

void removerEventoDeTPersona(TPersona &persona, int id) {
    if (!(esVaciaAgendaLS(persona->agenda))){
       removerDeAgendaLS(persona->agenda, id); 
    }
}

bool estaEnAgendaDeTPersona(TPersona persona, int id) {
    bool aux = estaEnAgendaLS(persona->agenda, id);
    return aux;
}

TEvento obtenerDeAgendaDeTPersona(TPersona persona, int id) {
    TEvento aux = obtenerDeAgendaLS(persona->agenda, id);
    return aux;
}

TPersona copiarTPersona(TPersona persona) {
    TPersona personaNueva = NULL;
    if (persona != NULL){
        personaNueva = new rep_persona;
        personaNueva->id = idTPersona(persona);
        personaNueva->edad = edadTPersona(persona);
        strcpy(personaNueva->nombre, persona->nombre);
        personaNueva->agenda = copiarAgendaLS(persona->agenda);
    }
    return personaNueva;
}
///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

TEvento primerEventoDeTPersona(TPersona persona){
    return primerEventoAgendaLS(persona->agenda);
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

