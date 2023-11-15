#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Paciente{
    char apelyNom[40];
    int edad;
    int dni;
    char direccion[30];
    char telefono[15];
    int eliminado;
} Paciente;

typedef struct ingresos{
    int nroIngreso;
    char fechaIngreso[10];
    char fechaRetiro[10];
    int dni;
    int matricula;
    int eliminado;
}ingresos;

typedef struct pracXingreso{
    int nroIngreso;
    int nroPractica;
    char resultado[40];
}pracXingreso;

typedef struct practicas{
    int nroPractica;
    char nombrePractica[30];
    int eliminado;
}practicas;

typedef struct nodoPaciente{
    Paciente paciente;
    struct nodoIngresos * ingresos;
    struct nodoA * izq;
    struct nodoA * der;
    
}nodoPaciente;

typedef struct nodoIngresos{
    ingresos ingreso;
    struct nodoPracticasXingreso * practicas;
    struct nodoIngresos * sig;
    struct nodoIngresos * ant;
}nodoIngresos;

typedef struct nodoPracticasXingreso{
    pracXingreso pXi;                       
    struct nodoPracticas * practicas;
    struct nodoPracticasXingreso * sig;
}nodoPracticasXingreso;

typedef struct nodoPracticas{
    practicas prac;
    struct nodoPracticas * sig;
}nodoPracticas;


int main(){


}

// Funciones nodoPracticas
nodoPracticas * crearNodoPrac(practicas p){
    nodoPracticas * aux =(nodoPracticas*)malloc(sizeof(nodoPracticas));
    aux->prac = p;
    aux->sig = NULL;
    return aux;
}

nodoPracticas * agregarPpio(nodoPracticas * lista, nodoPracticas * nuevo){
    if(lista == NULL){
        lista = nuevo;
    }else{
        nuevo->sig = lista;
        lista = nuevo;
    }
    return lista;
}


nodoPracticas * agregarEnOrdenP(nodoPracticas * lista, nodoPracticas * nuevoNodo){  //Agrego en orden segun el nombre de la practica
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        if(strcmpi(nuevoNodo->prac.nombrePractica,lista->prac.nombrePractica)< 0){
            agregarPpio(lista,nuevoNodo);
        }else{
            nodoPracticas * ante = lista;
            nodoPracticas * seg = lista->sig;
            while(seg != NULL && strcmpi(nuevoNodo->prac.nombrePractica,seg->prac.nombrePractica)> 0){
                ante = seg;
                seg = seg->sig;
            }   
            ante->sig = nuevoNodo;
            nuevoNodo->sig = lista;
        }
    }
    return lista;
}

practicas cargarPracticas(){
    practicas aux;
    printf("Ingrese el Nro de practicas: \n");
    fflush(stdin);
    scanf("%d", &aux.nroPractica);
    printf("Ingrese el nombre de la Practica: \n");
    fflush(stdin);
    gets(aux.nombrePractica);
    printf("Numero de eliminado: \n");
    fflush(stdin);
    scanf("%d", &aux.eliminado);

    return aux;
} 


nodoPracticas * alta_de_Practica(nodoPracticas * lista){
    practicas nuevaPractica = cargarPracticas();  //Guardo en la variable nuevaPractica los datos ingresado por el medico
    nodoPracticas * nuevoNodo = crearNodoPrac(nuevaPractica); // creo un nuevoNodo a partir de la variable nuevaPractica
    agregarEnOrdenP(lista,nuevoNodo);
    printf("Practica dada de alta correctamente");
    return lista;
}

