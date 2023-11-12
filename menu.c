#include <stdio.h>
#include <string.h>
#include "menu.h"

void mostrarHorizontalAUX(){
    for(int i=0;i<50;i++){
        printf("-");
    }
    printf("\n");
}
void moverHorizontalAUX(int tope){
    for(int i=0;i<tope;i++){
        printf(" ");
    }
}
void mostrarMenu(){
    mostrarAuxiliar();
    moverHorizontalAUX(10);
    printf("|MENU");
}