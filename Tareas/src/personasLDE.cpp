#include "../include/personasLDE.h"

struct nodoDoble{
    TPersona persona;
    nodoDoble * sig;
    nodoDoble * ant;
};

struct rep_personasLDE {
    int cantidad;
    nodoDoble * inicio;
    nodoDoble * final;
};

typedef nodoDoble * LDE;

TPersonasLDE crearTPersonasLDE(){
    TPersonasLDE c = new rep_personasLDE;
    c->inicio = NULL;
    c->final = NULL;
    c->cantidad = 0;
    return c; 
}

void insertarTPersonasLDE(TPersonasLDE &personas, TPersona persona, nat pos){
    personas->cantidad = personas->cantidad + 1;
    LDE nuevo = new nodoDoble;
    nuevo->persona = persona; //copiar Persona
    if (personas->final == NULL){ //es decir, es vacia
        nuevo->sig = nuevo->ant = NULL;
        personas->inicio = personas->final = nuevo;
    }else{
        if (pos == 1){ //AL INICIO
            nuevo->sig = personas->inicio;
            nuevo->ant = NULL;
            personas->inicio->ant = nuevo;
            personas->inicio = nuevo;
            
        }else{
            LDE iter = personas->inicio;
            nat count = 1;
            while ((iter->sig != NULL) && (pos > count)){
                iter = iter->sig;
                count = count + 1;
            }
            if (pos == count){ //EN EL MEDIO
                nuevo->sig = iter;
                nuevo->ant = iter->ant;
                iter->ant->sig = nuevo;
                iter->ant = nuevo;
            }
            else{ 
                //AL FINAL
                iter->sig = nuevo;
                nuevo->sig = NULL;
                nuevo->ant = iter;
                personas->final = nuevo;    
            }
        }
        

    }
    
}

void liberarTPersonasLDE(TPersonasLDE &personasLDE){
    if (personasLDE->final != NULL){ /*Reviso que la lista no sea vacia*/
        LDE aux = personasLDE->inicio;
        personasLDE->inicio = personasLDE->final = NULL; //?
        while (aux != NULL){
            LDE n2k = aux;
            aux = aux->sig;
            liberarTPersona(n2k->persona);
            delete n2k;
        }
    }
    delete personasLDE;
    personasLDE = NULL;
}

void imprimirTPersonasLDE(TPersonasLDE personas){
    LDE iter = personas->inicio;
    while (iter != NULL){
        imprimirTPersona(iter->persona);
        iter = iter->sig;
    }
}

nat cantidadTPersonasLDE(TPersonasLDE personas){
    return personas->cantidad;
}

void eliminarInicioTPersonasLDE(TPersonasLDE &personas){
    if (personas->cantidad != 0){
        
        LDE q = personas->inicio;
        if (personas->cantidad == 1){
            personas->inicio = personas->final = NULL;

        }else{
            personas->inicio = personas->inicio->sig;
            personas->inicio->ant = NULL;
            q->sig = NULL;
        }
        liberarTPersona(q->persona);
        delete q;
        q=NULL;
        personas->cantidad--;        
    }
}

void eliminarFinalTPersonasLDE(TPersonasLDE &personas){
    if (personas->inicio != NULL){
        if (personas->inicio == personas->final){
            LDE aux = personas->inicio;
            personas->inicio = personas->final = NULL;
            liberarTPersona(aux->persona);
            delete aux;
            if (personas->cantidad !=0){
                personas->cantidad = personas->cantidad - 1; 
            }
        }else{
            LDE aux = personas->final;
            aux->ant->sig = NULL;
            personas->final = aux->ant;
            aux->ant = NULL;
            liberarTPersona(aux->persona);
            delete aux;
            personas->cantidad = personas->cantidad - 1; 
        }
    }
}

bool estaEnTPersonasLDE(TPersonasLDE personas, nat id){
    LDE iter = personas->inicio;
    if (personas->final != NULL){
        while ((iter != NULL) && (idTPersona(iter->persona) != id)){
            iter = iter->sig;
        }
        return (iter != NULL);
    }else{
        return false;
    }
}

TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id){
    LDE iter = personas->inicio;
    if (personas->final != NULL){
        while ((iter != NULL) && (idTPersona(iter->persona) != id)){
            iter = iter->sig;
        }
        if (iter != NULL){
            return iter->persona;
        }else{
            return NULL;
        }
    }else{
        return NULL;
    }
}

TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2){
    TPersonasLDE res = new rep_personasLDE;
    res->inicio = NULL;
    res->final = NULL;
    if ((personas1->final != NULL) && (personas2->final != NULL)){
        res->inicio = personas1->inicio;
        personas1->final->sig = personas2->inicio;
        personas2->inicio->ant = personas1->final;
        res->final = personas2->final;
        res->cantidad = personas1->cantidad + personas2->cantidad;
    }else if ((personas1->final != NULL) && (personas2->final == NULL)){
        res->inicio = personas1->inicio;
        res->final = personas1->final;
        res->cantidad = personas1->cantidad;
    }else if ((personas1->final == NULL) && (personas2->final != NULL)){
        res->inicio = personas2->inicio;
        res->final = personas2->final;
        res->cantidad = personas2->cantidad;
    }
    personas1->inicio = NULL;
    personas2->inicio = NULL;
    personas1->final = NULL;
    personas2->final = NULL;
    liberarTPersonasLDE(personas1);
    liberarTPersonasLDE(personas2);
    return res;
}

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void insertarInicioDeTPersonasLDE(TPersonasLDE &personas, TPersona persona){
    LDE nuevo = new nodoDoble;
    nuevo->persona =persona;
    nuevo->ant = NULL;
    if (personas->inicio == NULL){
        nuevo->sig = NULL;
        personas->final = nuevo;
    }else{
        nuevo->sig = personas->inicio;
        personas->inicio->ant = nuevo;
    }
    personas->inicio = nuevo;
    personas->cantidad = personas->cantidad + 1;
}

void insertarFinalDeTPersonasLDE(TPersonasLDE &personas, TPersona persona){    
    LDE nuevo = new nodoDoble;
    nuevo->persona = persona;
    nuevo->sig = NULL;
    if (personas->inicio == NULL){
        nuevo->ant = NULL;
        personas->inicio = nuevo;
    }else{
        nuevo->ant = personas->final;
        personas->final->sig = nuevo;
    }   
    personas->final = nuevo;
    personas->cantidad = personas->cantidad + 1;
}

TPersona obtenerInicioDeTPersonasLDE(TPersonasLDE personas){
    return personas->inicio->persona;
}

TPersona obtenerFinalDeTPersonasLDE(TPersonasLDE personas){
    return personas->final->persona;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void eliminarPersonaConNombreTPersonasLDE(TPersonasLDE &personas, const char nombre[100]){
    if ((personas->inicio != NULL) && (strcmp(nombre,nombreTPersona(personas->inicio->persona)) == 0)){
        eliminarInicioTPersonasLDE(personas);
    }else if ((personas->final != NULL) && (strcmp(nombre,nombreTPersona(personas->final->persona)) == 0)){
        eliminarFinalTPersonasLDE(personas);
    }else{
    LDE q = personas->inicio;
    while ((q != NULL) && (strcmp(nombre,nombreTPersona(q->persona)) != 0)){
        q = q->sig;
    }
    if (q!= NULL){
        if (q->ant != NULL){
            q->ant->sig = q->sig;
        }
        if (q->sig != NULL){
            q->sig->ant = q->ant;
        }
        q->sig = NULL;
        q->ant = NULL;
        liberarTPersona(q->persona);
        delete q;
        q= NULL;
        personas->cantidad--;
    }
    }
}




bool estaPersonaConNombreEnTPersonasLDE(TPersonasLDE personas, const char nombre[100]){
    LDE iter = personas->inicio;
    while ((iter != NULL) && (strcmp(nombre,nombreTPersona(iter->persona)) != 0)){
        iter = iter->sig;
    }
    return (iter != NULL);
}

TPersona obtenerPersonaConNombreTPersonasLDE(TPersonasLDE personas, const char nombre[100]){
    LDE iter = personas->inicio;
    while ((iter != NULL) && (strcmp(nombre,nombreTPersona(iter->persona)) != 0)){
        iter = iter->sig;
    }
    return iter->persona;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
