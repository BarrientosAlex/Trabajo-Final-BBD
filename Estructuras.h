#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED
#include <time.h>

typedef struct stPacientes{
    char apelyNom[40];
    int edad;
    int dni;
    char direccion[30];
    char telefono[15];
    int eliminado;
} stPacientes;
typedef struct stIngresos{
    int nroIngreso;
    char fechaIngreso[11];
    char fechaRetiro[10];
    int dni;
    int matricula;
    int eliminado;
}stIngresos;
typedef struct stPracXingreso{
    int nroIngreso;
    int nroPractica;
    char nombrePractica[30];
    char resultado[40];
    int eliminado;
}stPracXingreso;
typedef struct practicas{
    int nroPractica;
    char nombrePractica[30];
    int eliminado;
}practicas;
typedef struct nodoPracticasXingreso{
    stPracXingreso pXi;
    struct nodoPracticasXingreso * sig;
}nodoPracticasXingreso;
typedef struct nodoIngresos{
    stIngresos ingreso;
    struct nodoPracticasXingreso * practicas;
    struct nodoIngresos * sig;
    struct nodoIngresos * ant;
}nodoIngresos;
typedef struct nodoPaciente{
    stPacientes paciente;
    struct nodoIngresos * ingresos;
    struct nodoPaciente * izq;
    struct nodoPaciente * der;
}nodoPaciente;

practicas cargarPracticas();
///FUNCIONES PACIENTES
nodoPaciente* inicArbol();
nodoPaciente * crearNodoPaciente(stPacientes pac);
stPacientes cargarPaciente();
//funciones validar
int validarNombre(char * nombre);
int validarEdad (char * edad);
int validarDNI(char * dni);
int validarTelefono(char * telefono);
int validarDireccion(char * direccion);
int validarPractica(char * nombrePractica);
//funciones insertar y agregar
nodoPaciente * insertarPaciente(nodoPaciente * a, stPacientes pac);
nodoPaciente * buscarPacienteDNI (nodoPaciente * a,int dni);
nodoPaciente * alta_de_paciente(nodoPaciente * arbolPaciente);
nodoPaciente * modificacion_de_paciente(nodoPaciente * arbolPaciente);
nodoPaciente * baja_de_paciente(nodoPaciente * arbolPaciente);
//funciones archivo
void arbolPacienteToArchivo(char archivo[],stPacientes dato);
void modificarArchivoPaciente(char archivo[],stPacientes datonuevo);
nodoPaciente* cargarArbolDesdeArchivo(char archivo[],nodoPaciente* arbol);
//funcion mostrar
void inOrder(nodoPaciente *arbolPaciente);
void inOrderADMIN(nodoPaciente *arbolPaciente);
void mostrarPaciente(stPacientes dato);
int calcularCantidadNodos(nodoPaciente * arbolPaciente);
void recorrerEnOrden(nodoPaciente * arbolPaciente, stPacientes * array, int * validos );
stPacientes * PacientesOrdenados(nodoPaciente * arbolPaciente, int * validos);
void mostrarPacientesOrdenados(stPacientes * array, int validos);
///FUNCIOES INGRESOS
//funciones crear y agregar
nodoIngresos * crearNodoIng (stIngresos a);
nodoIngresos * agregarPpioIngresos(nodoIngresos * lista, nodoIngresos * nuevo);
nodoIngresos * agregarOrdenFecha(nodoIngresos * lista, nodoIngresos * nuevo);
//funciones mostrar
void mostrarAux(stIngresos dato);
void mostrarIngreso(nodoIngresos* lista);
void mostrarIngresoADMIN(nodoIngresos* lista);
void recorrerArbol(nodoPaciente* arbol,char fechaDesde[],char fechaHasta[]);
//funciones para seleccionar por el usuario
nodoIngresos* buscarPorNroIngreso(nodoPaciente* arbol, int nroIngreso); /// busca nro de ingreso de determinado paciente No filtrado
nodoIngresos* buscarListaPractica(nodoPaciente * arbol,int nroIngreso);
nodoIngresos * filtrarPorNroIngreso(nodoPaciente* arbol);
nodoIngresos* filtrarPorFechaIngreso(nodoPaciente* arbol);
void filtrarPorDNI(nodoPaciente * arbol);
nodoIngresos * filtrarIngreso(nodoPaciente* arbol);
void filtrarIngresoParaMostrar(nodoPaciente* arbol,int nroIngreso);
stIngresos cargarIngresos();
nodoPaciente * alta_de_ingreso(nodoPaciente * arbolPaciente);
//funciones validar
int validarFecha(char *fechaRetiro);
int validarFechaIngreso(char* fechaIngreso);
int validarMatricula(char * matricula);
int validarDNIyEncontrar(nodoPaciente* arbol,nodoPaciente** encontrado);
//funciones archivos
void agregarNuevoIngresoArchivo(char archivo[],stIngresos nuevo);
int contarIngresosenArchivo( char archivo[]);
void modificarArchivoIngresos(char archivo[],stIngresos datonuevo); ///por parametro ya debemos pasar el ingreso modificado
nodoPaciente* cargarIngresosDesdeArchivo(char archivo[],nodoPaciente* arbol);
///FUNCIONES PARA PRACTICASXINGRESO
//funciones crear y agregar
nodoPracticasXingreso * crearNodoPxI(stPracXingreso pxi);
nodoPracticasXingreso * agregarPpioPXI(nodoPracticasXingreso * lista, nodoPracticasXingreso * nuevoNodo);
stPracXingreso cargarPXI(int numIngreso);
//funciones alta,baja,mod
nodoPracticasXingreso * Alta_de_pxi(nodoPracticasXingreso * lista,int num);
nodoPracticasXingreso * Baja_de_pxi(nodoPracticasXingreso * lista);
nodoPracticasXingreso * modificacion_de_pxi(nodoPracticasXingreso * lista);
int validarNumero(char * nroPractica);
//funciones buscar prefijo
int validarPrefijo(char * prefijo);
void buscarPrefijoPaciente(nodoPaciente* arbol,char prefijo[]);
void buscarPrefijoIngreso(nodoIngresos* lista,char prefijo[]);
void buscarPrefijoPractica(nodoPracticasXingreso* lista,char prefijo[]);
//funciones buscar y contar
nodoPracticasXingreso* buscarPractica(nodoPracticasXingreso* lista,int numPractica);
nodoPracticasXingreso * buscarNroPractica(nodoPracticasXingreso * lista, int nroPractica);
//funciones archivo
nodoPaciente* pasarPracticasAlArbolArchivo(char archivo[],nodoPaciente* arbol);
int contarPxienArchivo(char archivo[]);
int buscarPxiArchivo(char archivo[],int nrPractica);
void modificarArchivoPXI(char archivo[], stPracXingreso dato);
void agregarPxialArchivo(char archivo[], stPracXingreso dato);
//funciones mostrar
void mostrarPxiAUX(stPracXingreso dato);
void mostrarPxi(nodoPracticasXingreso* lista);
void mostrarPxiADMIN(nodoPracticasXingreso* lista);
void recorrerIngresosParamostrarPracticas(nodoIngresos* lista);
void recorrerArbolParaMostrarPracticas(nodoPaciente* arbol);
#endif // ARBOLPACIENTE_H_INCLUDED
