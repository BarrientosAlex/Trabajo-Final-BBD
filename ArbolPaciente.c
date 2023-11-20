#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "Estructuras.h"



// Funciones nodoPracticas


practicas cargarPracticas(){
    practicas aux;
    printf("Ingrese el Nro de practicas: \n");
    fflush(stdin);
    scanf("%d", &aux.nroPractica);
    printf("Ingrese el nombre de la Practica: \n");
    fflush(stdin);
    gets(aux.nombrePractica);
   aux.eliminado = 0;
    return aux;
}










///Funciones Paciente

nodoPaciente * crearNodoPaciente(stPacientes pac){
    nodoPaciente * aux = (nodoPaciente*)malloc(sizeof(nodoPaciente));
    aux->paciente= pac;
    aux->der= NULL;
    aux->izq = NULL;
    aux->ingresos = NULL;
    return aux;
}

stPacientes cargarPaciente(){
    stPacientes aux;
    int nombreValido = 0;
    int edadValido = 0;
    int telefonoValido = 0;
    int dniValido = 0;
    int direccionValida = 0;

    char edadString[10];
    char dniString[10];
 ///convierte un tipo de dato int a una cadena de caracteres


    do{
        printf("Ingrese nombre y apellido del paciente(poner un espacio para separarlos): \n");
        fflush(stdin);
        gets(aux.apelyNom);
        nombreValido = validarNombre(aux.apelyNom);
        if(nombreValido ==1){
            printf("Error.Nombre invalido. \n");
        }
    }while(nombreValido != 0);
    do{
        printf("Ingrese la edad del paciente: \n");
        fflush(stdin);
        scanf("%d", &aux.edad);
        sprintf(edadString,"%d",aux.edad);///convierte un tipo de dato int a una cadena de caracteres
        edadValido = validarEdad(edadString);
        if(edadValido == 1){
            printf("Error. Ingrese una edad valida.\n");
        }
    }while(edadValido != 0);

    do{
        printf("Ingrese el dni del paciente: \n");
        fflush(stdin);
        scanf("%d", &aux.dni);
        sprintf(dniString,"%d",aux.dni);
        dniValido = validarDNI(dniString);
        if(dniValido == 1){
            printf("Error.Ingrese DNI valido. \n");
        }
    }while(dniValido !=0);
    do{
        printf("Ingrese la direccion del paciente(calle y altura): \n");
        fflush(stdin);
        gets(aux.direccion);
        direccionValida = validarDireccion(aux.direccion);
        if(direccionValida == 1){
            printf("Error.Ingrese direccion valida.\n");
        }
    }while(direccionValida != 0);
    do{
    printf("Ingrese el telefono del paciente(sin prefijo):\n");
    fflush(stdin);
    gets(aux.telefono);
    telefonoValido = validarTelefono(aux.telefono);
    if(telefonoValido == 1 ){
        printf("Error.Telefono invalido");
    }
    }while(telefonoValido != 0);
    aux.eliminado = 0;
    return aux;
}


int validarNombre(char * nombre){
    int cantNum = strlen(nombre);
    int flag = 0;
     int espacioEncontrado;
    if(cantNum>8 &&cantNum<40){
        for(int i = 0; i<cantNum;i++){
            if(isdigit(nombre[i])){ ///No funciona el isspace
                flag = 1;
                ///Si encuentra un  digito en el nombre flag es igual 1 es decir va a dar error y tambien en caso de que no encuentre un espacio
            }
        }
    }else{
        flag = 1;
    }

    espacioEncontrado = strchr(nombre,' '); ///esta funcion busca el primer caracter de la cadena que coincide con el caracter especificado, es decir, con el espacio.

    if(espacioEncontrado == NULL){  ///Si es igual a NULL eso significa que no hay un espacio entre el nombre y el apellido, por tanto va a dar error
        flag = 1;
    }

    return flag;
}


int validarEdad (char * edad){
    int cantNum = strlen(edad);
    int flag = 0;

    if(cantNum <= 3){
        for(int i = 0; i<cantNum; i++){
            if(!isdigit(edad[i])){ ///Si encuentra un caracter distinto a un digito en la cadena de caracteres edad, la flag es igual a 1
                flag =1;
            }
        }
    }else{
         flag = 1;
    }


    if(flag == 0){  ///Si la flag sigue siendo 0
        int edadNum = atoi(edad); /// convierto el string edad en un tipo int con la funcion atoi

        if(edadNum< 0 || edadNum >100){
            flag = 1;
        }else{
            flag = 0;
        }
    }

    return flag;
}

