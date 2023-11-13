#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"

void mostrarHorizontalAUX(){
    for (int i=0;i<118;i++) {
        printf("-");
    }
}
void moverHorizontalAUX(int tope) {
    for (int i = 0; i < tope; i++) {
        printf(" ");
    }
}
void mostrarInicio(){
    mostrarHorizontalAUX();
    printf("\n");
    printf("|");
    moverHorizontalAUX(56);
    printf("MENU");
    moverHorizontalAUX(56);
    printf("|\n");
}
void mostrarfecha(){
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
void mostrarOp1(){
    printf("\n|");
    printf("Ingrese 1(uno) para generar ingreso de paciente");
    moverHorizontalAUX(69);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp2(){
    printf("\n|");
    printf("Ingrese 2(dos) para generar ingreso de practica");
    moverHorizontalAUX(69);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp3(){
    printf("\n|");
    printf("Ingrese 3(tres) para eliminar paciente");
    moverHorizontalAUX(78);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp4(){
    printf("\n|");
    printf("Ingrese 4(cuatro) para eliminar practicas");
    moverHorizontalAUX(75);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp5(){
    printf("\n|");
    printf("Ingrese 5(cinco) para cargar resultados");
    moverHorizontalAUX(77);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp6(){
    printf("\n|");
    printf("Ingrese 6(seis) para eliminar resultados");
    moverHorizontalAUX(76);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp7(){
    printf("\n|");
    printf("Ingrese 7(siete) para mostrar practicas y resultados");
    moverHorizontalAUX(64);
    printf("|\n");
    mostrarHorizontalAUX();
    printf("\n");
}
int mostrarMenu() {
    mostrarInicio();
    mostrarfecha();
    mostrarOp1();
    mostrarOp2();
    mostrarOp3();
    mostrarOp4();
    mostrarOp5();
    mostrarOp6();
    mostrarOp7();
    char op=getchar();
    printf("%c",op);
}

