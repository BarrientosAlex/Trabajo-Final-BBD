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
    arbolMother=cargarArbolDesdeArchivo("pacientes.bin",arbolMother);
    arbolMother=cargarIngresosDesdeArchivo("ingresos.bin",arbolMother);
    arbolMother=pasarPracticasAlArbolArchivo("pxi.bin",arbolMother);
    system("cls");
    Sleep(30);
    switch(op){
        case 0:{///Generar ingreso
            arbolMother=alta_de_ingreso(arbolMother);
            break;
        }
        case 1:{///Mod ingreso
            nodoPaciente* encontrado;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            if(encontrado){
                system("cls");
                filtrarPorDNI(arbolMother);
                aux=filtrarIngreso(arbolMother);
                printf("\nIngrese nueva fecha de retiro: ");
                fflush(stdin);
                gets(aux->ingreso.fechaRetiro);
                printf("\nIngrese nueva matricula: ");
                fflush(stdin);
                scanf("%i",&aux->ingreso.matricula);
            }else{
                printf("\nNo se encontro el dni %i",dni);
            }
            modificarArchivoIngresos("ingresos.bin",aux->ingreso);
            break;
        }
        case 2:{///Generar practica
            nodoPaciente* encontrado=NULL;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            filtrarPorDNI(encontrado);
            aux=filtrarIngreso(arbolMother);
            if(aux){
                aux->practicas=Alta_de_pxi(aux->practicas,aux->practicas->pXi.nroIngreso);
            }
            break;
        }
        case 3:{///Mod practica
            nodoPaciente* encontrado=NULL;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            filtrarPorDNI(encontrado);
            aux=filtrarIngreso(arbolMother);
            if(aux){
                mostrarPxi(aux->practicas);
                aux->practicas=modificacion_de_pxi(aux->practicas);
                modificarArchivoPXI("pxi.bin",aux->practicas->pXi);
            }
            break;
        }
        case 4:{///Eliminar practica
            nodoPaciente* encontrado=NULL;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            filtrarPorDNI(encontrado);
            aux=filtrarIngreso(arbolMother);
            mostrarPxi(aux->practicas);
            aux->practicas=Baja_de_pxi(aux->practicas);
            modificarArchivoPXI(archivoPxI,aux->practicas->pXi);
            break;
        }
        case 5:{///Cargar resultado
            nodoPaciente* encontrado=NULL;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            filtrarPorDNI(encontrado);
            aux=filtrarIngreso(arbolMother);///Mostrar practicas
            if(aux){
                mostrarPxi(aux->practicas);
                char numPractica[30];
                int valido=0;
                do{
                    printf("\nIngrese nro.Practica a modificar: ");///Validarlo
                    fflush(stdin);
                    gets(numPractica);
                    valido=validarNumero(numPractica);
                    if(valido==1){
                        printf("\nError: Ingrese un num.Practica valido. \n");
                    }
                }while(valido!=0);
                nodoPracticasXingreso* auxPractica=NULL;
                int nPractica=atoi(numPractica);
                auxPractica=buscarPractica(aux->practicas,nPractica);
                printf("\nIngrese resultado de la practica: ");
                fflush(stdin);
                gets(auxPractica->pXi.resultado);
                modificarArchivoPXI("pxi.bin",auxPractica->pXi);
                break;
            }
        }
        case 6:{///Mod resultado
            nodoPaciente* encontrado=NULL;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            filtrarPorDNI(encontrado);
            aux=filtrarIngreso(arbolMother);///Mostrar practicas
            if(aux){
                mostrarPxi(aux->practicas);
                char numPractica[30];
                int valido=0;
                do{
                    printf("\nIngrese nro.Practica a modificar: ");///Validarlo
                    fflush(stdin);
                    gets(numPractica);
                    valido=validarNumero(numPractica);
                    if(valido==1){
                        printf("\nError: Ingrese un num.Practica valido. \n");
                    }
                }while(valido!=0);
                nodoPracticasXingreso* auxPractica=NULL;
                int nPractica=atoi(numPractica);
                auxPractica=buscarPractica(aux->practicas,nPractica);
                printf("\nIngrese nuevo resultado de la practica: ");
                fflush(stdin);
                gets(auxPractica->pXi.resultado);
                modificarArchivoPXI("pxi.bin",auxPractica->pXi);
                break;
            }
        }
        case 7:{///Eliminar resultado
            nodoPaciente* encontrado=NULL;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            filtrarPorDNI(encontrado);
            aux=filtrarIngreso(arbolMother);///Mostrar practicas
            if(aux){
                mostrarPxi(aux->practicas);
                char numPractica[30];
                int valido=0;
                do{
                    printf("\nIngrese nro.Practica a modificar: ");///Validarlo
                    fflush(stdin);
                    gets(numPractica);
                    valido=validarNumero(numPractica);
                    if(valido==1){
                        printf("\nError: Ingrese un num.Practica valido. \n");
                    }
                }while(valido!=0);
                nodoPracticasXingreso* auxPractica=NULL;
                int nPractica=atoi(numPractica);
                auxPractica=buscarPractica(aux->practicas,nPractica);
                printf("\nEl resultado a sido eliminado correctamente. \n");
                strcpy(auxPractica->pXi.resultado,"\0");///resultado eliminado asignandole null
                modificarArchivoPXI("pxi.bin",auxPractica->pXi);
                break;
            }
        }
        case 8:{///Eliminar paciente
            nodoPaciente* auxArbol=NULL;
            arbolMother=baja_de_paciente(arbolMother);
            break;
        }
        case 9:{///Mod paciente
            arbolMother=modificacion_de_paciente(arbolMother);
            break;
        }
        case 10:{///Mostrar arbol
            inOrder(arbolMother);
            break;
        }
    }
}
