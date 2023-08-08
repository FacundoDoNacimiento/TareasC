#include "../include/aplicaciones.h"
#include "../include/colaDePrioridadPersona.h"

void listarEnOrden(TTablaPersonas t, char** nombres, nat n){
    nat i = 0;
    TColaDePrioridadPersona c = crearCP(MAX_ID);
    while (i < n){
        if (perteneceATTablaPersonas(t,nombres[i])){
            insertarEnCP(copiarTPersona(obtenerPersonaDeTTablaPersonas(t,nombres[i])) ,c);
            eliminarPersonaDeTTablaPersonas(t,nombres[i]);
        }
        i++;
    }
    while (!estaVaciaCP(c)){
        imprimirTPersona(prioritaria(c));
        eliminarPrioritaria(c);
    }
    liberarCP(c);
}