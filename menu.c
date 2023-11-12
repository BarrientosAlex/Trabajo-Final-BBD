#include <stdio.h>
<<<<<<< Updated upstream
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
=======
#include <stdlib.h>
#include <time.h>
#include "menu.h"

void mostrarHorizontalAUX(){///Agrega horizontalmente lineas
    for (int i=0; i<118;i++){
        printf("-");
    }
}
void moverHorizontalAUX(int tope){///Rellena espacios en blanco hasta el tope
    for (int i=0;i<tope;i++){
        printf(" ");
    }
}
struct tm* tmLocal(){///Retorna un puntero a la hora y fecha actual
    time_t tiempoActual;
    struct tm* tiempoLocal;
    time(&tiempoActual);
    tiempoLocal=localtime(&tiempoActual);
    return tiempoLocal;
}
void mostrarEncabezado(){///Muestro encabezado
    mostrarHorizontalAUX();
    printf("\n");
    printf("|");
    moverHorizontalAUX(54);
    printf("MENU");
    moverHorizontalAUX(58);
    printf("|\n");
    printf("|");
    moverHorizontalAUX(45);
    printf("%.24s", asctime(tmLocal()));
    moverHorizontalAUX(47);
    printf("|\n");
    mostrarHorizontalAUX();
}
void mostrarOp1(){
    printf("\n");
    printf("|");

}
void mostrarMenu(){///Muestro el menu
    mostrarEncabezado();

}
>>>>>>> Stashed changes
