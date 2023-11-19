#include <stdio.h>
#include <stdlib.h>
#include "ArbolPaciente.h"
int main()
{
   char archivoPac[]= "pacientes.bin";
    char archivoIng[]= "ingresos.bin";
    char archivoPra[]= "practicas.bin";

    nodoPaciente * arbolPaciente = NULL;
    arbolPaciente = arbolToarchi(arbolPaciente,archivoPac);
    arbolPaciente = leerArchivoPaciente(archivoPac,arbolPaciente);
}
