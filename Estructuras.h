#ifndef ARBOLPACIENTE_H_INCLUDED
#define ARBOLPACIENTE_H_INCLUDED

typedef struct pacientes{
    char apelyNom[40];
    int edad;
    int dni;
    char direccion[30];
    char telefono[15];
    int eliminado;
} pacientes;


typedef struct ingresos{
    int nroIngreso;
    char fechaIngreso[10];
    char fechaRetiro[10];
    int dni;
    int matricula;
    int eliminado;
}ingresos;

typedef struct pracXingreso{
    int nroIngreso;
    int nroPractica;
    char resultado[40];
}pracXingreso;

typedef struct practicas{
    int nroPractica;
    char nombrePractica[30];
    int eliminado;
}practicas;


typedef struct nodoPracticasXingreso{
    pracXingreso pXi;
    struct nodoPracticas * practicas;
    struct nodoPracticasXingreso * sig;
}nodoPracticasXingreso;

typedef struct nodoIngresos{
    ingresos ingreso;
    struct nodoPracticasXingreso * practicas;
    struct nodoIngresos * sig;
    struct nodoIngresos * ant;
}nodoIngresos;

typedef struct nodoPaciente{
    pacientes paciente;
    struct nodoIngresos * ingresos;
    struct nodoA * izq;
    struct nodoA * der;
}nodoPaciente;


typedef struct nodoPracticas{
    practicas prac;
    struct nodoPracticas * sig;
}nodoPracticas;

nodoPracticas * crearNodoPrac(practicas p);
nodoPracticas * agregarPpio(nodoPracticas * lista, nodoPracticas * nuevo);
nodoPracticas * agregarEnOrdenP(nodoPracticas * lista, nodoPracticas * nuevoNodo);
practicas cargarPracticas();
nodoPracticas * alta_de_Practica(nodoPracticas * lista);
nodoPracticas * modificacion_de_Practica(nodoPracticas * lista);
void  filtrarPorPrefijo (nodoPracticas * lista);
nodoPaciente * crearNodoPaciente(pacientes pac);
pacientes cargarPaciente();
nodoPaciente * insertarPaciente(nodoPaciente * a, pacientes pac);
nodoPaciente * buscarPacienteDNI (nodoPaciente * a,int dni);
nodoPaciente * alta_de_paciente(nodoPaciente * arbolPaciente);
nodoPaciente * modificacion_de_paciente(nodoPaciente * arbolPaciente);
nodoPaciente * baja_de_paciente(nodoPaciente * arbolPaciente);
nodoPaciente * arbolToarchi(nodoPaciente * arbolPaciente, char archivoPac[]);
nodoPaciente * leerArchivoPaciente(char archivoPac[], nodoPaciente * arbolPaciente);
void inOrder(nodoPaciente *arbolPaciente);
nodoIngresos * crearNodoIng (ingresos a);
nodoIngresos * agregarPpioIngresos(nodoIngresos * lista, nodoIngresos * nuevo);
nodoIngresos * agregarOrdenFecha(nodoIngresos * lista, nodoIngresos * nuevo);
void mostrarPorFechas(nodoIngresos * listaIngresos,nodoPaciente * arbolPaciente);
int filtrarPorNroIngreso(nodoIngresos * lista);
int filtrarPorFechaIngreso(nodoIngresos * lista);
int filtrarPorDNI(nodoIngresos * lista);
nodoIngresos * filtrarIngreso(nodoIngresos * lista);
ingresos cargarIngresos();
nodoPracticasXingreso * crearNodoPxI(pracXingreso pxi);
nodoPracticasXingreso * agregarPpioPXI(nodoPracticasXingreso * lista, nodoPracticasXingreso * nuevoNodo);
pracXingreso cargarPXI();
nodoPracticasXingreso * buscarNroIngresoYpractica(nodoPracticasXingreso * lista, pracXingreso pxi);
nodoPracticasXingreso * Alta_de_pxi(nodoPracticasXingreso * lista);
nodoPracticasXingreso *  modificacion_de_pxi(nodoPracticasXingreso * lista);
nodoPracticasXingreso * Baja_de_pxi(nodoPracticasXingreso * lista);


#endif // ARBOLPACIENTE_H_INCLUDED
