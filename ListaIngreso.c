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


void mostrarPorFechas(nodoIngresos * listaIngresos,nodoPaciente * arbolPaciente){ //La funcion va a mostrar los ingresos desde la fecha ingresada hasta la fecha ingresada por el usuario.
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

ingresos cargarIngresos(){
    ingresos aux;
    int dniString[10];
    char numString[10];
    int fechaValida = 0;
    int dniValido = 0;
    time_t t;
    struct tm * tm_info;
    time(&t);
    tm_info = localtime(&t);

        printf("Ingrese numero de ingreso: \n");
        fflush(stdin);
        scanf("%d", &aux.nroIngreso);
        strftime(aux.fechaIngreso,sizeof(aux.fechaIngreso),"%d/%m/%Y", tm_info);
        printf("%s", aux.fechaIngreso);

    do{
        printf("Ingrese la fecha del retiro(formato dd/mm/yy): \n");
        fflush(stdin);
        gets(aux.fechaRetiro);
        fechaValida =validarFecha(aux.fechaRetiro);
        if(fechaValida == 1){
            printf("Error.Ingrese una fecha de retiro valido. \n");
        }
    }while(fechaValida != 0);
    do{
        printf("Ingrese dni del paciente: \n");
        fflush(stdin);
        scanf("%d", &aux.dni);
        sprintf(dniString,"%d",aux.dni);
        dniValido = validarDNI(dniString);
        if(dniValido == 1){
            printf("Error.Ingrese DNI valido. \n");
        }
    }while(dniValido !=0);


    printf("Ingrese matricula del Profesional: \n");
    fflush(stdin);
    scanf("%d", &aux.matricula);
    aux.eliminado = 0;
    return aux;
}

int validarFecha(char *fechaRetiro){
    int cantNum =strlen(fechaRetiro);
    int flag = 0;
    int dia = (fechaRetiro[0]-'0')* 10 + fechaRetiro[1]-'0'; /// Paso el los dos primeras posiciones del string a un tipo int (Le resto el caracter - '0' que en la tabla ascii en el numero a 48 para convertirlo en tipo int
    int mes = (fechaRetiro[3]-'0') *10 +fechaRetiro[4]- '0'; /// Por lo tanto si en la posicion del string seleccionado es '1' le restas '0' y se busca su numero en la tabla ascii (49) - (48) y da 1 y se convierte en tipo int
    int anio = (fechaRetiro[6]-'0') * 10 + fechaRetiro[7]-'0';

    if(cantNum ==8){
        for(int i = 0;i<cantNum;i++){
            if(!isdigit(fechaRetiro[i])&& fechaRetiro[i] != '/'){   /// Para que se permita el uso de la barra entre el medio de dia, mes y año
                flag =1;
            }
        }

        if(flag == 0){
            if(dia < 1 || dia>31 || mes<01 || mes>12 || anio<23 ||anio>33){
                flag = 1;

            }
          }

        if(anio ==23){
            if(mes<11 || mes >12){
                flag = 1;
            }
        }

    }else{
        flag = 1;
    }

    return flag;

}



nodoIngresos * alta_de_ingreso(nodoIngresos * listaIngresos,nodoPaciente * arbolPaciente){
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
            listaIngresos = agregarOrdenFecha(listaIngresos,nuevoNodo);
            printf("Ingreso dado de alta correctamente.\n");
        }else{
        printf("Error. El paciente con DNI %d ha sido eliminado. \n",dni);
        }
    }else{
        printf("Error.No se encontro el DNI %d del paciente \n" ,dni);
    }

    return listaIngresos;
}
