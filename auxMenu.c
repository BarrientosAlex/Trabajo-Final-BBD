#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "auxMenu.h"

void mostrarHorizontalAUX(){///Muestra horizontalmente guiones
    for (int i=0;i<118;i++) {
        printf("-");
    }
}
void moverHorizontalAUX(int tope) {///Mueve horizontalmente en pantalla posiciones
    for (int i = 0; i < tope; i++) {
        printf(" ");
    }
}
void mostrarInicio(){///Muestra el menu
    mostrarHorizontalAUX();
    printf("\n");
    printf("|");
    moverHorizontalAUX(56);
    printf("MENU");
    moverHorizontalAUX(56);
    printf("|\n");
}
void mostrarfecha(){///Muestra la fecha
    time_t tiempoActual;
    struct tm* tmLocal;
    time(&tiempoActual);
    tmLocal=localtime(&tiempoActual);
    printf("|");
    moverHorizontalAUX(53);
    printf("%02d/%02d/%04d",tmLocal->tm_mday, tmLocal->tm_mon+1, tmLocal->tm_year+1900);
    moverHorizontalAUX(53);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOpCrear(){}
void mostrarOp1(){///Muestra opcion 1
    printf("\n|");
    printf("Ingrese 0(cero) para generar ingreso de paciente");
    moverHorizontalAUX(68);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp2(){
    printf("\n|");
    printf("Ingrese 1(uno) para modificar ingreso de paciente");
    moverHorizontalAUX(67);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp3(){
    printf("\n|");
    printf("Ingrese 2(dos) para generar ingreso de practica");
    moverHorizontalAUX(69);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp4(){
    printf("\n|");
    printf("Ingrese 3(tres) para modificar practicas");
    moverHorizontalAUX(76);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp5(){
    printf("\n|");
    printf("Ingrese 4(cuatro) para eliminar Practica");
    moverHorizontalAUX(76);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp6(){
    printf("\n|");
    printf("Ingrese 5(cinco) para cargar resultados");
    moverHorizontalAUX(77);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp7(){
    printf("\n|");
    printf("Ingrese 6(seis) para modificar resultados");
    moverHorizontalAUX(75);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp8(){
    printf("\n|");
    printf("Ingrese 7(siete) para eliminar resultados");
    moverHorizontalAUX(75);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp9(){
    printf("\n|");
    printf("Ingrese 8(ocho) para eliminar paciente");
    moverHorizontalAUX(78);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp10(){
    printf("\n|");
    printf("Ingrese 9(nueve) para modificar paciente");
    moverHorizontalAUX(76);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp11(){///Muestra opcion final
    printf("\n|");
    printf("Ingrese 10(diez) para mostrar practicas y resultados");
    moverHorizontalAUX(64);
    printf("|\n");
    mostrarHorizontalAUX();
    printf("\n");
}

int validarOp(){
    char op[30];
    int num;
    do {
        fgets(op, 30, stdin);
        op[strcspn(op, "\n")] = '\0'; // elimina el salto de línea final
        num = atoi(op);

        if (strlen(op) > 3 || !isdigit(op[0]) || (strlen(op) == 3 && !isdigit(op[1])) || (num < 0 || num > 10)) {
            printf("Opcion no valida. Ingrese un numero entre 0 y 10: ");
        }
    } while (strlen(op) > 3 || !isdigit(op[0]) || (strlen(op) == 3 && !isdigit(op[1])) || (num < 0 || num > 10));

    return num; // Devuelvo directamente el valor numérico ingresado
}
    ///char op[30];
    /*int num;
    do{
        printf("Ingrese un numero del 0 al 10: ");
        if(scanf("%i",&num)!=1){
            printf("Error: Ingresa un num valido del 0 al 10.\n");
            fflush(stdin);
        }else if(num<0||num>10){
            printf("Error: El numero debe estar entre 0 y 10.\n");
        }else{
            break;
        }
        /*fflush(stdin);
        gets(op);
        op[strcspn(op,"\n")]='\0';///elimina el salto de lina final
        num=atoi(op);///paso el arreglo a un int
        if(strlen(op)>2||!isdigit(op[0])||(strlen(op)>1 && !isdigit(op[1]))||(num<0||num>10)){///si son mas de dos char o si la pos 0 no es digito
            printf("Opcion no valida. Ingrese un numero entre 0 y 10: ");                     ///o si son dos char que la segunda sea un digito y por ultimo que sea entre 0 y 10
        }*/
    /*}while();///Verifico todas las condiciones juntas
    //strlen(op)>2||!isdigit(op[0])||(strlen(op)>1 && !isdigit(op[1]))||(num<0||num>10)
    return strdup(op);*/

int mostrarMenu(){///Invoca todas las funciones de mostrar y retorna la opcion
    mostrarInicio();
    mostrarfecha();
    mostrarOp1();
    mostrarOp2();
    mostrarOp3();
    mostrarOp4();
    mostrarOp5();
    mostrarOp6();
    mostrarOp7();
    mostrarOp8();
    mostrarOp9();
    mostrarOp10();
    mostrarOp11();
    int op=validarOp();
    printf("\nOpcion: %i",op);
    return op;
}

