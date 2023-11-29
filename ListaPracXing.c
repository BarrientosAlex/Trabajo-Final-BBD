#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "Estructuras.h"


///Funciones nodoPracticasXingreso
practicas cargarPracticas(){///esta no se usa
    practicas aux;
    printf("Ingrese el Nro de practicas: \n");
    fflush(stdin);
    scanf("%d", &aux.nroPractica);
    printf("Ingrese el nombre de la Practica: \n");
    fflush(stdin);
    gets(aux.nombrePractica);
    aux.eliminado=0;
    return aux;
}
///Funciones mostrar
void mostrarPxiAUX(stPracXingreso dato){
    printf("\nNro. practica: %i",dato.nroPractica);
    printf("\nNombre de practica: %s",dato.nombrePractica);
    printf("\nResultado: %s\n",dato.resultado);
}
void mostrarPxi(nodoPracticasXingreso* lista){
    while(lista){
       if(lista->pXi.eliminado==0){
            mostrarPxiAUX(lista->pXi);
       }
       lista=lista->sig;
    }
}
void mostrarPxiADMIN(nodoPracticasXingreso* lista){
    while(lista){
        mostrarPxiAUX(lista->pXi);
        lista=lista->sig;
    }
}
void recorrerIngresosParamostrarPracticas(nodoIngresos* lista){
    nodoIngresos* seg=lista;
    while(seg){
        printf("\n-------------------\n");
        mostrarPxi(seg->practicas);
        printf("\n-------------------\n");
        seg=seg->sig;
    }
}
void recorrerArbolParaMostrarPracticas(nodoPaciente* arbol){
    if(arbol){
        recorrerArbolParaMostrarPracticas(arbol->izq);
        recorrerIngresosParamostrarPracticas(arbol->ingresos);
        recorrerArbolParaMostrarPracticas(arbol->der);
    }
}
///Funciones buscar por prefijo
int validarPrefijo(char * prefijo){
    int flag = 0;
    int cantNum = strlen(prefijo);
    if(cantNum < 14){
        for(int i = 0;i<cantNum;i++){
            if(isdigit(prefijo[i])){/// En caso de que ingrese un numero va a tirar error
                flag = 1;
            }
        }

        if(prefijo[0] == '\0'){ /// EN caso de que ingrese un enter en el primer caracter del arreglo va a tirar error
            flag = 1;
        }

    }else{
        flag=1;
    }
    return flag;
}
void buscarPrefijoPractica(nodoPracticasXingreso* lista,char prefijo[]){///Recorre la lista de practicas
    nodoPracticasXingreso* seg=lista;
    while(seg){
        if(strstr(strlwr(seg->pXi.nombrePractica),strlwr(prefijo))){///Si es distinto de null encontro el prefijo dentro de la cadena
            mostrarPxiAUX(seg->pXi);
        }
        seg=seg->sig;
    }
}
void buscarPrefijoIngreso(nodoIngresos* lista,char prefijo[]){///Recorre la lista de ingresos
    nodoIngresos* seg=lista;
    while(seg){
        buscarPrefijoPractica(seg->practicas,prefijo);
        seg=seg->sig;
    }
}
void buscarPrefijoPaciente(nodoPaciente* arbol,char prefijo[]){///Recorre el arbol
    if(arbol){
        buscarPrefijoPaciente(arbol->izq,prefijo);
        buscarPrefijoIngreso(arbol->ingresos,prefijo);
        buscarPrefijoPaciente(arbol->der,prefijo);
    }
}
///Funciones crearNodo y agregar
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
    int practicaValida = 0;
    aux.nroPractica = contarPxienArchivo("pxi.bin")+1;
    printf("\n--------------------------");
    printf("\nNumero ingreso: %d",numIngreso);
    printf("\nNumero practica: %d",aux.nroPractica);
    do{
        printf("\nIngrese nombre de la practica: ");
        fflush(stdin);
        gets(aux.nombrePractica);
        practicaValida = validarPractica(aux.nombrePractica);
        if(practicaValida == 1){
            printf("\nERROR. No puede ingresar un nombre de la practica vacio.");
        }
    }while(practicaValida != 0);
    system("cls");
    printf("\n--------------------------");
    printf("\nNumero ingreso: %d",numIngreso);
    printf("\nNumero practica: %d",aux.nroPractica);
    printf("\n Nombre de la Practica: %s", aux.nombrePractica);
    printf("\n--------------------------");
    /*printf("\nIngrese resultado: " );
    fflush(stdin);
    gets(aux.resultado);*/
    aux.resultado[0]='\0';///le asigno null al resultado, ya que lo asigna el profesional
    //strcpy(aux.resultado,"\0");
    aux.eliminado=0;
    return aux;
}
int validarPractica(char * nombrePractica){
    int flag = 0;
     if(nombrePractica[0] == '\0'){   //Para que no pueda ingresar un espacio o un enter  en la primera posicion

        flag = 1;
        return flag;
    }
    return flag;
}
nodoPracticasXingreso * buscarNroPractica(nodoPracticasXingreso * lista, int nroPractica){///Ya tenes que estar
    nodoPracticasXingreso * actual = lista;                                               ///situado en el ingreso a buscar
    while(actual != NULL){
        if(actual->pXi.nroPractica == nroPractica){
            return actual;
        }
        actual = actual->sig;
    }
    return NULL;
}
nodoPracticasXingreso * Alta_de_pxi(nodoPracticasXingreso * lista,int num){///Ya tenes el nro.Ingreso
    char elec='s';
    while(elec=='s'||elec=='S'){
        stPracXingreso pxi = cargarPXI(num);
        int flag=buscarPxiArchivo("pxi.bin",pxi.nroPractica);
        nodoPracticasXingreso * nuevoPxi =NULL;
        nuevoPxi=crearNodoPxI(pxi);
        if(flag==0){
            lista = agregarPpioPXI(lista,nuevoPxi);
            agregarPxialArchivo("pxi.bin",pxi);
        }else{
            printf("\nError: nro.Practica existente.\n");
        }
        printf("\nDesea cargar mas practicas para el paciente? (s) para continuar: ");
        fflush(stdin);
        scanf("%c",&elec);
    }
    return lista;
}
nodoPracticasXingreso * modificacion_de_pxi(nodoPracticasXingreso * lista){  //Busco por nro de ingreso para modificar
    nodoPracticasXingreso* auxPractica=NULL;
    stPracXingreso aux;
    aux.nroIngreso=lista->pXi.nroIngreso;
    int numValido = 0;
     int practicaValida = 0;
     int resultadoValido = 0;
    char numString[10];
    do{
        printf("\nIngrese Nro.Practica: ");
        scanf("%i",&aux.nroPractica);
        sprintf(numString,"%i",aux.nroPractica);
        numValido = validarNumero(numString);///Verificar el do while
        if(numValido ==1){
            printf("\nError. Ingrese un numero de practica valido.");
        }
    }while(numValido != 0);
    auxPractica=buscarNroPractica(lista,aux.nroPractica);///Envio la practica que quiero buscar
    if(auxPractica){ ///encontro el nodo que tiene el nro de practica
        do{
            printf("\nIngrese nuevo nombre de la practica: \n");
            fflush(stdin);
            gets(auxPractica->pXi.nombrePractica);
            practicaValida = validarPractica(auxPractica->pXi.nombrePractica);
        if(practicaValida == 1){
            printf("\nERROR. No puede ingresar un nombre de la practica vacio.");
        }
    }while(practicaValida != 0);

        do{
            printf("\nIngrese el nuevo resultado: \n");
            fflush(stdin);
            gets(auxPractica->pXi.resultado);
            resultadoValido = validarPractica(auxPractica->pXi.resultado);
            if(resultadoValido == 1){
                printf("\nERROR.No puede ingresar un resultado de la practica vacio");
            }
        }while(resultadoValido != 0);

        printf("\nDatos modificados correctamente.");
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
        printf("\nIngrese el nro de la practica a eliminar: \n");
        fflush(stdin);
        scanf("%i", &nroPractica);
        sprintf(numString,"%i",nroPractica);
        numeroValido = validarNumero(numString);                                    ///Verificar el do while
        if(numeroValido ==1){
            printf("\nError. Ingrese un numero de practica valido.");
        }
    }while(numeroValido != 0);
    ///Teniendo en cuenta que las practica estan ordenadas en orden ascendete y de a uno.
    nodoPracticasXingreso* actualPractica=buscarNroPractica(lista,nroPractica);///Busco el nodo de la practica
    if(actualPractica){
        actualPractica->pXi.eliminado=1;
        modificarArchivoPXI("pxi.bin",actualPractica->pXi);
        printf("\nLa practica de ingreso con numero %d ha sido eliminada correctamente.", nroPractica);
    }else{
        printf("\nLa practica de ingreso con el numero %d no se se encontro.", nroPractica);
    }
    return lista;
}
int validarNumero(char * nroPractica){ ///Valida que el usuario no ingrese letras y que en caso de ingresar mas de 7 numeros tire error
    int cantNum = strlen(nroPractica);
    int flag = 0;
    if(cantNum <7){
        for(int i = 0;i<cantNum; i++){
            if(!isdigit((unsigned char)nroPractica[i])){
                flag = 1;
            }
        }

        if(nroPractica[0] == '\0'){
            flag = 1;
        }


    }else{
        flag = 1;
    }
    return flag;
}
nodoPracticasXingreso* buscarPractica(nodoPracticasXingreso* lista,int numPractica){///Previamente mostrar todas las practicas
    nodoPracticasXingreso* seg=lista;
    nodoPracticasXingreso* actual=NULL;
    int encontrado=0;
    while(seg&&encontrado==0){
        if(seg->pXi.nroPractica==numPractica){
            actual=seg;
            encontrado=1;
        }
        seg=seg->sig;
    }
    return actual;
}
///Funciones Archivo
nodoPaciente* pasarPracticasAlArbolArchivo(char archivo[],nodoPaciente* arbol){
    stPracXingreso aux;
    FILE* archi=fopen(archivo,"rb");
    nodoIngresos* ing=NULL;
    if(!archi){
        archi=fopen(archivo,"ab");
    }else{
        if(fread(&aux,sizeof(stPracXingreso),1,archi)>0){
            fseek(archi, 0, SEEK_SET);
            while(fread(&aux,sizeof(stPracXingreso),1,archi)>0){
                ing=buscarPorNroIngreso(arbol,aux.nroIngreso);
                ing->practicas=agregarPpioPXI(ing->practicas,crearNodoPxI(aux));
            }
        }else{
            printf("\nError. No se pudo leer el archivo.\n");
        }
    }
    fclose(archi);
    return arbol;
}
void agregarPxialArchivo(char archivo[], stPracXingreso dato){ ///Por parametro pasar lista PXI->dato
    FILE * archi = fopen(archivo,"ab");
    if(archi){
        fwrite(&dato,sizeof(stPracXingreso),1,archi);
    }else{
        printf("Error al cargar archivoPXI.");
    }
    fclose(archi);
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
    FILE* archi =fopen(archivo, "r+b");
    stPracXingreso aux;
    if(archi){
        while(fread(&aux,sizeof(stPracXingreso),1,archi)>0){
            if(aux.nroPractica == dato.nroPractica){
                fseek(archi,(-1)*sizeof(stPracXingreso),SEEK_CUR);
                fwrite(&dato,sizeof(stPracXingreso),1,archi);
                break;
            }
        }
        fclose(archi);
    }
}
int contarPxienArchivo(char archivo[]){
    FILE * archi = fopen(archivo,"rb");
    int cant = 0;
    if(archi){
            fseek(archi,0,SEEK_END);
            int tam=ftell(archi);
            cant=tam/sizeof(stPracXingreso);
    }
    fclose(archi);
    return cant;
}
int buscarPxiArchivo(char archivo[],int nrPractica){
    FILE* archi=fopen(archivo,"rb");
    int flag=0;
    stPracXingreso aux;
    if(archi){
        while(fread(&aux,sizeof(stPracXingreso),1,archi)>0){
            if(aux.nroPractica==nrPractica){
                flag=1;
                return flag;
            }
        }
        fclose(archi);
    }
    return flag;
}

