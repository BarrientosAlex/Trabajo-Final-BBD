#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "auxMenu.h"
#include "user.h"

int validarPermisos(int tipoUser,char op,int flag){
   switch (tipoUser){
        case 1:{
            flag=0;
            break;
        }
        case 2:{
            if(op!='5'&&op!='6'&&op!='10'){
                printf("Necesitas permisos para esta opcion vuelve a intentar.\n");
                system("pause");
            }else{
                flag=0;
            }
            break;
        }
        case 3:{
            if(op=='4'||op=='5'||op=='6'||op=='7'||op=='8'){
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
    char op=mostrarMenu();
    int flag=1;
    while(flag==1){
        flag=validarPermisos(tipoUser,op,flag);
        if(flag==1){
            system("cls");
            op=mostrarMenu();
        }
    }
}
