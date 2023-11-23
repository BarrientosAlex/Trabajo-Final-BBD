#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include "menu.h"
#include "auxMenu.h"
#include "user.h"
#include "Estructuras.h"

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
void mostrarSubMenu(){
    printf("----------------------------------------------------");
    printf("\nIngrese una opcion");
    printf("\n1.Lista general de empleados(Ordenados por AyN)");
    printf("\n2.Lista general de pacientes");
    printf("\n3.Lista general de las practicas por ingresos");
    printf("\n4.Lista general de los ingresos de los pacientes");
    printf("\n5.Mostrar un ingreso");
    printf("\n6.Mostrar un empleado por dni");
    printf("\n7.Mostrar un paciente");
    printf("\n8.Mostrar una practica por ingreso");
    printf("\n9.Mostrar solo admin\n");
}
void menu(){
    nodoPaciente* arbolMother=inicArbol();
    arbolMother=cargarArbolDesdeArchivo("pacientes.bin",arbolMother);
    arbolMother=cargarIngresosDesdeArchivo("ingresos.bin",arbolMother);
    arbolMother=pasarPracticasAlArbolArchivo("pxi.bin",arbolMother);
    int tipoUser=login("usuarios.bin");
    system("pause");
    system("cls");
    //char eleccion;
    int op;
    int flag;
    op=mostrarMenu();
    flag=1;
    while(flag==1){
        flag=validarPermisos(tipoUser,op,flag);
        if(flag==1){
            system("cls");
            op=mostrarMenu();
        }
    }
    //int volverMenu=1;
    //while(volverMenu==1){
    system("cls");
    Sleep(30);
    switch(op){
        case 0:{///Generar ingreso
            //printf("\nDesea volver al menu? Presione (s): ");
            //fflush(stdin);
            //scanf("%c",&eleccion);
            //if(eleccion=='s'||eleccion=='S'){
                //volverMenu=1;
                //system("pause");
            //}else{
            //volverMenu=0;
            arbolMother=alta_de_ingreso(arbolMother);
            //}
            break;
        }
        case 1:{///Mod ingreso
            nodoPaciente* encontrado;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            int fechaValida = 0;
            int matriculaValida = 0;
            char matriculaString[20];
            if(encontrado){
                system("cls");
                filtrarPorDNI(arbolMother);
                aux=filtrarIngreso(arbolMother);
                if(aux){
                    do{
                        printf("\nIngrese nueva fecha de retiro(formato dd/mm/yyyy): ");
                        fflush(stdin);
                        gets(aux->ingreso.fechaRetiro);
                        fechaValida = validarFecha(aux->ingreso.fechaIngreso);
                        if(fechaValida == 1){
                            printf("Error. Ingrese una fecha de retiro valida.");
                        }
                    }while(fechaValida != 0);
                    do{
                        printf("\nIngrese nueva matricula: ");
                        fflush(stdin);
                        scanf("%i",&aux->ingreso.matricula);
                        sprintf(matriculaString,"%d",aux->ingreso.matricula);
                        matriculaValida = validarMatricula(matriculaString);
                        if(matriculaValida == 1){
                            printf("Error.Ingrese matricula Valida.");
                        }
                    }while(matriculaValida != 0);
                }else{
                    printf("\nNo se encontro el dni %i",dni);
                }
                modificarArchivoIngresos("ingresos.bin",aux->ingreso);
            }
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
                system("cls");
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
            system("cls");
            mostrarPxi(aux->practicas);
            aux->practicas=Baja_de_pxi(aux->practicas);
            modificarArchivoPXI("pxi.bin",aux->practicas->pXi);
            break;
        }
        case 5:{///Cargar resultado
            nodoPaciente* encontrado=NULL;
            int dni=validarDNIyEncontrar(arbolMother,&encontrado);
            nodoIngresos* aux=NULL;
            filtrarPorDNI(encontrado);
            aux=filtrarIngreso(arbolMother);///Mostrar practicas
            if(aux){
                system("cls");
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
                system("cls");
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
                system("cls");
                mostrarPxi(aux->practicas);
                char numPractica[30];
                int valido=0;
                do{
                    printf("\nIngrese nro.Practica del resultado a eliminar: ");///Validarlo
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
            arbolMother=baja_de_paciente(arbolMother);
            break;
        }
        case 9:{///Mod paciente
            arbolMother=modificacion_de_paciente(arbolMother);
            break;
        }
        case 10:{///Mostrar arbol
            char opcion;
            int flag=1;
            nodoIngresos* aux=NULL;
            nodoPaciente* paux=NULL;
            do{
                mostrarSubMenu();
                fflush(stdin);
                scanf("%c",&opcion);
                switch(opcion){
                    case '1':{///lista emp
                        system("cls");
                        mostrarArchivoOrdenado("usuarios.bin",tipoUser);
                        break;
                    }
                    case '2':{///lista pacientes ordenado porNyA
                        int validos=0;
                        system("cls");
                        stPacientes* array=PacientesOrdenados(arbolMother,&validos);
                        mostrarPacientesOrdenados(array,validos);
                        break;
                    }
                    case '3':{///lista pxi
                        system("cls");
                        recorrerArbolParaMostrarPracticas(arbolMother);
                        break;
                    }
                    case '4':{///lista ingresos
                        char fechaDesde[10];
                        char fechaHasta[10];
                        int validarFecha=0;
                        do{
                            printf("\nIngrese la fecha desde (formato DD/MM/YYYY):\n");
                            fflush(stdin);
                            gets(fechaDesde);
                            validarFecha=validarFechaIngreso(fechaDesde);
                            if(validarFecha==0){
                                printf("\nError. Ingrese una fecha valida.\n");
                            }
                        }while(validarFecha!=1);
                        do{
                            printf("\nIngrese la fecha hasta (formato DD/MM/YYY):\n");
                            fflush(stdin);
                            gets(fechaHasta);
                            validarFecha=validarFechaIngreso(fechaHasta);
                            if(validarFecha==0){
                                printf("\nError. Ingrese una fecha valida.\n");
                            }
                        }while(validarFecha!=1);
                        system("cls");
                        recorrerArbol(arbolMother,fechaDesde,fechaHasta);
                        break;
                    }
                    case '5':{///ingreso
                        aux=filtrarIngresoParaMostrar(arbolMother);
                        system("cls");
                        if(aux){
                            mostrarIngreso(aux);
                        }
                        break;
                    }
                    case '6':{///empleado
                        int dni,dniValido=0;
                        char dniString[10];
                        do{
                            printf("Ingrese el dni del paciente: \n");
                            fflush(stdin);
                            scanf("%d", &dni);
                            sprintf(dniString,"%d",dni);
                            dniValido = validarDNI(dniString);
                            if(dniValido == 1){
                                printf("Error.Ingrese DNI valido. \n");
                            }
                        }while(dniValido !=0);
                        system("cls");
                        consultaEmpleado("usuarios.bin",dni,tipoUser);
                        break;
                    }
                    case '7':{///paciente por dni
                        int dni=validarDNIyEncontrar(arbolMother,&paux);
                        system("cls");
                        inOrder(paux);///muestra eliminados tmb, chequear
                        break;
                    }
                    case '8':{///pxi
                        char prefijo[15];
                        int prefijoValidado;
                        do{
                            printf("\nIngrese prefijo de las practicas a mostrar: \n");          ///Validar
                            fflush(stdin);
                            gets(prefijo);
                            prefijoValidado = validarPrefijo(prefijo);
                            if(prefijoValidado==1){
                                printf("Error.Ingrese un prefijo Valido.");
                            }
                        }while(prefijoValidado!=0);
                        system("cls");
                        buscarPrefijoPaciente(arbolMother,prefijo);
                        break;
                    }
                    case '9':{///admin
                        system("cls");
                        if(tipoUser==1){
                            inOrder(arbolMother);
                        }else{
                            printf("\nError. Necesitas permisos del messias.\n");
                        }
                        break;
                    }
                    default:{
                        printf("\nError. Ingrese una opcion valida. ");
                        flag=0;
                        system("cls");
                    }
                }
            }while(flag!=1);
            break;
        }
    }
    ///}
}
