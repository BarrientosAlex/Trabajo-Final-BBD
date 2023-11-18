#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Estructuras.h"



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
   aux.eliminado = 0;
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





///Funciones Paciente

nodoPaciente * crearNodoPaciente(pacientes pac){
    nodoPaciente * aux = (nodoPaciente*)malloc(sizeof(nodoPaciente));
    aux->paciente= pac;
    aux->der= NULL;
    aux->izq = NULL;
    aux->ingresos = NULL;
    return aux;
}

pacientes cargarPaciente(){
    pacientes aux;
    printf("Ingrese nombre y apellido del paciente: \n");
    fflush(stdin);
    gets(aux.apelyNom);
    printf("Ingrese la edad del paciente: \n");
    fflush(stdin);
    scanf("%d", &aux.edad);
    printf("Ingrese el dni del paciente: \n");
    fflush(stdin);
    scanf("%d", &aux.dni);
    printf("Ingrese la direccion del paciente: \n");
    fflush(stdin);
    gets(aux.direccion);
    printf("Ingrese el telefono del paciente:\n");
    fflush(stdin);
    gets(aux.telefono);
    aux.eliminado = 0;
    return aux;
}


nodoPaciente * insertarPaciente(nodoPaciente * a, pacientes pac){
    if(a == NULL){
        a = crearNodoPaciente(pac);
    }

    if(a){
        if(strcmpi(pac.apelyNom,a->paciente.apelyNom)< 0 ){
            a->izq = insertarPaciente(a->izq,pac);
        }else{
            a->der = insertarPaciente(a->der,pac);
        }
    }  //Si la comparacio nes igual a 0 significa que los nombres son iguales por lo tanto no hacemos nada para evitar duplicados.
    return a;
}

nodoPaciente * buscarPacienteDNI (nodoPaciente * a,int dni){  ///busca DNI en el arbol
   if(a == NULL){
    return NULL;
   }

   if(a->paciente.dni == dni){
    return a;
   }

  if(dni < a->paciente.dni){
    return buscarPacienteDNI(a->izq,dni);
  }else{
    return buscarPacienteDNI(a->der,dni);
  }
}


nodoPaciente * alta_de_paciente(nodoPaciente * arbolPaciente){
    pacientes nuevoPaciente = cargarPaciente();
    nodoPaciente * buscar = buscarPacienteDNI(arbolPaciente,nuevoPaciente.dni);

    if(buscar == NULL){
        arbolPaciente = insertarPaciente(arbolPaciente, nuevoPaciente);
        printf("Paciente dado de alta correctamente.\n");
    } else {
        printf("Error. El paciente con DNI %d ya existe.\n", nuevoPaciente.dni);
    }

    return arbolPaciente;
}


nodoPaciente * modificacion_de_paciente(nodoPaciente * arbolPaciente){
    int dni;
    printf("Ingrese el DNI del paciente a modificar: \n");
    fflush(stdin);
    scanf("%d", &dni);

    nodoPaciente * paciente = buscarPacienteDNI(arbolPaciente,dni);
    if(paciente != NULL){   //Si el nodo es != NULL eso significa que encontro el dni del paciente dentro del arbol
        printf("Ingrese el nuevo nombre y apellido del paciente: ");
        fflush(stdin);
        gets(paciente->paciente.apelyNom);

        printf("Ingrese la nueva edad del paciente: ");
        fflush(stdin);
        scanf("%d", &paciente->paciente.edad);

        printf("Ingrese la nueva dirección del paciente: ");
        fflush(stdin);
        gets(paciente->paciente.direccion);

        printf("Ingrese el nuevo teléfono del paciente: ");
        fflush(stdin);
        gets(paciente->paciente.telefono);

        printf("Modificación del paciente con DNI %d realizada correctamente.\n", dni);
    }else{
        printf("Error.No se encontreo el paciente con DNI %d. \n", dni);
    }
    return arbolPaciente;
}

nodoPaciente * baja_de_paciente(nodoPaciente * arbolPaciente){
    int dni;
    printf("Ingrese el DNI del paciente a dar de baja: \n");
    fflush(stdin);
    scanf("%d",&dni);
    nodoPaciente * paciente = buscarPacienteDNI(arbolPaciente, dni);
    if(paciente != NULL){
        if(paciente->ingresos == NULL){  //Si el paciente no tiene asociado ningun ingreso, marcarlo como eliminado
            paciente->paciente.eliminado = 1;
            printf("Paciente eliminado correctamente.");
        }else{
            printf("Error. El paciente tiene ingresos asociados y no se pudo eliminar correctamente.");
        }
    }else{
        printf("Error. No se encontro el paciente con DNI %d\n", dni);
    }
    return arbolPaciente;
}


///Funciones copiar al archivo





nodoPaciente * arbolToarchi(nodoPaciente * arbolPaciente, char archivoPac[]){

    arbolPaciente = alta_de_paciente(arbolPaciente);

    FILE *  archi = fopen(archivoPac, "ab");
        if(archi){
                if(arbolPaciente){
                    fwrite(&(arbolPaciente->paciente),sizeof(pacientes),1,archivoPac);
                    arbolPaciente = arbolToarchi(arbolPaciente->izq,archivoPac);
                    arbolPaciente = arbolToarchi(arbolPaciente->der,archivoPac);
                }
                fclose(archi);
        }else{
            printf("Error el archivo no se pudo abrir.");
        }
    return arbolPaciente;
}


nodoPaciente * leerArchivoPaciente(char archivoPac[], nodoPaciente * arbolPaciente){
    FILE * archi = fopen(archivoPac,"rb");
    pacientes aux;
    if(archi){
        pacientes paciente;
        while(fread(&paciente,sizeof(pacientes),1, archi) > 0){
            arbolPaciente = insertarPaciente(arbolPaciente,aux);
        }
        fclose(archi);
    }else{
        printf("Error al abrir el archivo");
    }
    return arbolPaciente;
}



void inOrder(nodoPaciente *arbolPaciente){
    if(arbolPaciente){
        inOrder(arbolPaciente->izq);
        printf("------- %s --------", arbolPaciente->paciente.apelyNom);
        printf("DNI:%d \n", arbolPaciente->paciente.dni);
        printf("Direccion: %s \n", arbolPaciente->paciente.direccion);
        printf("Edad: %d \n", arbolPaciente->paciente.edad);
        printf("Telefono: %d", arbolPaciente->paciente.telefono);
        printf("Eliminado: %d", arbolPaciente->paciente.eliminado);
        inOrder(arbolPaciente->der);
    }
}

