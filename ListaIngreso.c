#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "Estructuras.h"

///Funciones crear y agregar
nodoIngresos * crearNodoIng (stIngresos a){
    nodoIngresos * aux =(nodoIngresos*)malloc(sizeof(nodoIngresos));
    aux->ingreso = a;
    aux->practicas = NULL;
    aux->sig = NULL;
    aux->ant = NULL;
    return aux;
}
nodoIngresos * agregarPpioIngresos(nodoIngresos * lista, nodoIngresos * nuevo){ ///funcion auxiliar para agregar en orden la fecha
    if(lista == NULL){
        lista = nuevo;
    }else{
        lista->ant = nuevo;
        nuevo->sig = lista;
        lista = nuevo;
    }
    return lista;
}
nodoIngresos * agregarOrdenFecha(nodoIngresos * lista, nodoIngresos * nuevo){ ///Se agrega en orden las fechas de manera descendente
    if(lista == NULL){
        lista = nuevo;
    }else{
        // Comparar las fechas
        int comparacionFecha=strcmpi(nuevo->ingreso.fechaIngreso, lista->ingreso.fechaIngreso);
        if(comparacionFecha>0||(comparacionFecha==0&&nuevo->ingreso.nroIngreso>lista->ingreso.nroIngreso)){
            lista=agregarPpioIngresos(lista,nuevo);
        }else{
            nodoIngresos * ante = lista;
            nodoIngresos * seg = lista->sig;
            while(seg != NULL &&(comparacionFecha<0||(comparacionFecha==0&&nuevo->ingreso.nroIngreso>lista->ingreso.nroIngreso))){
                ante = seg;
                seg = seg->sig;
            }
            ante->sig = nuevo;
            nuevo->ant = ante;
            nuevo->sig =seg;
            if(seg != NULL){
                seg->ant = nuevo;
            }
        }
    }
    return lista;
}
///Funciones mostrar
void mostrarAux(stIngresos dato){
    ///if(dato.eliminado==0){
        printf("\n*********************\n");
        printf("Numero de ingreso :%i\n",dato.nroIngreso);
        printf("Fecha de ingreso :%s\n",dato.fechaIngreso);
        printf("Fecha de retiro:%s\n",dato.fechaRetiro);
        //Dni lo muestro una sola vez antes
        printf("Matricula : %i",dato.matricula);
    ///}
}
void mostrarIngreso(nodoIngresos* lista){///Muestra los no eliminados
    if(lista){
        if(lista->ingreso.eliminado==0){
            mostrarAux(lista->ingreso);
            printf("\n\tPRACTICAS \n");
            fflush(stdout);
            mostrarPxi(lista->practicas);
        }
        mostrarIngreso(lista->sig);
    }
}
void recorrerArbol(nodoPaciente* arbolPaciente,char fechaDesde[],char fechaHasta[]){///recorro y muestro por fechas
    if(arbolPaciente){
        recorrerArbol(arbolPaciente->izq,fechaDesde,fechaHasta);
        printf("\n------- %s --------\n", arbolPaciente->paciente.apelyNom);
        printf("DNI:%d \n", arbolPaciente->paciente.dni);
        printf("Direccion: %s \n", arbolPaciente->paciente.direccion);
        printf("Edad: %d \n", arbolPaciente->paciente.edad);
        printf("Telefono: %s\n", arbolPaciente->paciente.telefono);
        printf("Eliminado: %d\n", arbolPaciente->paciente.eliminado);
        printf("---------------------------\n");
        mostrarIngreso(arbolPaciente->ingresos);
        printf("\n********************\n");
        nodoIngresos * seg=arbolPaciente->ingresos;
        while(seg){
            if(strcmp(seg->ingreso.fechaIngreso,fechaDesde)>=0 && strcmp(seg->ingreso.fechaRetiro,fechaHasta)<=0){
                mostrarAux(seg->ingreso);
            }
            seg=seg->sig;
        }
        recorrerArbol(arbolPaciente->der,fechaDesde,fechaHasta);
    }
}
///Funcion para para que el usuario pueda seleccionar por que forma filtrar la busqueda y si se encuentra lo que busco dentro de la lista, que retorne ese nodo.
nodoIngresos* buscarPorNroIngreso(nodoPaciente* arbol, int nroIngreso){
    nodoIngresos* aux=NULL;
    if(arbol){
        aux=buscarPorNroIngreso(arbol->der,nroIngreso);
        if(aux==NULL){
            if(arbol->ingresos){
                nodoIngresos* seg=arbol->ingresos;
                while(seg!=NULL && aux==NULL){
                    if(seg->ingreso.nroIngreso==nroIngreso){
                        aux=seg;
                    }
                    seg=seg->sig;
                }
            }
            if(aux==NULL){
                aux=buscarPorNroIngreso(arbol->izq,nroIngreso);
            }
        }
    }
    return aux;
}
nodoIngresos* buscarListaPractica(nodoPaciente * arbol,int nroIngreso){
    nodoIngresos* aux=NULL;
    if(arbol==NULL){
        return aux;
    }else{
        nodoIngresos* aux = buscarPorNroIngreso(arbol,nroIngreso);
        if(aux==NULL){
            aux=buscarListaPractica(arbol->der,nroIngreso);
            aux=buscarListaPractica(arbol->izq,nroIngreso);
        }
    }
    return aux;
}
nodoIngresos * filtrarPorNroIngreso(nodoPaciente* arbol){ ///anteriormente pedir el paciente por el cual queremos buscar el ingreso
    nodoIngresos* aux=NULL;
    if(arbol){
        int nroIngreso;                                       /// por parametro hacer un a busqueda por dni y lo que retorne utilizarlo
        printf("Ingrese el nro de Ingreso a buscar: \n");
        fflush(stdin);
        scanf("%d", &nroIngreso);
        nodoIngresos* seg=arbol->ingresos;
        while(seg!=NULL && aux==NULL){
            if(seg->ingreso.nroIngreso==nroIngreso){
                aux=seg;
            }
            seg=seg->sig;
        }
        if(!aux){
            printf("\nError. No se encontro el numero de ingreso.\n");
        }
    }
    return aux;  ///retorna NULL si no lo encontro, o el puntero a todos los datos del ingreso
}
nodoIngresos* filtrarPorFechaIngreso(nodoPaciente* arbol){ ///anteriormente tenemos que haber buscado el paciente del que quermos el ingreso
    nodoIngresos* aux=NULL;
    int fechaValida=0;
    if(arbol){
        char fechaIngreso[10];
        do{
            printf("Ingrese la fecha de ingreso a buscar(formato dd/mm/yyyy): \n");
            fflush(stdin);
            gets(fechaIngreso);
            fechaValida=validarFechaIngreso(fechaIngreso);
            if(fechaValida==0){
                printf("\nError. Ingrese una fecha valida.\n");
            }
        }while(fechaValida!=1);
        nodoIngresos* seg= arbol->ingresos;
        while(seg!=NULL && aux==NULL){
            if(strcmpi(seg->ingreso.fechaIngreso, fechaIngreso) == 0){
                aux=seg;
            }
            seg=seg->sig;
        }
        if(!aux){
            printf("\nError. Fecha de ingreso inexistente.\n");
        }
    }
    return aux;
}
void filtrarPorDNI(nodoPaciente * arbol) {///Mostrara todos los ingresos de la persona que desee la cual anteriormente debemos corroborar que exista o no
   if(arbol){
        printf("\n---------------\n");
        printf("DNI: %i",arbol->paciente.dni);
        if(arbol->ingresos==NULL){
            printf("\nError: no hay ingresos cargados.\n");
        }else{
            mostrarIngreso(arbol->ingresos);
        }
   }
}
nodoIngresos * filtrarIngreso(nodoPaciente* arbol){ /// anteriormente tenemos que llamar a buscar por dni para saber si existe o no
    nodoIngresos* aux=NULL;
    if(arbol){
        aux = filtrarPorNroIngreso(arbol);
    }else{
        printf("Paciente no existente.\n");
    }
    return aux;
}
nodoIngresos* filtrarIngresoParaMostrar(nodoPaciente* arbol){
    nodoIngresos *aux=NULL;
    char eleccion;
    int flag=1;
    if(arbol){
        do{
            printf("Ingrese: \n.1-Filtrar nro.Ingreso.\n.2-Filtrar por fecha ingreso.\n");
            fflush(stdin);
            scanf("%c",&eleccion);
            switch(eleccion){
                case '1':{
                    aux=filtrarPorNroIngreso(arbol);
                    break;
                }
                case '2':{
                    aux=filtrarPorFechaIngreso(arbol);
                    break;
                }
                default:{
                    flag=0;
                    break;
                }
            }
        }while(flag!=1);
    }
    return aux;
}
stIngresos cargarIngresos(){
    stIngresos aux;
    char matriString[10];
    int fechaValida = 0;
    int matriculaValida = 0;
    time_t t;
    struct tm * tm_info;
    time(&t);
    tm_info = localtime(&t);
    aux.nroIngreso = contarIngresosenArchivo("ingresos.bin")+1;
    sprintf(aux.fechaIngreso, "%02d/%02d/%04d", tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900);
    char fechaRetiroBuffer[10];
    system("cls");
    printf("---------------------\n");
    printf("Ingreso numero: %i\n",aux.nroIngreso);
    printf("Fecha ingreso: %s\n",aux.fechaIngreso);
    do{
        printf("Ingrese la fecha del retiro(formato dd/mm/yyyy): \n");
        fflush(stdin);
        gets(fechaRetiroBuffer);
        fechaValida=validarFecha(fechaRetiroBuffer);
        if(fechaValida==1){
            printf("Error.Ingrese una fecha de retiro valido. \n");
        }
    }while(fechaValida!=0);
    system("cls");
    printf("---------------------\n");
    printf("Ingreso numero: %i\n",aux.nroIngreso);
    printf("Fecha de ingreso: %s\n",aux.fechaIngreso);
    strcpy(aux.fechaRetiro, fechaRetiroBuffer);
    printf("Fecha de retiro: %s\n",aux.fechaRetiro);
    //Copiar la fecha de retiro al buffer de la estructura
    do{
        printf("Ingrese los 6 numeros de la matricula del Profesional: \n");
        fflush(stdin);
        scanf("%d", &aux.matricula);
        sprintf(matriString,"%d", aux.matricula);
        matriculaValida = validarMatricula(matriString);
        if(matriculaValida == 1){
            printf("Error.Ingrese una matricula valida.\n");
        }
    }while(matriculaValida != 0);
    system("cls");
    printf("---------------------\n");
    printf("Ingreso numero: %i\n",aux.nroIngreso);
    printf("Fecha de ingreso: %s\n",aux.fechaIngreso);
    printf("Fecha de retiro: %s\n",aux.fechaRetiro);
    printf("Matricula: %d\n",aux.matricula);
    aux.eliminado = 0;
    return aux;
}
int validarFechaIngreso(char* fechaIngreso){
    int cantNum=strlen(fechaIngreso);
    int flag=1;
    int dia=(fechaIngreso[0]-'0')*10+fechaIngreso[1]-'0';
    int mes=(fechaIngreso[3]-'0')*10+fechaIngreso[4]-'0';
    int anio=(fechaIngreso[6]-'0')*1000+(fechaIngreso[7]-'0')*100+(fechaIngreso[8]-'0')*10+(fechaIngreso[9]-'0');
    if(cantNum==10){
        for(int i=0;i<cantNum;i++){
            if(!isdigit((unsigned char)fechaIngreso[i])&&fechaIngreso[i]!='/'){
                flag=0;
                break;
            }
        }
    }else{
        flag=0;
    }
    return flag;
}
int validarFecha(char *fechaRetiro){
    int cantNum =strlen(fechaRetiro);
    int flag = 0;
    int dia = (fechaRetiro[0]-'0')* 10 + fechaRetiro[1]-'0'; /// Paso el los dos primeras posiciones del string a un tipo int (Le resto el caracter - '0' que en la tabla ascii en el numero a 48 para convertirlo en tipo int
    int mes = (fechaRetiro[3]-'0') *10 +fechaRetiro[4]- '0'; /// Por lo tanto si en la posicion del string seleccionado es '1' le restas '0' y se busca su numero en la tabla ascii (49) - (48) y da 1 y se convierte en tipo int
    int anio = (fechaRetiro[6]-'0') * 1000 + (fechaRetiro[7]-'0')*100 + (fechaRetiro[8]-'0')*10+ (fechaRetiro[9]-'0');
    if(cantNum ==10){
        for(int i = 0;i<cantNum;i++){
            if(!isdigit((unsigned char)fechaRetiro[i])&& fechaRetiro[i] != '/'){   /// Para que se permita el uso de la barra entre el medio de dia, mes y año
                flag =1;
            }
        }
        if(flag == 0){
            if(dia < 1 || dia>31 || mes<01 || mes>12 || anio<2023 ||anio>2033){
                flag = 1;
            }
        }
        if(anio == 2023){
            if(mes<11 || mes >12){
                flag = 1;
            }
            else if(mes == 11){
                if(dia<22 || dia> 30){
                    flag = 1;
                }
            }
        }
    }else{
        flag = 1;
    }
    return flag;
}
int validarMatricula(char * matricula){
    int cantNum = strlen(matricula);
    int flag = 0;
    if(cantNum == 6){
        for(int i = 0; i<cantNum;i++){
            if(!isdigit(matricula[i])){
                flag = 1;
            }
        }
    }else{
        flag = 1;
    }
    return flag;
}
nodoPaciente * alta_de_ingreso(nodoPaciente * arbolPaciente){
    int dni;
    char dniString[10];
    int dniValido = 0;
    do{
        printf("Ingrese DNI del paciente para dar de alta el ingreso: \n");
        fflush(stdin);
        scanf("%d",&dni);
        sprintf(dniString,"%d",dni);
        dniValido = validarDNI(dniString);
        if(dniValido == 1){
            printf("Error.Ingrese DNI valido. \n");
        }
    }while(dniValido != 0);
    nodoPaciente * paciente = buscarPacienteDNI(arbolPaciente,dni);
    if(paciente != NULL){
        if(paciente->paciente.eliminado == 0){
            stIngresos nuevoIng = cargarIngresos();
            ///Hasta aca cargamos un ingreso con sus datos correspondientes
            nuevoIng.dni=dni; ///le ponemos el mismo dni que la persona para poder enlazarlo despues
            nodoIngresos * nuevoNodo = crearNodoIng(nuevoIng); ///Creamos el nodo de tipo ingreso
            paciente->ingresos=agregarOrdenFecha(paciente->ingresos,nuevoNodo); ///lo agregamos en orden en la lista de ingresos
            ///entramos a la lista de practicas
            paciente->ingresos->practicas= Alta_de_pxi(paciente->ingresos->practicas,paciente->ingresos->ingreso.nroIngreso);
            agregarNuevoIngresoArchivo("ingresos.bin",nuevoIng);
            printf("Ingreso dado de alta correctamente.\n");
        }
    }else{
        printf("\nError el paciente no fue encontrado, cargue un paciente.\n");
        arbolPaciente=alta_de_paciente(arbolPaciente);
    }
    return arbolPaciente;
}
int validarDNIyEncontrar(nodoPaciente* arbol,nodoPaciente** encontrado){
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
    *encontrado=buscarPacienteDNI(arbol,dni);
    return dni;
}
///Funciones arhivo
void agregarNuevoIngresoArchivo(char archivo[],stIngresos nuevo){
    FILE* archi=fopen(archivo,"ab");
    if(archi){
        ///fseek(archi,0,SEEK_END); no hace falta, el ab lo pone al final
        fwrite(&nuevo,sizeof(stIngresos),1,archi);
    }else{
        printf("\nSe produjo un error al abrir el archivo de Ingresos.\n");
    }
    fclose(archi);
}
void modificarArchivoIngresos(char archivo[],stIngresos datonuevo){ ///por parametro ya debemos pasar el ingreso modificado
    FILE*archi=fopen(archivo,"r+b");
    int enc=0;
    stIngresos aux;
    if(archi){
        while((fread(&aux,sizeof(stIngresos),1,archi)>0 && enc ==0)){
                if(datonuevo.nroIngreso==aux.nroIngreso){
                fseek(archi,(-1)*sizeof(stIngresos),SEEK_CUR);
                aux=datonuevo;
                fwrite(&aux,sizeof(stIngresos),1,archi);
              }
        }
    }else{
        printf("Se produjo un error con el arrchivo modificar ingresos.\n");
    }
    fclose(archi);
}
int contarIngresosenArchivo( char archivo[]){
    FILE * archi = fopen(archivo,"rb");
    int cant = 0;
    if(archi){
        fseek(archi,0,SEEK_END);
        int tam=ftell(archi);
        cant=tam/sizeof(stIngresos);
    }
    fclose(archi);
    return cant;
}
nodoPaciente* cargarIngresosDesdeArchivo(char archivo[],nodoPaciente* arbol){
    stIngresos aux;
    nodoPaciente* rama=inicArbol();
    FILE*archi=fopen(archivo,"rb");
    if(archi==NULL){
        archi=fopen(archivo,"ab");
    }else{
        if(fread(&aux,sizeof(stIngresos),1,archi)>0){
            fseek(archi, 0, SEEK_SET);
            while(fread(&aux, sizeof(stIngresos), 1, archi) > 0){
                rama=buscarPacienteDNI(arbol,aux.dni);
                if(rama!=NULL){
                    rama->ingresos=agregarOrdenFecha(rama->ingresos,crearNodoIng(aux));
                }
            }
        }
    }
    fclose(archi);
    return arbol;
}



