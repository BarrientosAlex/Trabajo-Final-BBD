#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Estructuras.h"



nodoIngresos * crearNodoIng (ingresos a){
    nodoIngresos * aux =(nodoIngresos*)malloc(sizeof(nodoIngresos));
    aux->ingreso = a;
    aux->practicas = NULL;
    aux->sig = NULL;
    aux->ant = NULL;
    return aux;

}
nodoIngresos * agregarPpioIngresos(nodoIngresos * lista, nodoIngresos * nuevo){ ///funcion auxiliar para agregar en orden la fecha
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
void mostrarPorFechas(nodoIngresos * listaIngresos,nodoPaciente * arbolPaciente){ ///FUNCION A CHEKEAR CON LEITO 3 CABEZAS PIENSAN MEJOR QUE DOS //La funcion va a mostrar los ingresos desde la fecha ingresada hasta la fecha ingresada por el usuario.
    char fechaDesde[10];
    char fechaHasta[10];
    printf("Ingrese la fecha desde (formato DD/MM/YYYY):");
    fflush(stdin);
    gets(fechaDesde);
    printf("Ingrese la fecha hasta (formato DD/MM/YYY)");
    fflush(stdin);
    gets(fechaHasta);

    printf("\n Listado general de ingresos:\n");
    nodoIngresos * seg = listaIngresos;

    while(seg != NULL){
        if(strcmp(seg->ingreso.fechaIngreso,fechaDesde)>= 0 && strcmp(seg->ingreso.fechaIngreso,fechaHasta) <=0){//Si la fecha del ingreso por el usuario es igual o mayor a una fecha que se encuentre en la lista de ingreso y la fecha hasta la que fue ingresada es menor o igual a una que se encuentre en la lista,
            //Ingresar funcion de mostrar la lista de ingreso.
        }

    nodoPaciente * paciente = buscarPacienteDNI(arbolPaciente,seg->ingreso.dni);   // Hacemos esto para mostrar tambien los pacientes;
    if(paciente != NULL){
        //Ingresar funcion mostrar Paciente;
    }
    seg = seg->sig;
    }
}

///Funcion para para que el usuario pueda seleccionar por que forma filtrar la busqueda y si se encuentra lo que busco dentro de la lista, que retorne ese nodo.
void mostrarIngreso(ingresos dato){
    if(dato.eliminado==0){
        printf("-----------------------\n");
        printf("Numero de ingreso :%s\n",dato.nroIngreso);
        printf("Fecha de ingreso :%s\n",dato.fechaIngreso);
        //Dni lo muestro una sola vez antes
        printf("Matricula : %i",dato.matricula);
    }
}
nodoIngresos * filtrarPorNroIngreso(nodoPaciente* arbol){ ///anteriormente pedir el paciente por el cual queremos buscar el ingreso
    nodoIngresos* aux=NULL;
    if(arbol){
        int nroIngreso;                                       /// por parametro hacer un a busqueda por dni y lo que retorne utilizarlo
        printf("Ingrese el nro de Ingreso a buscar: \n");
        fflush(stdin);
        scanf("%d", &nroIngreso);
        nodoIngresos* seg=arbol->ingresos;
        while(seg!=NULL && aux==NULL){
            if(seg->ingreso.nroIngreso==nroIngreso){
                aux=seg;
            }
            seg=seg->sig;
        }
    }
     return aux;  ///retorna NULL si no lo encontro, o el puntero a todos los datos del ingreso
}
nodoIngresos* filtrarPorFechaIngreso(nodoPaciente* arbol){ ///anteriormente tenemos que haber buscado el paciente del que quermos el ingreso
    nodoIngresos* aux=NULL;
    if(arbol){
        char fechaIngreso[10];
        printf("Ingrese la fecha de ingreso a buscar: \n");
        fflush(stdin);
        gets(fechaIngreso);
        ///aca tiene que haber una funcion para validar la fecha que el usuario pone /// att lucho
        nodoIngresos* seg= arbol->ingresos;
        while(seg!=NULL && aux==NULL){
            if(strcmpi(seg->ingreso.fechaIngreso, fechaIngreso) == 0){
                aux=seg;
            }
            seg=seg->sig;
        }
    }
    return aux;  ///retorna 1 si se cumple la condicion o 0 si no encuentra el nroIngresado en la lista;
}
void filtrarPorDNI(nodoPaciente * arbol) { ///Mostrara todos los ingresos de la persona que desee la cual anteriormente debemos corroborar que exista o no
   nodoIngresos* seg= NULL;
   if(arbol){
       printf("---------------\n");
        printf("DNI: %i",arbol->paciente.dni);
        while(seg!=NULL){
            mostrarIngreso(seg->ingreso);
            seg=seg->sig;
        }
   }
}



nodoIngresos * filtrarIngreso(nodoPaciente* arbol){ /// anteriormente tenemos que llamar a buscar por dni para saber si existe o no
    nodoIngresos* aux=NULL;
    if(arbol){
        int opcion; ///validar para que no pongan cualquier cosa ATTENTAMENTE LUCHOIDE
        printf("Presione 1 para filtrar por nro de Ingreso \n .Presione 2 para filtrar por fecha de Ingreso \n. Presione 3 para filtrar por DNI de paciente \n.");
        fflush(stdin);
        scanf("%d", &opcion);
            switch(opcion)
            {
            case 1:
                aux = filtrarPorNroIngreso(arbol);
                break;
            case 2:
                aux= filtrarPorFechaIngreso(arbol);
                break;
            case 3:
                filtrarPorDNI(arbol);
                break;
            default:
                printf("Error. Ingrese una opcion valida.");
                break;
            }
    } else{
        printf("Paciente no existente.\n");
    }

    return aux;

}

ingresos cargarIngresos(){
    ingresos aux;
    time_t t;
    struct tm * tm_info;
    time(&t);
    tm_info = localtime(&t);
    printf("Ingrese numero de ingreso: \n");
    fflush(stdin);
    scanf("%d", &aux.nroIngreso);
    strftime(aux.fechaIngreso,sizeof(aux.fechaIngreso),"%d/%m/%Y", tm_info);
    printf("Ingrese la fecha del retiro: \n");
    fflush(stdin);
    gets(aux.fechaRetiro);
    printf("Ingrese dni del paciente: \n");
    fflush(stdin);
    scanf("%d", &aux.dni);
    printf("Ingrese matricula del Profesional: \n");
    fflush(stdin);
    scanf("%d", &aux.matricula);
    aux.eliminado = 0;
    return aux;
}


nodoPaciente * alta_de_ingreso(nodoPaciente * arbolPaciente){
    int dni;
    printf("Ingrese DNI del paciente para dar de alta el ingreso: \n");
    fflush(stdin);
    scanf("%d",&dni);

    nodoPaciente * paciente = buscarPacienteDNI(arbolPaciente,dni);

    if(paciente != NULL){
        if(paciente->paciente.eliminado == 0){
            ingresos nuevoIng = cargarIngresos();
            nodoIngresos * nuevoNodo = crearNodoIng(nuevoIng);
            nuevoNodo->practicas = Alta_de_pxi(nuevoNodo->practicas);
            paciente->ingresos = agregarOrdenFecha(paciente->ingresos,nuevoNodo);
            printf("Ingreso dado de alta correctamente.\n");
        }else{
        printf("Error. El paciente con DNI %d ha sido eliminado. \n",dni);
        }
    }else{
        printf("Error.No se encontro el DNI %d del paciente \n" ,dni);
    }

    return arbolPaciente;
}
