#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Estructuras.h"


//Funciones nodoPracticasXingreso
nodoPracticasXingreso* crearNodoPxI(stPracXingreso pxi){
    nodoPracticasXingreso * aux =(nodoPracticasXingreso*)malloc(sizeof(nodoPracticasXingreso));
    aux->pXi = pxi;
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
stPracXingreso cargarPXI(int numIngreso){///Por parametro pasa lista.Ingresos.NrIngresos
    stPracXingreso aux;
    aux.nroIngreso=numIngreso;
        aux.nroPractica = contarPxienArchivo("pxi.bin",numIngreso)+1;
        printf("Ingrese nombre de la practica:\n");
        fflush(stdin);
        gets(aux.nombrePractica);

    printf("Ingrese resultado: \n" );
    fflush(stdin);
    gets(aux.resultado);
    return aux;
}
nodoPracticasXingreso * buscarNroPractica(nodoPracticasXingreso * lista, int nroPractica){///Ya tenes que estar
    nodoPracticasXingreso * actual = lista;                                                          ///situado en el ingreso a buscar
    while(actual != NULL){
        if(lista->pXi.nroPractica == nroPractica){
            return actual;
        }
        actual = actual->sig;
    }
    return NULL;
}
nodoPracticasXingreso * Alta_de_pxi(nodoPracticasXingreso * lista){///Ya tenes el nro.Ingreso
    stPracXingreso pxi = cargarPXI(lista->pXi.nroIngreso);
    nodoPracticasXingreso * buscar = buscarNroPractica(lista,pxi.nroIngreso);
    if(buscar == NULL){
        nodoPracticasXingreso * nuevoPxi = crearNodoPxI(pxi);
        lista = agregarPpioPXI(lista,nuevoPxi);
    }else{
        printf("Error. El nro de practica ya existe.");
    }
    return lista;
}
nodoPracticasXingreso * modificacion_de_pxi(nodoPracticasXingreso * lista){  //Busco por nro de ingreso para modificar
    nodoPracticasXingreso* auxPractica=NULL;
    stPracXingreso aux;
    aux.nroIngreso=lista->pXi.nroIngreso;
    int numValido = 0;
    char numString[10];
    do{
    printf("\nIngrese Nro.Practica: ");
    scanf("%i",&aux.nroPractica);
    sprintf(numString,"%i",aux.nroPractica);
    numValido = validarNumero(numString);                                    ///Verificar el do while
    if(numValido ==1){
    printf("Error. Ingrese un numero de practica valido.");
        }
    }while(numValido != 0);

    auxPractica=buscarNroPractica(lista,aux.nroPractica);///Envio la practica que quiero buscar

    if(!auxPractica){ ///encontro el nodo que tiene el nro de practica
       /* printf("\nIngrese el nuevo nro de practica: ");
        fflush(stdin); */  ///Al hacer el numero de practica que se aumente mediante la variable estatica cada vez que se llama no haria falta modificar el numero de practica
      //  scanf("%d",&auxPractica->pXi.nroPractica);
        printf("Ingrese nuevo nombre de la practica: \n");
        fflush(stdin);
        gets(auxPractica->pXi.nombrePractica);
        printf("\nIngrese el nuevo resultado: \n");
        fflush(stdin);
        gets(auxPractica->pXi.resultado);
        printf("\nDatos modificados modificados correctamente");
    }else{
        printf("\nNo se encontro la practica de ingreso a modificar."); // En caso de que no se encuentre el nodo que tiene el nro de ingreso
    }
    return lista;
}
nodoPracticasXingreso * Baja_de_pxi(nodoPracticasXingreso * lista){
   if(!lista){
        printf("\nLa lista de practicas por ingreso esta vacia. \n");
        return NULL;
    }
    int nroPractica;
    int numeroValido = 0;
    char numString[10];
        do{
        printf("Ingrese el nro de la practica a eliminar: \n");
        fflush(stdin);
        scanf("%i", &nroPractica);
        sprintf(numString,"%i",nroPractica);
        numeroValido = validarNumero(numString);                                    ///Verificar el do while
        if(numeroValido ==1){
            printf("Error. Ingrese un numero de practica valido.");
        }
    }while(numeroValido != 0);
    ///Teniendo en cuenta que las practica estan ordenadas en orden ascendete y de a uno.
    nodoPracticasXingreso* anteriorPractica=buscarNroPractica(lista,nroPractica-1);///Busco el nodo de la practica anterior
    nodoPracticasXingreso* actualPractica=buscarNroPractica(lista,nroPractica);///Busco el nodo de la practica
    if(actualPractica){
        anteriorPractica->sig=actualPractica->sig;
        free(actualPractica);
        printf("La practica de ingreso con numero %d ha sido eliminada correctamente.", nroPractica);
    }else{
        printf("La practica de ingreso con el numero %d no se se encontro.", nroPractica);
    }
    return lista;
}
int validarNumero(char * nroPractica){ ///Valida que el usuario no ingrese letras y que en caso de ingresar mas de 7 numeros tire error
    int cantNum = strlen(nroPractica);
    int flag = 0;
    if(cantNum <7){
        for(int i = 0;i<cantNum; i++){
            if(!isdigit(nroPractica[i])){
                flag = 1;
            }
        }
    }else{
        flag = 1;
    }
    return flag;
}
///Funciones Archivo
nodoPaciente* pasarPracticasAlArbolArchivo(char archivo[],nodoPaciente* arbol){
    stPracXingreso aux;
    FILE* archi=fopen(archivo,"rb");
    nodoIngresos* ing=NULL;
    if(archi){
        if(fread(&aux,sizeof(stPracXingreso),1,archi)>0){
            fseek(archi, 0, SEEK_SET);
            while(fread(&aux,sizeof(stPracXingreso),1,archi)>0){

                ing=buscarPorNroIngreso(arbol,aux.nroIngreso);
                ing=agregarPpioPXI(ing,crearNodoPxI(aux));
            }
        }
    }else{
        printf("Se produjo un error.\n");
    }
    fclose(archi);
    return arbol;
}
void agregarPxialArchivo(char archivo[], stPracXingreso dato){ ///Por parametro pasar lista PXI->dato
    FILE * archi = fopen(archivo,"ab");
    stPracXingreso aux;
    if(archi){
         aux = dato;
        fwrite(&aux,sizeof(stPracXingreso),1,archi);
        fclose(archi);
    }else{
        printf("Error al cargar archivoPXI.");
    }
}
void mostrarArchivoPXI(char archivo[]){
    FILE * archi = fopen(archivo,"rb");
    stPracXingreso aux;
    if(archi != NULL){
        while(fread(&aux,sizeof(stPracXingreso),1,archi)>0){
            printf("Numero de ingreso: %d \n" ,aux.nroIngreso);
            printf("Numero de practica: %d \n", aux.nroPractica);
            printf("Resultado: %s \n", aux.resultado);
        }
        fclose(archi);
    }
}
void modificarArchivoPXI(char archivo[], stPracXingreso dato){  ///Pasar por parametro listaPXI->dato
    FILE * archi =(archivo, "r+b");
    stPracXingreso aux;
    if(archi){
        while(fread(&aux,sizeof(stPracXingreso),1,archi)>0){
            if(aux.nroIngreso == dato.nroIngreso){
               printf("Ingrese nuevo nombre de la Practica: \n");
               scanf("%s", &aux.nombrePractica);
                printf("Ingrese nuevo resultado de la practica: \n");
                scanf("%c", &aux.resultado);
                fseek(archi,(-1)*sizeof(stPracXingreso),SEEK_CUR);
                fwrite(&aux,sizeof(stPracXingreso),1,archi);
            }
        }
        fclose(archi);
    }
}
int contarPxienArchivo( char archivo[],int nroIngreso){
    FILE * archi = fopen(archivo,"rb");
    stPracXingreso aux;
    int cant = 0;
    if(archi){
        while(fread(&aux,sizeof(stPracXingreso),1,archi)>0){        ///Recorro el archivo
            if(aux.nroIngreso == nroIngreso){       ///Si encuentra el mismo nro de ingreso pasado por parametro  que aumente el contador de el nro de practicas
                cant++;
            }
        }
    }
    return cant;
}