nodoPracticas * modificacion_de_Practica(nodoPracticas * lista){
    int nroPractica;
    printf("Ingrese el numero de la practica a modificar:");
    fflush(stdin);
    scanf("%d",&nroPractica);
    nodoPracticas * actual = lista;
    while(actual != NULL && actual->prac.nroPractica != nroPractica){
        actual = actual->sig;  
        //Este ciclo while se va a romper cuando actual haya recorrido toda la lista o cuando encuentre un nodo que tenga el mismo numero de practica que el ingresado para modificar.
    }

    if(actual != NULL){ //Si actual es != NULL significa que se encontro un nodo con el mismo numero de practica que el ingresado.
        printf("Ingrese el nuevo nombre de la practica: ");
        fflush(stdin);
        gets(actual->prac.nombrePractica);
        printf("Nombre modificado correctamente. \n");
    }else{
        printf("La practica con el numero %d no se encontro.\n", actual->prac.nroPractica);
    }
    return lista;
}

   void  filtrarPorPrefijo (nodoPracticas * lista){
        char practicaFiltrada[30];
        printf("Ingrese el prefijo para filtrar las practicas:");
        fflush(stdin);
        gets(practicaFiltrada);

        nodoPracticas * actual = lista;
        while(actual != NULL){
            if(strstr(actual->prac.nombrePractica,practicaFiltrada)!= NULL){  //La funcion strstr busca una subcadena que este contenido dentro de otra cadena, si no la encuentra retorna NULL, si la encuentra retorna un puntero a la posicion
                printf("%d - %s", actual->prac.nroPractica , actual->prac.nombrePractica);
            }
            actual = actual->sig;
        }
    }

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

    
    pracXingreso cargarPXI (){
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


void  modificacion_de_pxi(nodoPracticasXingreso * lista, int nroIngreso){  //Busco por nro de ingreso para modificar
        nodoPracticasXingreso * actual = lista;
        nodoPracticasXingreso * seg = lista->sig;
        while(actual != NULL && actual->pXi.nroIngreso != nroIngreso){
            actual = seg;
            seg = seg->sig;
        }

        if(actual != NULL){ ///encontro el nodo que tiene el nro de ingreso
            printf("Ingrese el nuevo nro de practica: \n");
            fflush(stdin);
            scanf("%d", &actual->pXi.nroIngreso);
            printf("Ingrese el nuevo resultado: \n");
            fflush(stdin);
            gets(actual->pXi.resultado);
            printf("Datos modificados modificados correctamente");
        }else{
            printf("No se encontro la practica de ingreso a modificar."); // En caso de que no se encuentre el nodo que tiene el nro de ingreso
        }

}


//Funciones Ingreso de Laboratorio

nodoIngresos * inicListaDoble(){
    return NULL;
}

nodoIngresos * crearNodoIng (ingresos a){
    nodoIngresos * aux =(nodoIngresos*)malloc(sizeof(nodoIngresos));
    aux->ingreso = a;
    aux->practicas = NULL;
    aux->sig = NULL;
    aux->ant = NULL;
    return aux;

}

nodoIngresos * agregarPpioIngresos(nodoIngresos * lista, nodoIngresos * nuevo){
    if(lista == NULL){
        lista = nuevo;
    }else{
        lista->ant = nuevo;
        nuevo->sig = lista;
        lista = nuevo;
    }
    return lista;
}

nodoIngresos * agregarOrdenFecha(nodoIngresos * lista, nodoIngresos * nuevo){ ///Se agrega en orden las fechas de manera descendente 
    if(lista == NULL){
        lista = nuevo;
    }else{
        if(strcmpi(nuevo->ingreso.fechaIngreso,lista->ingreso.fechaIngreso)>0){
            agregarPpioIngresos(lista,nuevo);
        }else{
            nodoIngresos * ante = lista;
            nodoIngresos * seg = lista->sig;
            while(seg != NULL && strcmpi(nuevo->ingreso.fechaIngreso,seg->ingreso.fechaIngreso)<0){
                ante = seg;
                seg = seg->sig;
            }

            ante->sig = nuevo;
            nuevo->ant = ante;
            nuevo->sig =seg;
            if(seg != NULL){
                seg->ant = nuevo;
            }
        }
    }
    return lista;
}

///Funcion para para que el usuario pueda seleccionar por que forma filtrar la busqueda y si se encuentra lo que busco dentro de la lista, que retorne ese nodo.


int filtrarPorNroIngreso(nodoIngresos * lista){
    int nroIngreso;
      printf("Ingrese el nro de Ingreso a buscar: \n");
      fflush(stdin);
     scanf("%d", &nroIngreso);
     return lista->ingreso.nroIngreso == nroIngreso;  ///retorna 1 si se cumple la condicion o 0 si no encuentra el nroIngresado en la lista;
}

int filtrarPorFechaIngreso(nodoIngresos * lista){
    char fechaIngreso[10];
    printf("Ingrese la fecha de ingreso a buscar: \n");
    fflush(stdin);
    gets(fechaIngreso);
    return strcmpi(lista->ingreso.fechaIngreso, fechaIngreso) == 0; ///retorna 1 si se cumple la condicion o 0 si no encuentra el nroIngresado en la lista;
}

int filtrarPorDNI(nodoIngresos * lista) {
    int dni;
    printf("Ingrese el DNI del paciente a buscar: \n");
    fflush(stdin);
    scanf("%d", &dni);
    return lista->ingreso.dni == dni;       ///retorna 1 si se cumple la condicion o 0 si no encuentra el nroIngresado en la lista;
}



nodoIngresos * filtrarIngreso(nodoIngresos * lista){ 
    nodoIngresos * actual = lista;
    int opcion;
    printf("Presione 1 para filtrar por nro de Ingreso \n .Presione 2 para filtrar por fecha de Ingreso \n. Presione 3 para filtrar por DNI de paciente \n.");
    fflush(stdin);
    scanf("%d", &opcion);
    while(actual != NULL){
        switch(opcion)
        {
        case 1:
            
            if(filtrarPorNroIngreso(actual)){
                return actual;
            }
            break;
        case 2: 
            if(filtrarPorFechaIngreso(actual)){
                return actual;
            }
            break;
        case 3: 
            if(filtrarPorDNI(actual)){
                return actual;
            }
            break;
        default:
            printf("Error. Ingrese una opcion valida.");
            break;
        }
        actual = actual->sig;
    }
    return NULL;

}

