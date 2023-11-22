#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "user.h"
#include "Estructuras.h"
#define ff fflush(stdin);
void crearArchivouser(FILE* archivo){
    if(archivo){
        stUsuario a;
        strcpy(a.nombreUsuario,"admin");
        strcpy(a.contrasena,"admin123");
        a.dni=1000000;
        strcpy(a.nombreYapellido,"ADMIN");
        strcpy(a.perfil,"admin");
        fwrite(&a,sizeof(stUsuario),1,archivo);
    }
}
void mostrarArchivoUser(char archivo[]){
    FILE*archi=fopen(archivo,"rb");
    stUsuario aux;
    if(archi){
        while(fread(&aux,sizeof(stUsuario),1,archi)>0){
            printf("Nombre usuario: %s\n",aux.nombreUsuario);
            printf("DNI : %i\n",aux.dni);
        }
    }else{
        printf("archivo no creado");
    }

}
int validarNombreUser(char archivo[], char usuario[]){//funcion para saber si existe el usuario, en caso de que exista debera ingresar otro.
    int flag=0;
    FILE*archi=fopen(archivo,"rb");
    stUsuario aux;
    if(archi){
        while(fread(&aux,sizeof(stUsuario),1,archi)>0 && flag==0){
            if(strcmp(aux.nombreUsuario,usuario)==0){
                flag=1;
            }
        }
    }
    fclose(archi);
    return flag;
}
int tipoDeEmpleado(char perfil[]){
    int tipoUser=0;
    if(strcmpi(perfil,"admin")==0){
                tipoUser=1;
            }else if(strcmpi(perfil,"tecnico")==0 || strcmpi(perfil,"bioquimico")==0){
                tipoUser=2;
            }else{
                tipoUser=3;
            }
    return tipoUser;
}
int validarUsuarioCompleto(char archivo[],char contrasena[], char usuario[]){ //funcion para que a la hora de iniciar sesion verifiquemos si existe, retornaremos el tipo de usuario que es.
    int tipoUser=0;
    FILE*archi=fopen(archivo,"rb");
    stUsuario aux;
    while (fread(&aux,sizeof(stUsuario),1,archi)>0 && tipoUser == 0)
    {
        if(strcmp(usuario,aux.nombreUsuario)==0 && strcmp(contrasena,aux.contrasena)==0){
            tipoUser=tipoDeEmpleado(aux.perfil);
        }
    }
    fclose(archi);
    return tipoUser;
}
int validarDNIUser(char archivo[], int dni){
    int flag=0;
    FILE*archi=fopen(archivo,"rb");
    stUsuario aux;
    if(archi){
        while (fread(&aux,sizeof(stUsuario),1,archi)>0 && flag ==0){
            if(aux.dni==dni){
                flag=1;
            }
        }
    }
    fclose(archi);
    return flag;
}
void cargarUsuarioArchivo(char archivo[],stUsuario aux){
    FILE*archi=fopen(archivo,"ab");
    if(archi){
        fwrite(&aux,sizeof(stUsuario),1,archi);
    }
    fclose(archi);
}
int validarNombreYapellido(char * nombre){///a borrar si funciona
    int cantNum = strlen(nombre);
    int flag = 0;
    if(cantNum < 25 ){
        for ( int i = 0; i<cantNum; i++){
            if(isdigit(nombre[i])){
                flag = 1; ///Si encuentra un digito en el nombre  error 1
            }
        }
    }else{
       flag=1; ///Mas de 25 caracteres el nombre
    }
    return flag;
}
int validarCargoUser(char* cargo){
    int flag=0;
    if(strcmpi(cargo,"administrativo")==0||strcmpi(cargo,"bioquimico")==0||strcmpi(cargo,"tecnico")==0){
        flag=1;
    }
    return flag;
}
int cargarNuevoUsuario(char archivo[]){
    char contra[9];
    unsigned int cantmax=20;
    int valc=0;
    int vald=1;
    stUsuario aux;
    int i=0;
    int j=0;
    int flag=1;
    int tipoUser;
    int nombreApellido=0;
    int cargo=0;
    printf("--------------------------\n");ff
    while (vald==1){///Valida dni
        do{
            printf("Ingrese DNI: ");
            if(scanf("%d",&aux.dni)!=1){///verifica si la entrada es invalida
        // Limpiar el búfer del teclado en caso de una entrada no válida
            ff printf("Ingrese solo numeros.\n");
            continue;
            }else if(aux.dni<1000000 || aux.dni>99999999){
            ff printf("Ingrese un dni valido, maximo 8 numeros.\n");
            }
        }while(aux.dni<1000000 || aux.dni>99999999);
        vald=validarDNIUser(archivo,aux.dni);
        if(vald==1){
            printf("Numero de DNI ya registrado.\n");
        }
    }
    system("cls");
    printf("--------------------------\n");
    printf("DNI: %d\n",aux.dni);
    do{///valida nyApellido
        printf("Nombre y apellido (dejar un espacio entre nombre y apellido): \n");
        fflush(stdin);
        gets(aux.nombreYapellido);
        nombreApellido=validarNombre(aux.nombreYapellido);
        if(nombreApellido==1){
            printf("Error. Nombre invalido. \n");
        }
    }while(nombreApellido!=0);
    system("cls");
    printf("--------------------------\n");
    printf("DNI: %d\n",aux.dni);
    printf("Nombre y Apellido: %s\n",aux.nombreYapellido);
    do{///valida nombre de usuario
        printf("Ingrese Nombre de usuario :\n");ff
        gets(aux.nombreUsuario);
        if(strlen(aux.nombreUsuario)>cantmax){
            printf("\nEl nombre de usuario supera la cantidad de caracteres permitidos. Intentelo de nuevo.\n");
        }else{
            flag=validarNombreUser(archivo,aux.nombreUsuario);
            if(flag==1){
                printf("\nEl nombre de usuario no esta disponible, vuelva a intentarlo.\n");
            }
        }
    }while(cantmax<strlen(aux.nombreUsuario)&&flag==1);
    system("cls");
    printf("--------------------------\n");
    printf("DNI: %d\n",aux.dni);
    printf("Nombre y Apellido: %s\n",aux.nombreYapellido);
    printf("Nombre de usuario: %s\n",aux.nombreUsuario);
    do{///valida cargo correspondiente
        printf("Ingrese cargo correspondiente (administrativo, bioquimico o tecnico).\n");ff
        gets(aux.perfil);
        cargo=validarCargoUser(aux.perfil);
        if(cargo==0){
            printf("\nError. Ingrese un cargo valido.\n");
        }
    }while(cargo!=1);
    system("cls");
    printf("--------------------------\n");
    printf("DNI: %d\n",aux.dni);
    printf("Nombre y Apellido: %s\n",aux.nombreYapellido);
    printf("Nombre de usuario: %s\n",aux.nombreUsuario);
    printf("Cargo: %s\n",aux.perfil);
    printf("\nIngrese contrase%ca:\n",164);ff
    while(1){
        char ch = getch();
        if(ch == '\r'){ // Si se presiona Enter
            break;
        }else if(ch == '\b'){ // Si se presiona Retroceso
            if(i > 0){
                i--;
                printf("\b \b"); // Borrar el último asterisco mostrado
            }
        }else if(i < 8) {
            aux.contrasena[i] = ch;
            printf("*");
            i++;
        }
    }
    aux.contrasena[i] = '\0'; // Agregar el carácter nulo al final de la cadena
    printf("\n");
    while (valc == 0){
        j = 0; // Reiniciar el índice j a 0
        printf("\nIngrese nuevamente la contrase%ca:\n",164);
        fflush(stdout);
        while(1){
            char vp = getch();
            if (vp == '\r') { // Si se presiona Enter
                break;
            } else if (vp == '\b') { // Si se presiona Retroceso
                if (j > 0) {
                    j--;
                    printf("\b \b"); // Borrar el último asterisco mostrado
                }
            } else if (j < 8) {
                contra[j] = vp;
                printf("*");
                j++;
            }
        }
        contra[j] = '\0'; // Agregar el carácter nulo al final de la cadena
        if (strcmp(aux.contrasena, contra) == 0){
            valc = 1;
        }else{
            printf("\nLas contrase%cas no coinciden, intentalo nuevamente.\n",164);
        }
    }
    printf("\n");
    printf("-------------------------\n");
    printf("\nUsuario cargado correctamente.\n");
    cargarUsuarioArchivo(archivo,aux);
    tipoUser=tipoDeEmpleado(aux.perfil);
    return tipoUser;
}
stUserAux cargarUser(){
    stUserAux aux;
    int i = 0;
    printf("-------------------------\n");
    printf("Ingrese nombre de usuario:\n");ff
    gets(aux.nombreUsuario);
    printf("Ingrese contrase%ca:\n",164);ff
    while (1) {
        char ch = getch();
        if (ch == '\r') { // Si se presiona Enter
            break;
        } else if (ch == '\b') { // Si se presiona Retroceso
            if (i > 0) {
                i--;
                printf("\b \b"); // Borrar el último asterisco mostrado
            }
        } else if (i < 8) {
            aux.contrasena[i] = ch;
            printf("*");
            i++;
        }
    }
    aux.contrasena[i] = '\0'; // Agregar el carácter nulo al final de la cadena
    printf("\n");
    printf("-------------------------\n");
    return aux;
}
int inicioSesion(char archivo[]){
    int i=0;
    int tipoUser=0;
    int op=0;
    stUserAux user;
    do{
        user = cargarUser();
        tipoUser = validarUsuarioCompleto(archivo, user.contrasena, user.nombreUsuario);///valida que el usuario exista
        if (tipoUser == 0){///si no existe le pide registrarse o reintentar
            printf("\n----------------\n");
            printf("Los datos que ingreso son incorrectos. Presione cualquier tecla para volver a intentarlo.\n");
            printf("Presione 1 para registrarse.\n");
            printf("\n----------------\n");
            scanf("%d", &op);
            system("cls");
            if(op == 1){
                tipoUser = cargarNuevoUsuario(archivo);///se registra
            }
        }else{
            printf("Usuario encontrado con exito.\n");
            break; // Salir del bucle si se encuentra un usuario válido
        }
        i++;
        if(i == 3){///si alcanzo 3 intentos se le cierra el programa entero
            printf("\nAlcanzo el limite de intentos. Intentelo mas tarde.\n");
            exit(0);
        }
    }while(tipoUser==0);///mientras user sea 0, no existe el usuario
    return tipoUser;
}
char validarOpcionUser(){
    char op[30];
    do{
        fgets(op,30,stdin);
        if (op[strlen(op) - 1] == '\n'){///Eliminar el salto de linea al final de la cadena si esta presente(la tecla enter)
            op[strlen(op) - 1] = '\0';
        }
        if(strlen(op)!= 1){///Verifica que la cadena ingresada tenga como maximo un solo caracter
            printf("Opcion no valida. Ingrese solo un caracter entre 1 y 2: ");
            continue;///Obligo a salir del if y volver a entrar al doWhile
        }
        if(!isdigit(op[0]) || op[0]<'1' || op[0]>'2'){///Verifico si no es un digito o si es menor a 1 o si es mayor a 7 da error
            printf("Opcion no valida. Ingrese solo un caracter entre 1 y 2: ");
        }
    }while(strlen(op)!= 1 || (!isdigit(op[0])||op[0]<'1'||op[0]>'2'));///Verifico todas las condiciones juntas
    return op[0];

}
int login(char archivo[]){
    FILE* archi=fopen(archivo,"rb");
    if(!archi){
        archi=fopen(archivo,"ab");
        crearArchivouser(archi);
    }
    fclose(archi);
    char eleccion;
    int tipoUser;
    printf("INICIO DE SESION:\n");
    printf("1. PARA INICIAR SESION:\n");
    printf("2. PARA REGISTRARSE:\n");ff
    eleccion=validarOpcionUser();
    system("cls");
    if (eleccion == '1') {
        tipoUser = inicioSesion(archivo);
    } else if (eleccion == '2') {
        tipoUser = cargarNuevoUsuario(archivo);
    }
    return tipoUser;
}
/// FUNCIONES PARA EL MANEJO DE NODOS, PARA ASI MOSTRAR EL ARCHIVO DE MANERA ORDENADA.
nodoUser* inicLista(){
    return NULL;
}
nodoUser* crearNodo(stUsuario dato){
    nodoUser* aux=(nodoUser*)malloc(sizeof(nodoUser));
    aux->dato=dato;
    aux->sig=NULL;
    return aux;
}
nodoUser* agregarNodoOrdenado(nodoUser* lista, nodoUser* nuevo){ //Los voy a ordenar por numero de documento
    if(lista==NULL){
        lista=nuevo;
    }else{
        if(strcmpi(lista->dato.nombreYapellido,nuevo->dato.nombreYapellido)>0){
            nuevo->sig=lista;
            lista=nuevo;
        }else{
            lista->sig=agregarNodoOrdenado(lista->sig,nuevo);
        }
    }
    return lista;
}
void mostrarListaUsuarios(nodoUser* lista,int tipoUser){
    if(lista){
        printf("Numero de DNI: %i\n",lista->dato.dni);
        printf("Nombre y apellido: %s\n",lista->dato.nombreYapellido);
        printf("Usuario: %s\n",lista->dato.nombreUsuario);
        if(tipoUser==1){
            printf("Contrase%ca: %s\n",164,lista->dato.contrasena);
        }else{
            printf("Contrase%ca: ", 164);
        for (int i = 0; i < strlen(lista->dato.contrasena); i++) {
            printf("*");
        }
        printf("\n");
        }
        printf("Tipo de perfil: %s\n",lista->dato.perfil);
        printf("----------------------\n");
        mostrarListaUsuarios(lista->sig,tipoUser);
    }
}
void mostrarArchivoOrdenado(char archivo[], int tipoUser){
    nodoUser* aux=inicLista();
    stUsuario a;
    FILE* archi=fopen(archivo,"rb");
    if(archi){
        while (fread(&a,sizeof(stUsuario),1,archi)>0){
            aux=agregarNodoOrdenado(aux,crearNodo(a));
        }
        mostrarListaUsuarios(aux,tipoUser);
    }else{
        printf("No se encontro el archivo.\n\n");
    }
    liberarLista(aux);
    fclose(archi);
}
void liberarLista(nodoUser* lista) {
    while (lista != NULL) {
        nodoUser* nodoAEliminar = lista;
        lista = lista->sig;
        free(nodoAEliminar);  // Libera la memoria del nodo actual
    }
}
void consultaEmpleado(char archivo[], int dni,int tipoUser){///busca el dni y lo muestra
    stUsuario aux;
    FILE*archi=fopen(archivo,"rb");
    if(archi){
        while(fread(&aux,sizeof(stUsuario),1,archi)>0){
            if(aux.dni==dni){
                nodoUser* nuevo=crearNodo(aux);
                mostrarListaUsuarios(nuevo,tipoUser);
                break;
            }
        }
    }
    fclose(archi);
}
