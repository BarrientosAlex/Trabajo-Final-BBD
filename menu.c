#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "auxMenu.h"
#include "user.h"
#include "Estructuras.h"
#include "windows.h"

int validarPermisos(int tipoUser,char op,int flag){
   switch (tipoUser){
        case 1:{
            flag=0;
            break;
        }
        case 2:{
            if(op!=5&&op!=6&&op!=10){
                printf("Necesitas permisos para esta opcion vuelve a intentar.\n");
                system("pause");
            }else{
                flag=0;
            }
            break;
        }
        case 3:{
            if(op==4||op==5||op==6||op==7||op==8){
                printf("Necesitas permisos para esta opcion, vuelve a intentar.\n");
                system("pause");
            }else{
                flag=0;
            }
            break;
        }
    }
    return flag;
}
void menu(){
    int tipoUser=login("usuarios.bin");
    system("pause");
    system("cls");
    int op=mostrarMenu();
    printf("NUMERO: %d", op);
    int flag=1;
    while(flag==1){
        flag=validarPermisos(tipoUser,op,flag);
        if(flag==1){
            system("cls");
            op=mostrarMenu();
        }
    }
    char archivoPacientes[]=("pacientes.bin");
    char archivoIngresos[]=("ingresos.bin");
    char archivoPxI[]=("pxi.bin");
    nodoPaciente* arbolMother=NULL;
    printf("f");
    arbolMother=cargarArbolDesdeArchivo("pacientes.bin",arbolMother);
    arbolMother=cargarIngresosDesdeArchivo("ingresos.bin",arbolMother);
    arbolMother=pasarPracticasAlArbolArchivo("pxi.bin",arbolMother);
    system("cls");
    printf("Leido correctamente");
    printf("a");
    switch(op){
        case 0:{///Generar ingreso
            arbolMother=alta_de_ingreso(arbolMother);
            break;
        }
        case 1:{///Mod ingreso
            printf("H");
            nodoPaciente* encontrado;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            if(encontrado){
                aux=filtrarIngreso(arbolMother);
                printf("\nIngrese nueva fecha de ingreso: ");
                fflush(stdin);
                gets(aux->ingreso.fechaIngreso);
                printf("\nIngrese nueva fecha de retiro: ");
                fflush(stdin);
                gets(aux->ingreso.fechaRetiro);
                printf("\nIngrese nueva matricula: ");
                fflush(stdin);
                scanf("%i",&aux->ingreso.matricula);
            }else{
                printf("\nNo se encontro el dni %i",dni);
            }
            modificarArchivoIngresos(archivoIngresos,aux->ingreso);
            break;
        }
        case 2:{///Generar practica
            nodoPaciente* encontrado=NULL;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            aux=filtrarIngreso(arbolMother);
            aux->practicas=Alta_de_pxi(aux,aux->ingreso.nroIngreso);
            agregarPxialArchivo(archivoPxI,aux->practicas->pXi);
            break;
        }
        case 3:{///Mod practica
            nodoPaciente* encontrado=NULL;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            aux=filtrarIngreso(arbolMother);
            aux->practicas=modificacion_de_pxi(aux->practicas);
            modificarArchivoPXI(archivoPxI,aux->practicas->pXi);
            break;
        }
        case 4:{///Eliminar practica
            nodoPaciente* encontrado=NULL;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            aux=filtrarIngreso(arbolMother);
            aux->practicas=Baja_de_pxi(aux->practicas);
            modificarArchivoPXI(archivoPxI,aux->practicas->pXi);
            break;
        }
        case 5:{///Cargar resultado
            nodoPaciente* encontrado=NULL;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            aux=filtrarIngreso(arbolMother);///Mostrar practicas

            int numPractica;
            printf("\nIngrese nro.Practica a modificar");///Validarlo
            scanf("%i",&numPractica);
            nodoPracticasXingreso* auxPractica=NULL;
            auxPractica=buscarPractica(aux->practicas,numPractica);
            printf("\nIngrese resultado de la practica");
            gets(auxPractica->pXi.resultado);
            modificarArchivoPXI(archivoPxI,auxPractica->pXi);
            break;
        }
        case 6:{///Mod resultado
            nodoPaciente* encontrado=NULL;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            aux=filtrarIngreso(arbolMother);///Mostrar practicas

            int numPractica;
            printf("\nIngrese nro.Practica a modificar");///Validarlo
            scanf("%i",&numPractica);
            nodoPracticasXingreso* auxPractica=NULL;
            auxPractica=buscarPractica(aux->practicas,numPractica);
            printf("\nIngrese nuevo resultado de la practica");
            gets(auxPractica->pXi.resultado);
            modificarArchivoPXI(archivoPxI,auxPractica->pXi);
            break;
        }
        case 7:{///Eliminar resultado
            nodoPaciente* encontrado=NULL;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            aux=filtrarIngreso(arbolMother);///Mostrar practicas

            int numPractica;
            printf("\nIngrese nro.Practica a buscar");///Validarlo
            scanf("%i",&numPractica);
            nodoPracticasXingreso* auxPractica=NULL;
            auxPractica=buscarPractica(aux->practicas,numPractica);
            strcpy(auxPractica->pXi.resultado,"\0");
            modificarArchivoPXI(archivoPxI,auxPractica->pXi);
            break;
        }
        case 8:{///Eliminar paciente
            nodoPaciente* auxArbol=NULL;
            auxArbol=baja_de_paciente(arbolMother);
            modificarArchivoPaciente(archivoPacientes,auxArbol->paciente);
            break;
        }
        case 9:{///Mod paciente
            nodoPaciente* auxArbol=modificacion_de_paciente(arbolMother);
            modificarArchivoPaciente(archivoPacientes,auxArbol->paciente);
            break;
        }
        case 10:{///Mostrar arbol
            inOrder(arbolMother);
            break;
        }
    }

}
