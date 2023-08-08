#include "../include/fecha.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 1 //////
///////////////////////////////////


struct rep_fecha {
    /************ Parte 2.1 ************/
    /*Escriba el código a continuación */
    nat dia, mes , anio;
    /****** Fin de parte Parte 2.1 *****/
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
    TFecha nuevaFecha = NULL;
    /************ Parte 3.1 ************/
    /*Escriba el código a continuación */
    nuevaFecha = new rep_fecha;
    nuevaFecha->dia= dia;
    nuevaFecha->mes= mes;
    nuevaFecha->anio= anio;
    /****** Fin de parte Parte 3.1 *****/
    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {
    /************ Parte 3.3 ************/
    /*Escriba el código a continuación */
    delete fecha;
    fecha = NULL;
    /****** Fin de parte Parte 3.3 *****/
}

void imprimirTFecha(TFecha fecha) {
    /************ Parte 3.5 ************/
    /*Escriba el código a continuación */
    printf("%d/%d/%d\n", fecha->dia, fecha->mes, fecha->anio );
    /****** Fin de parte Parte 3.5 *****/
}

/************ Parte 3.9 ************/
/*Escriba el código a continuación */
/*Recuerde que las funciones auxiliares
  deben declararse antes de ser utilizadas*/
// Función para obtener la cantidad de días de un mes en un año dado
bool anioBisiesto(nat anio){
bool aux = false;
nat i=0;
for (i=0; (anio >= ((i*4)+2024)) ; i++){
    aux =  (anio == ((i*4)+2024));
    }
return aux;
}

nat diasMes(nat mes, nat anio){ //tendria que utilizar una variable para devolver el valor?
nat res = 0;
switch (mes){
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        //Meses que tienen 31 dias
        res= 31;
    break;
    case 4: case 6: case 9: case 11:
        //Meses que tienen 30 dias
        res= 30;
    break;
    case 2:
        //Meses con 28/29 dias
        if (anioBisiesto(anio)){
            res= 29;
        } else res= 28;
    break;
default: res= 0;
}
return res;
}

void aumentarTFecha(TFecha &fecha, nat dias) {
fecha->dia += dias;
while (fecha->dia > diasMes(fecha->mes, fecha->anio)) {
    fecha->dia -= diasMes(fecha->mes, fecha->anio);
    fecha->mes++;
    if (fecha->mes > 12) {
        fecha->mes = 1;
        fecha->anio++;
    }
}
}
/****** Fin de parte Parte 3.9 *****/

bool sonFechasIguales(TFecha fecha1, TFecha fecha2){
    bool aux = ((fecha1->anio == fecha2->anio) && (fecha1->mes == fecha2->mes) && (fecha1->dia == fecha2->dia));
    return aux;
}

int compararTFechas(TFecha fecha1, TFecha fecha2) {
    int res = 0;
    /************ Parte 3.10 ************/
    /*Escriba el código a continuación */
    if (!(sonFechasIguales(fecha1, fecha2))){
        if ((fecha1->anio > fecha2->anio) || ( (fecha1->anio == fecha2->anio) && (fecha1->mes > fecha2->mes)) || ((fecha1->anio == fecha2->anio) && (fecha1->mes == fecha2->mes) && (fecha1->dia > fecha2->dia))) {
            res = 1;
        } else res = -1;
    } 
    /****** Fin de parte Parte 3.10 *****/
    return res;
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 1 //////
/////////////////////////////////

/*-----------------------------*/

///////////////////////////
////// FUNCION NUEVA //////
///////////////////////////

// Retorna una copia de la fecha
TFecha copiarTFecha(TFecha fecha) {
    if (fecha!=NULL){
        TFecha fechaNueva = new rep_fecha;
        fechaNueva->dia = fecha->dia;
        fechaNueva->mes = fecha->mes;
        fechaNueva->anio = fecha->anio;
        return fechaNueva;
    }else{
        return NULL;
    }
}
