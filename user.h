#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
typedef struct {
    int dni;
    char nombreYapellido[40];
    char nombreUsuario [20];
    char contrasena[20];
    char perfil[20];
}stUsuario;
typedef struct
{
    char nombreUsuario[20];
    char contrasena[20];
}stUserAux; ///creo este tipo de dato para poder guardar el usuario y la contraseña en una variable
typedef struct nodoUser
{
    stUsuario dato;
    struct nodoUser* sig;
}nodoUser;


void crearArchivouser(char archivo[]);
void mostrarArchivoUser(char archivo[]);
int validarNombreUser(char archivo[], char usuario[]);
int tipoDeEmpleado(char perfil[]);
int validarUsuarioCompleto(char archivo[],char contrasena[], char usuario[]);
int validarDNI(char archivo[], int dni);
int cargarNuevoUsuario(char archivo[]);
void cargarUsuarioArchivo(char archivo[],stUsuario aux);
stUserAux cargarUser();
int inicioSesion(char archivo[]);
int login(char archivo[]);
///funciones nodos
nodoUser* inicLista();
nodoUser* crearNodo(stUsuario aux);
nodoUser* agregarNodoOrdenado(nodoUser* lista, nodoUser* nuevo);
void mostrarListaUsuarios(nodoUser* lista,int tipoUser);
void mostrarArchivoOrdenado(char archivo[], int tipoUser);
void liberarLista(nodoUser* lista);


#endif // USER_H_INCLUDED
