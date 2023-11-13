#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"

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
void mostrarOp1(){///Muestra opcion 1
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
void mostrarOp7(){///Muestra opcion final
    printf("\n|");
    printf("Ingrese 7(siete) para mostrar practicas y resultados");
    moverHorizontalAUX(64);
    printf("|\n");
    mostrarHorizontalAUX();
    printf("\n");
}
char validarOp(){
    char op[30];
    do{
        fgets(op,30,stdin);
        if (op[strlen(op) - 1] == '\n'){///Eliminar el salto de linea al final de la cadena si esta presente(la tecla enter)
            op[strlen(op) - 1] = '\0';
        }
        if(strlen(op)!= 1){///Verifica que la cadena ingresada tenga como maximo un solo caracter
            printf("Opcion no valida. Ingrese solo un caracter entre 1 y 7: ");
            continue;///Obligo a salir del if y volver a entrar al doWhile
        }
        if(!isdigit(op[0])||op[0]<'1'||op[0]>'7'){///Verifico si no es un digito o si es menor a 1 o si es mayor a 7 da error
            printf("Opcion no valida. Ingrese solo un caracter entre 1 y 7: ");
        }
    }while(strlen(op)!= 1||(!isdigit(op[0])||op[0]<'1'||op[0]>'7'));///Verifico todas las condiciones juntas
    return op[0];
}
char mostrarMenu(){///Invoca todas las funciones de mostrar y retorna la opcion
    mostrarInicio();
    mostrarfecha();
    mostrarOp1();
    mostrarOp2();
    mostrarOp3();
    mostrarOp4();
    mostrarOp5();
    mostrarOp6();
    mostrarOp7();
    char op=validarOp();
    return op;
}

