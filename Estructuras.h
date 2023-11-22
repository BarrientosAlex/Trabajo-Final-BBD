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
    struct nodoA * izq;
    struct nodoA * der;
}nodoPaciente;



practicas cargarPracticas();
//void  filtrarPorPrefijo (nodoPracticas * lista);
///FUNCIONES PACIENTES
void modificarArchivoPaciente(char archivo[],stPacientes datonuevo);
void arbolPacienteToArchivo(char archivo[],stPacientes dato);
nodoPaciente * crearNodoPaciente(stPacientes pac);
stPacientes cargarPaciente();
nodoPaciente * insertarPaciente(nodoPaciente * a, stPacientes pac);
nodoPaciente * buscarPacienteDNI (nodoPaciente * a,int dni);
nodoPaciente * alta_de_paciente(nodoPaciente * arbolPaciente);
nodoPaciente * modificacion_de_paciente(nodoPaciente * arbolPaciente);
nodoPaciente * baja_de_paciente(nodoPaciente * arbolPaciente);
void inOrder(nodoPaciente *arbolPaciente);
nodoPaciente* cargarArbolDesdeArchivo(char archivo[],nodoPaciente* arbol);
///FUNCIOES INGRESOS
void mostrarAux(stIngresos dato);
void mostrarIngreso(nodoIngresos* lista);
int validarDNIyEncontrar(nodoPaciente* arbol,nodoPaciente** encontrado);
nodoPaciente * alta_de_ingreso(nodoPaciente * arbolPaciente);
int contarIngresosenArchivo( char archivo[]);
void modificarArchivoIngresos(char archivo[],stIngresos datonuevo); ///por parametro ya debemos pasar el ingreso modificado
nodoIngresos* buscarPorNroIngreso(nodoPaciente* arbol, int nroIngreso); /// busca nro de ingreso de determinado paciente No filtrado
nodoIngresos* buscarListaPractica(nodoPaciente * arbol,int nroIngreso);
nodoPaciente* cargarIngresosDesdeArchivo(char archivo[],nodoPaciente* arbol);
nodoIngresos * filtrarPorNroIngreso(nodoPaciente* arbol);
nodoIngresos* filtrarPorFechaIngreso(nodoPaciente* arbol);
nodoIngresos * crearNodoIng (stIngresos a);
nodoIngresos * agregarPpioIngresos(nodoIngresos * lista, nodoIngresos * nuevo);
nodoIngresos * agregarOrdenFecha(nodoIngresos * lista, nodoIngresos * nuevo);
void mostrarPorFechas(nodoIngresos * listaIngresos,nodoPaciente * arbolPaciente);
nodoPaciente* cargarArbolDesdeArchivo(char archivo[],nodoPaciente* arbol);
void filtrarPorDNI(nodoPaciente * arbol);
nodoIngresos * filtrarIngreso(nodoPaciente* arbol);
nodoIngresos* filtrarIngresoParaMostrar(nodoPaciente* arbol);
stIngresos cargarIngresos();
void agregarNuevoIngresoArchivo(char archivo[],stIngresos nuevo);
void modificarArchivoIngresos(char archivo[],stIngresos datonuevo);
int contarIngresosenArchivo( char archivo[]);
int validarDNIyEncontrar(nodoPaciente* arbol,nodoPaciente** encontrado);
///FUNCIONES PARA PRACTICASXINGRESO
void mostrarPxiAUX(stPracXingreso dato);
void mostrarPxi(nodoPracticasXingreso* lista);
void buscarPrefijoPractica(nodoPracticasXingreso* lista,char prefijo[]);
void buscarPrefijoIngreso(nodoIngresos* lista,char prefijo[]);
void buscarPrefijoPaciente(nodoPaciente* arbol,char prefijo[]);
nodoPracticasXingreso* buscarPractica(nodoPracticasXingreso* lista,int numPractica);
nodoPaciente* pasarPracticasAlArbolArchivo(char archivo[],nodoPaciente* arbol);
nodoPracticasXingreso * crearNodoPxI(stPracXingreso pxi);
nodoPracticasXingreso * agregarPpioPXI(nodoPracticasXingreso * lista, nodoPracticasXingreso * nuevoNodo);
stPracXingreso cargarPXI(int numIngreso);
nodoPracticasXingreso * buscarNroPractica(nodoPracticasXingreso * lista, int nroPractica);
nodoPracticasXingreso * Alta_de_pxi(nodoPracticasXingreso * lista,int num);
nodoPracticasXingreso * modificacion_de_pxi(nodoPracticasXingreso * lista);
nodoPracticasXingreso * Baja_de_pxi(nodoPracticasXingreso * lista);
void agregarPxialArchivo(char archivo[], stPracXingreso dato);
void mostrarArchivoPXI(char archivo[]);
int contarPxienArchivo( char archivo[]);
void modificarArchivoPXI(char archivo[], stPracXingreso dato);

///VALIDACIONES
int validarNombre(char * nombre);
int validarEdad (char * edad);
int validarDNI(char * dni);
int validarTelefono(char * telefono);
int validarDireccion(char * direccion);
int validarNumero(char * nroPractica);
void mostrarPaciente(stPacientes dato);
#endif // ARBOLPACIENTE_H_INCLUDED
