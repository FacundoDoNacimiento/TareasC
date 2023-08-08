#include "../include/tablaPersonas.h"

struct rep_tablaPersonas {
    TPersonasLDE * h;
    int max;
    int cantidad;
};

nat funcionDeDispersion(const char nombre[100]){
    nat res = 0;
    int i = 0;
    while(i< 100 && nombre[i] != '\0'){
        res += int(nombre[i]);
        i++;
    }
    return res;
}

TTablaPersonas crearTTablaPersonas(int max){
    TTablaPersonas t = new rep_tablaPersonas;
    t->cantidad = 0;
    t->max = max;
    t->h = new TPersonasLDE[max + 1];
    for (int i = 0; i<=max; i++){
        t->h[i] = crearTPersonasLDE();
    }
    return t;
}

void insertarPersonaEnTabla(TTablaPersonas &tabla, TPersona persona){
    int pos = funcionDeDispersion(nombreTPersona(persona)) % tabla->max;
    insertarInicioDeTPersonasLDE(tabla->h[pos],persona);
}


void eliminarPersonaDeTTablaPersonas(TTablaPersonas &tabla, const char nombre[100]){
    int pos = funcionDeDispersion(nombre) % tabla->max;
    eliminarPersonaConNombreTPersonasLDE(tabla->h[pos],nombre);
}

bool perteneceATTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    int pos = funcionDeDispersion(nombre) % tabla->max;   
    return estaPersonaConNombreEnTPersonasLDE(tabla->h[pos],nombre);
}

TPersona obtenerPersonaDeTTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    int pos = funcionDeDispersion(nombre) % tabla->max;   
    return obtenerPersonaConNombreTPersonasLDE(tabla->h[pos],nombre);
}


void liberarTTablaPersonas(TTablaPersonas &tabla){
    for (int i = 0; i<= tabla->max; i++){
        liberarTPersonasLDE(tabla->h[i]);
    }
    delete [] tabla->h;
    delete tabla;
    tabla = NULL;
}


void imprimirTTablaPersonas(TTablaPersonas tabla){
    for(int i = 0; i<= tabla->max; i++){
        imprimirTPersonasLDE(tabla->h[i]);
    }
}