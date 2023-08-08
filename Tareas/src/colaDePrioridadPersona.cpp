#include "../include/colaDePrioridadPersona.h"
#include "../include/utils.h"
#include "../include/evento.h"



struct rep_colaDePrioridadPersona {
  int *vectorPos;
  TPersona * vectorPer;
  nat max;
  nat cantidad;
  bool invertirPrioridad;
};

TColaDePrioridadPersona crearCP(nat N) {
  TColaDePrioridadPersona c = new rep_colaDePrioridadPersona;
  c->max = N;
  c->cantidad = 0;
  c->vectorPos = new int[N + 1];
  c->vectorPer = new TPersona[N + 1];
  for (nat i = 0; i <= N ; i++){
    c->vectorPer[i] = NULL;
    c->vectorPos[i] = 0;
  }
  c->invertirPrioridad = false;
  return c;
} 

void invertirPrioridad(TColaDePrioridadPersona &cp) {
  if (cp->cantidad <= 1){
    cp->invertirPrioridad = !(cp->invertirPrioridad);
  }else{
    cp->invertirPrioridad = true;
    TColaDePrioridadPersona aux = crearCP(cp->max);
    nat i = 1;
    while (!estaVaciaCP(cp)){
      aux->vectorPer[i] = (cp->vectorPer[cp->cantidad]); //reciente
      aux->vectorPos[idTPersona(aux->vectorPer[i])] = i;
      aux->cantidad = i;
      i++;
      cp->cantidad--;
    }
    nat j = 1;
    while(!estaVaciaCP(aux)){
      cp->vectorPer[j] = (aux->vectorPer[j]);
      cp->vectorPos[idTPersona(cp->vectorPer[j])] = j;
      aux->cantidad--;
      cp->cantidad = j;
      j++;
    }
    /*queda vacia aux*/
    liberarCP(aux);
  }
}

void liberarCP(TColaDePrioridadPersona &cp) {
  delete []cp->vectorPos;
  for(nat i = 1; i<=cp->cantidad; i++ ){
    liberarTPersona(cp->vectorPer[i]);
  }
  cp->cantidad = 0;
  cp->max = 0;
  delete []cp->vectorPer;
  delete cp;
  cp = NULL;
}

void filtradoA(TColaDePrioridadPersona &cp, int pos){
  TPersona swp;
  int k = pos;
  if (cp->invertirPrioridad == false){
    while ((pos > 1) && ( compararTFechas(fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos])), (fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos/2])))) == -1)){
      swp = cp->vectorPer[pos];
      cp->vectorPer[pos] = cp->vectorPer[pos/2];
      cp->vectorPer[pos /2] = swp;
      cp->vectorPos[idTPersona(cp->vectorPer[pos])] = pos;
      cp->vectorPos[idTPersona(cp->vectorPer[pos/2])] = pos/2;
      pos = pos / 2;
    }
      if ((k > 1) && ( compararTFechas(fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos])), (fechaTEvento(primerEventoDeTPersona(cp->vectorPer[k-1])))) == -1)){
      swp = cp->vectorPer[k];
      cp->vectorPer[k] = cp->vectorPer[k-1];
      cp->vectorPer[k -1] = swp;
      cp->vectorPos[idTPersona(cp->vectorPer[k])] = k;
      cp->vectorPos[idTPersona(cp->vectorPer[k-1])] = k-1;
      //pos = pos-1;
    }
  }else{
    while ((pos > 1) && ( compararTFechas(fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos])), (fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos / 2])))) == 1)){
    swp = cp->vectorPer[pos];
    cp->vectorPer[pos] = cp->vectorPer[pos / 2];
    cp->vectorPer[pos / 2] = swp;
    cp->vectorPos[idTPersona(cp->vectorPer[pos])] = pos;
    cp->vectorPos[idTPersona(cp->vectorPer[pos/2])] = pos/2;
    pos = pos / 2;
  }
  }
}

bool estaLleno(TColaDePrioridadPersona cp){
  return (cp->cantidad == cp->max);
}

void insertarEnCP(TPersona persona, TColaDePrioridadPersona &cp){
  if (!estaLleno(cp)){
    cp->cantidad++;
    cp->vectorPer[cp->cantidad] = persona ;
    if (cp->cantidad > 1){
      cp->vectorPos[idTPersona(cp->vectorPer[cp->cantidad])] = cp->cantidad;
      filtradoA(cp,cp->cantidad);
    }else{
      cp->vectorPos[idTPersona(persona)] = 1;
    }
  }
}

bool estaVaciaCP(TColaDePrioridadPersona cp) {
  return (cp->cantidad == 0);
}

