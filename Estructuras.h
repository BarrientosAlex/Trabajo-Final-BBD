#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

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
    char fechaIngreso[10];
    char fechaRetiro[10];
    int dni;
    int matricula;
    int eliminado;
}stIngresos;

typedef struct stPracXingreso{
    int nroIngreso;
    int nroPractica;
    char resultado[40];
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
nodoPaciente * crearNodoPaciente(stPacientes pac);
stPacientes cargarPaciente();
nodoPaciente * insertarPaciente(nodoPaciente * a, stPacientes pac);
nodoPaciente * buscarPacienteDNI (nodoPaciente * a,int dni);
nodoPaciente * alta_de_paciente(nodoPaciente * arbolPaciente);
nodoPaciente * modificacion_de_paciente(nodoPaciente * arbolPaciente);
nodoPaciente * baja_de_paciente(nodoPaciente * arbolPaciente);
nodoPaciente * arbolToarchi(nodoPaciente * arbolPaciente, char archivoPac[]);
nodoPaciente * leerArchivoPaciente(char archivoPac[], nodoPaciente * arbolPaciente);
void inOrder(nodoPaciente *arbolPaciente);
///FUNCIOES INGRESOS
void mostrarIngreso(stIngresos dato);
nodoIngresos * filtrarPorNroIngreso(nodoPaciente* arbol);
nodoIngresos* filtrarPorFechaIngreso(nodoPaciente* arbol);
nodoIngresos * crearNodoIng (stIngresos a);
nodoIngresos * agregarPpioIngresos(nodoIngresos * lista, nodoIngresos * nuevo);
nodoIngresos * agregarOrdenFecha(nodoIngresos * lista, nodoIngresos * nuevo);
void mostrarPorFechas(nodoIngresos * listaIngresos,nodoPaciente * arbolPaciente);

void filtrarPorDNI(nodoPaciente * arbol);
nodoIngresos * filtrarIngreso(nodoPaciente* arbol);
stIngresos cargarIngresos();
///FUNCIONES PARA PRACTICASXINGRESO
nodoPracticasXingreso * crearNodoPxI(stPracXingreso pxi);
nodoPracticasXingreso * agregarPpioPXI(nodoPracticasXingreso * lista, nodoPracticasXingreso * nuevoNodo);
stPracXingreso cargarPXI();
nodoPracticasXingreso * buscarNroIngresoYpractica(nodoPracticasXingreso * lista, stPracXingreso pxi);
nodoPracticasXingreso * Alta_de_pxi(nodoPracticasXingreso * lista);
nodoPracticasXingreso *  modificacion_de_pxi(nodoPracticasXingreso * lista);
nodoPracticasXingreso * Baja_de_pxi(nodoPracticasXingreso * lista);
///VALIDACIONES
int validarNombre(char * nombre);
int validarEdad (char * edad);
int validarDNI(char * dni);
int validarTelefono(char * telefono);
int validarDireccion(char * direccion);
void mostrarPaciente(stPacientes dato);
#endif // ARBOLPACIENTE_H_INCLUDED
