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

typedef struct nodoPaciente{
    pacientes paciente;
    struct nodoIngresos * ingresos;
    struct nodoA * izq;
    struct nodoA * der;
}nodoPaciente;

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


typedef struct nodoPracticas{
    practicas prac;
    struct nodoPracticas * sig;
}nodoPracticas;
#endif // ARBOLPACIENTE_H_INCLUDED