int validarDNI(char * dni){
    int cantNum = strlen(dni);
    int flag = 0;
    if(cantNum == 8){
         for(int i = 0; i<cantNum; i++){
            if(!isdigit(dni[i])){ ///Si encuentra un caracter distinto a un digito en la cadena de caracteres edad, la flag es igual a 1
            flag =1;
            return flag;
            }
         }
    }else{
        flag = 1;
        return flag;
    }

    return flag;

}
int validarTelefono(char * telefono){
    int cantNum = strlen(telefono);
    int flag = 0;
    if(cantNum == 10){
        for(int i = 0; i<cantNum; i++){
            if(!isdigit(telefono[i])){
                flag = 1;
            }
        }
    }else{
        int flag = 1;
    }
    return flag;
}
int validarDireccion(char * direccion){
    int cantNum = strlen(direccion);
    int flag = 0;
    int contador = 0;
    if(cantNum < 5 || cantNum >30){  ///Si el usuario ingresa menos de 5 caracteres o mas de 30 la flag va a ser igual 1 por ende va a tirar error
        flag = 1;
        return flag;
    }

    for(int i= 0; i<cantNum;i++){
        if(!isalnum(direccion[i] && !isspace(direccion[i])&& !ispunct(direccion[i]))) { ///isalnum va a retornar un valor distinto de 0 si no se ingresa un caracter alfanumerico y isspace va a retornar un valor distinto de 0 si hay un espacio( lo vamos a usar para que el usuario distinga domicilio y calle)
        int flag = 1;                                           ///Con el ispunct no le permito al usuario ingresar caracteres especiales
        }
    }

    for(int j = 0; j<cantNum; j++){
        if(isdigit(direccion[j])){
            contador++;  ///Cada vez que en el string encuentre un digito que lo cuente en la variable contador.
        }
    }
    if(contador < 2 || contador > 5){ /// Si el contador es menor a 2 o mayor a 5 el numero de la calle seria falso
        flag = 1;
    }

    return flag;
}


nodoPaciente * insertarPaciente(nodoPaciente * a, stPacientes pac){
    if(a == NULL){
        a = crearNodoPaciente(pac);
    }

    if(a){
        if(pac.dni < a->paciente.dni ){
            a->izq = insertarPaciente(a->izq,pac);
        }else{
            a->der = insertarPaciente(a->der,pac);
        }
    }  //Si la comparacio nes igual a 0 significa que los nombres son iguales por lo tanto no hacemos nada para evitar duplicados.
    return a;
}

nodoPaciente * buscarPacienteDNI (nodoPaciente * a,int dni){  ///busca DNI en el arbol
   if(a == NULL){
    return NULL;
   }

   if(a->paciente.dni == dni){
    return a;
   }

  if(dni < a->paciente.dni){
    return buscarPacienteDNI(a->izq,dni);
  }else{
    return buscarPacienteDNI(a->der,dni);
  }
}


nodoPaciente * alta_de_paciente(nodoPaciente * arbolPaciente){
    stPacientes nuevoPaciente = cargarPaciente();
    nodoPaciente * buscar = buscarPacienteDNI(arbolPaciente,nuevoPaciente.dni);

    if(buscar == NULL){
        arbolPaciente = insertarPaciente(arbolPaciente, nuevoPaciente);
        printf("Paciente dado de alta correctamente.\n");
    } else {
        printf("Error. El paciente con DNI %d ya existe.\n", nuevoPaciente.dni);
    }

    return arbolPaciente;
}


