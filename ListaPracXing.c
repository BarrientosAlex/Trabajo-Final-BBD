#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Estructuras.h"


//Funciones nodoPracticasXingreso
    nodoPracticasXingreso * crearNodoPxI(pracXingreso pxi){
        nodoPracticasXingreso * aux =(nodoPracticasXingreso*)malloc(sizeof(nodoPracticasXingreso));
        aux->pXi = pxi;
        aux->practicas = NULL;
        aux->sig = NULL;
        return aux;
    }

    nodoPracticasXingreso * agregarPpioPXI(nodoPracticasXingreso * lista, nodoPracticasXingreso * nuevoNodo){
         if(lista == NULL){
            lista = nuevoNodo;
        }else{
            nuevoNodo->sig = lista;
            lista = nuevoNodo;
        }
        return lista;
    }


    pracXingreso cargarPXI(){
        pracXingreso aux;
        printf("Ingrese nro de Ingreso: \n" );
        fflush(stdin);
        scanf("%d", &aux.nroIngreso);
        printf("Ingrese nro de Practica: \n" );
        fflush(stdin);
        scanf("%d", &aux.nroPractica);
         printf("Ingrese resultado: \n" );
        fflush(stdin);
        gets(aux.resultado);
        return aux;
    }


   nodoPracticasXingreso * buscarNroIngresoYpractica(nodoPracticasXingreso * lista, pracXingreso pxi){
        nodoPracticasXingreso * actual = lista;
        while(actual != NULL){
            if(lista->pXi.nroIngreso == pxi.nroIngreso && lista->pXi.nroPractica == pxi.nroPractica){
                return actual;
            }
            actual = actual->sig;
        }
        return NULL;
   }

nodoPracticasXingreso * Alta_de_pxi(nodoPracticasXingreso * lista){
    pracXingreso pxi = cargarPXI();
    nodoPracticasXingreso * buscar = buscarNroIngresoYpractica(lista,pxi);
    if(buscar == NULL){
        nodoPracticasXingreso * nuevoPxi = crearNodoPxI(pxi);
        lista = agregarPpioPXI(lista,nuevoPxi);

    }else{
        printf("Error. El nro de practica o de ingreso ya existe.");
    }
    return lista;
}


nodoPracticasXingreso *  modificacion_de_pxi(nodoPracticasXingreso * lista){  //Busco por nro de ingreso para modificar
       int nroIngreso;
        nodoPracticasXingreso * ante = lista;
        nodoPracticasXingreso * seg = lista->sig;

        printf("Ingrese el numero de ingreso de la practica: \n");
        fflush(stdin);
        scanf("%d", nroIngreso);

        while(seg != NULL && seg->pXi.nroIngreso != nroIngreso){
            ante = seg;
            seg = seg->sig;
        }

        if(seg != NULL){ ///encontro el nodo que tiene el nro de ingreso
            printf("Ingrese el nuevo nro de practica: \n");
            fflush(stdin);
            scanf("%d", &seg->pXi.nroIngreso);
            printf("Ingrese el nuevo resultado: \n");
            fflush(stdin);
            gets(seg->pXi.resultado);
            printf("Datos modificados modificados correctamente");
        }else{
            printf("No se encontro la practica de ingreso a modificar."); // En caso de que no se encuentre el nodo que tiene el nro de ingreso
        }
        return lista;
}

nodoPracticasXingreso * Baja_de_pxi(nodoPracticasXingreso * lista){
   if(lista == NULL){
        printf("La lista de practicas por ingreso esta vacia. \n");
        return NULL;
    }

    nodoPracticasXingreso * ante = lista;
    nodoPracticasXingreso * seg = lista->sig;
    int nroPractica;


    printf("Ingrese el nro de la practica a eliminar: \n");
    fflush(stdin);
    scanf("%d", &nroPractica);
    while(seg != NULL && seg->pXi.nroPractica != nroPractica){
        ante = seg;
        seg = seg->sig;
    }

    if(seg != NULL){
          ante->sig = seg->sig;
        free(seg);
            printf("La practica de ingreso con numero %d ha sido eliminada correctamente.", nroPractica);
    }else{
         printf("La practica de ingreso con el numero %d no se se encontro.", nroPractica);
     }
    return lista;

}
