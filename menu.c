#include <stdio.h>
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

void mostrarMenu(){///Muestro el menu
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