nodoPaciente * modificacion_de_paciente(nodoPaciente * arbolPaciente){
    int dni;
    int nombreValido = 0;
    char edadString[10];
    int edadValido = 0;
    int telefonoValido = 0;
    int dniValido = 0;
    int direccionValida = 0;

    printf("Ingrese el DNI del paciente a modificar: \n");
    fflush(stdin);
    scanf("%d", &dni);

    nodoPaciente * paciente = buscarPacienteDNI(arbolPaciente,dni);
    if(paciente != NULL){   //Si el nodo es != NULL eso significa que encontro el dni del paciente dentro del arbol
         do{
            printf("Ingrese el nuevo nombre y apellido del paciente: ");
            fflush(stdin);
            gets(paciente->paciente.apelyNom);
            nombreValido = validarNombre(paciente->paciente.apelyNom);
            if(nombreValido ==1){
            printf("Error.Nombre invalido. \n");
        }
        }while(nombreValido != 0);
        do{
            printf("Ingrese la nueva edad del paciente: ");
            fflush(stdin);
            scanf("%d", &paciente->paciente.edad);
            sprintf(edadString,"%d",paciente->paciente.edad); ///convierte un tipo de dato int a una cadena de caracteres
        edadValido = validarEdad(edadString);
        if(edadValido == 1){
            printf("Error. Ingrese una edad valida.\n");
        }
        }while(edadValido != 0);
        do{
            printf("Ingrese la nueva dirección del paciente: ");
            fflush(stdin);
            gets(paciente->paciente.direccion);
            direccionValida = validarDireccion(paciente->paciente.direccion);
        if(direccionValida == 1){
            printf("Error.Ingrese direccion valida.\n");
            }
        }while(direccionValida != 0);
        do{
        printf("Ingrese el nuevo teléfono del paciente: ");
        fflush(stdin);
        gets(paciente->paciente.telefono);
        telefonoValido = validarTelefono(paciente->paciente.telefono);
        if(telefonoValido == 1 ){
            printf("Error.Telefono invalido");
            }
        }while(telefonoValido != 0);

        printf("Modificación del paciente con DNI %d realizada correctamente.\n", dni);
    }else{
        printf("Error.No se encontreo el paciente con DNI %d. \n", dni);
    }
    return arbolPaciente;
}

nodoPaciente * baja_de_paciente(nodoPaciente * arbolPaciente){
    int dni;
    printf("Ingrese el DNI del paciente a dar de baja: \n");
    fflush(stdin);
    scanf("%d",&dni);
    nodoPaciente * paciente = buscarPacienteDNI(arbolPaciente, dni);
    if(paciente != NULL){
        if(paciente->ingresos == NULL){  //Si el paciente no tiene asociado ningun ingreso, marcarlo como eliminado
            paciente->paciente.eliminado = 1;
            printf("Paciente eliminado correctamente.");
        }else{
            printf("Error. El paciente tiene ingresos asociados y no se pudo eliminar correctamente.");
        }
    }else{
        printf("Error. No se encontro el paciente con DNI %d\n", dni);
    }
    return arbolPaciente;
}


///Funciones copiar al archivo
void arbolPacienteToArchivo(char archivo[],stPacientes dato){
    FILE* archi=fopen(archivo,"ab");
    stPacientes aux;
    if(archi){
        aux=dato;
        fwrite(&aux,sizeof(stPacientes),1,archi);
    }else{
        printf("\nError al abrir el archivo de pacientes\n");
    }
}


void inOrder(nodoPaciente *arbolPaciente){
    if(arbolPaciente){
        inOrder(arbolPaciente->izq);
        printf("------- %s --------", arbolPaciente->paciente.apelyNom);
        printf("DNI:%d \n", arbolPaciente->paciente.dni);
        printf("Direccion: %s \n", arbolPaciente->paciente.direccion);
        printf("Edad: %d \n", arbolPaciente->paciente.edad);
        printf("Telefono: %d", arbolPaciente->paciente.telefono);
        printf("Eliminado: %d", arbolPaciente->paciente.eliminado);
        inOrder(arbolPaciente->der);
    }
}
nodoPaciente* cargarIngresosDesdeArchivo(char archivo[],nodoPaciente* arbol){
    stIngresos aux;
    nodoPaciente* rama=NULL;
    FILE*archi=fopen(archivo,"rb");
    if(archi){
        if(fread(&aux,sizeof(stIngresos),1,archi)>0){
            fseek(archi, 0, SEEK_SET);
            while (fread(&aux, sizeof(stIngresos), 1, archi) > 0) {
                rama=buscarPacienteDNI(arbol,aux.dni);
                if(rama){
                   rama->ingresos=agregarOrdenFecha(rama,crearNodoIng(aux));
                }
            }
        }
    }
    fclose(archi);
    return arbol;
}
void modificarArchivoPaciente(char archivo[],stPacientes datonuevo){
    FILE*archi=fopen(archivo,"r+b");
    int enc=0;
    stPacientes aux;
    if(archi){
        while(fread(&aux,sizeof(stPacientes),1,archi)>0 && enc ==0){
                if(datonuevo.dni==aux.dni){
                fseek(archi,(-1)*sizeof(stPacientes),SEEK_CUR);
                aux=datonuevo;
                fwrite(&aux,sizeof(stPacientes),1,archi);
              }
        }
    }else{
        printf("Se produjo un error con el arrchivo modificar ingresos.\n");
    }
    fclose(archi);

}