TPersona prioritaria(TColaDePrioridadPersona cp) {
  return cp->vectorPer[1];
} 

void filtradoD(TColaDePrioridadPersona &cp,int pos, int fin){
  TPersona swp ;
  bool seguir = true;
  int pos1= pos * 2;
  int pos2 = pos1 + 1;
  int posPrima;
  if (cp->invertirPrioridad == false){
    while ((pos1 <= fin) && (seguir)){
      if (pos2 > fin){
        seguir = false;
        if (compararTFechas(fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos])), (fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos1])))) == 1){
          swp = cp->vectorPer[pos];
          cp->vectorPer[pos] = cp->vectorPer[pos1];
          cp->vectorPer[pos1] = swp;
          cp->vectorPos[idTPersona(cp->vectorPer[pos])] = pos;
          cp->vectorPos[idTPersona(cp->vectorPer[pos1])] = pos1;
        }
      }else{
        if (compararTFechas(fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos1])), (fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos2])))) == -1){
          posPrima = pos1;
        }else{
          posPrima = pos2;
        }
        if (compararTFechas(fechaTEvento(primerEventoDeTPersona(cp->vectorPer[posPrima])), (fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos])))) == -1){
          swp = cp->vectorPer[posPrima];
          cp->vectorPer[posPrima] = cp->vectorPer[pos];
          cp->vectorPer[pos] = swp;
          cp->vectorPos[idTPersona(cp->vectorPer[posPrima])] = posPrima;
          cp->vectorPos[idTPersona(cp->vectorPer[pos])] = pos;
        }
        pos = posPrima;
        pos1 = pos * 2; //pos2 * 2
        pos2 = pos1 + 1;
      }
    }
  }else{
    while ((pos1 <= fin) && (seguir)){
      if (pos2 > fin){
        seguir = false;
        if (compararTFechas(fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos])), (fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos1])))) == -1){
          swp = cp->vectorPer[pos];
          cp->vectorPer[pos] = cp->vectorPer[pos1];
          cp->vectorPer[pos1] = swp;
          cp->vectorPos[idTPersona(cp->vectorPer[pos])] = pos;
          cp->vectorPos[idTPersona(cp->vectorPer[pos1])] = pos1;
        }
      }else{
        if (compararTFechas(fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos1])), (fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos2])))) == 1){
          posPrima = pos1;
        }else{
          posPrima = pos2;
        }
        if (compararTFechas(fechaTEvento(primerEventoDeTPersona(cp->vectorPer[posPrima])), (fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos])))) == 1){
          swp = cp->vectorPer[posPrima];
          cp->vectorPer[posPrima] = cp->vectorPer[pos];
          cp->vectorPer[pos] = swp;
          cp->vectorPos[idTPersona(cp->vectorPer[posPrima])] = posPrima;
          cp->vectorPos[idTPersona(cp->vectorPer[pos])] = pos;
        }
        pos = posPrima;
        pos1 = pos * 2 ; //pos2 * 2
        pos2 = pos1 + 1;
      }
    }
  }
}

void eliminarPrioritaria(TColaDePrioridadPersona &cp) {
  if (!estaVaciaCP(cp)){
    cp->cantidad--;
    if(cp->cantidad == 0){
      cp->vectorPos[idTPersona(cp->vectorPer[1])] = 0;
      liberarTPersona(cp->vectorPer[1]);
    }else if (cp->cantidad == 1){
      cp->vectorPos[idTPersona(cp->vectorPer[1])] = 0;
      liberarTPersona(cp->vectorPer[1]);
      cp->vectorPer[1] = cp->vectorPer[2];
      cp->vectorPos[idTPersona(cp->vectorPer[1])] = 1;
    }else if (cp->cantidad > 1){
      cp->vectorPos[idTPersona(cp->vectorPer[1])] = 0;
      liberarTPersona(cp->vectorPer[1]);
      cp->vectorPos[idTPersona(cp->vectorPer[cp->cantidad + 1])] = 1;
      cp->vectorPer[1] = cp->vectorPer[cp->cantidad +1];
      filtradoD(cp,1,cp->cantidad);
    }
  }
}

bool estaEnCP(nat id, TColaDePrioridadPersona cp) {
  if ((!estaVaciaCP(cp))&&(id>= 0) && (id<=cp->max)){
    return (cp->vectorPos[id] > 0 );
  }else{
    return false;
  }
  
}

TFecha prioridad(nat id, TColaDePrioridadPersona cp){
  int pos = cp->vectorPos[id];
  return fechaTEvento(primerEventoDeTPersona(cp->vectorPer[pos]));
}