
///                                       TP FINAL LABORATORIO I 2021
///                          INTEGRANTES: Fazio Galo, Rodriguez Lucia y Seijo Lucas

///     --------------------------------------------------------------------------------------------------

///                                            DEFINICIONES GLOBALES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

const char nombrePeliculas[30] = "peliculas.dat";
const char nombreUsuarios[30] = "usuarios.dat";

typedef struct
{
    int idPelicula; // Autoincremental
    char nombre[50];
    int anio;
    char genero[10]; // ACCION, COMEDIA, DRAMA, ROMANTICA, SUSPENSO, TERROR.
    char actores[3][50];
    int calificacion; // 1 a 5 estrellas
    int estado; // 1 activo - 0 inactivo
} Pelicula;


typedef struct
{
    int id; // Autoincremental
    char apellidoYnombres [50];
    char mail[50];
    char celular[15];
    char password[8];
    Pelicula miLista[50];
    int estado; // 1 activo - 0 inactivo
} Usuario;

///     ---------------------------------------------------------------------------------------------
///                                             PROTOTIPADO

// Peliculas

void cargarArchivoPeliculas (char nombrePeliculas[]);
void cargarVariasPeliculas (char nombrePeliculas[]);
Pelicula cargarPelicula ();
int contarPeliculasEnArchivo (char nombrePeliculas[]);
void mostrarArchivoPeliculas (char nombrePeliculas[], int admin);
void mostrarPelicula(Pelicula aux, int admin);
int verificarNombrePelicula (Pelicula dato);
void modificarPeliculaEnArchivo (char nombrePeliculas[], int nroPelicula, int admin);
void ordenacionSeleccionN (Pelicula A[], int validos);
int posicionMenorN (Pelicula A[], int pos, int validos);
void mostrarListadoPorNombre (char nombreArchivo[], int admin);
void ordenacionSeleccionA (Pelicula A[], int validos);
int posicionMayorA (Pelicula A[], int pos, int validos);
void mostrarListadoPorAntiguedad (char nombrePeliculas[], int admin);
void buscarMostrarPeliculaPorNombre (char nombreUsuarios[], Usuario user, int admin, char nombrePeli[]);
int pasarPeliculaArreglo (Pelicula aux, Pelicula arr[], int i, char genero[]);
int pasarArchivoArreglo (char nombrePeliculas[], Pelicula arr[]);
int filtroGenero (char nombrePeliculas[], Pelicula A[], char genero[]);
void mostrarArreglo(Pelicula arr[], int val);
Usuario cargarMiListaUsuario (char nombreUsuarios[], Usuario user, int admin);
Usuario bajaMiListaUsuario (char nombreUsuarios[], Usuario user, int admin);
void mostrarMiLista (char nombreUsuarios[], Usuario user, int admin);
void altaBajaDePelicula (char nombrePeliculas[], int nroPelicula, int admin);

// Usuarios

void cargarArchivoUsuarios (char nombreUsuarios[]);
void cargarArchivoUsuariosConUnUsuario (char nombreUsuarios[]);
void cargarVariosUsuarios (char nombreUsuarios[]);
void cargarVariosUsuariosAdmin (char nombreUsuarios[]);
Usuario cargarUsuario ();
int contarUsuariosEnArchivo (char nombreUsuarios[]);
void mostrarArchivoUsuarios (char nombreUsuarios[]);
void modificarUsuariosEnArchivoAdmin (char nombreUsuarios[], int nroUsuario);
Usuario modificarUsuariosEnArchivo (char nombreUsuarios[], int nroUsuario);
int verificarMailUsuario (char mailLogin[]);
int verificarPasswordUsuario (char passwordLogin[], char mailLogin[]);
Usuario encontrarUser (char nombreUsuarios[], char mail[]);
int verificarAdmin (Usuario user);
void altaBajaDeUsuario (char nombreUsuarios[], int nroUsuario, int admin, int login);
const int dimensionMiLista = 50;
void mostrarUsuario(Usuario aux);
void recomendacionesPorGeneroFavorito (char nombreUsuarios[], Usuario user, int admin, char generoFavorito[]);
void generoMasVisto (int a, int c, int d, int r, int s, int t, char generoFavorito[]);

// Extras

void imprimirBienvenida();
void sonidoLogin();

///     ---------------------------------------------------------------------------------------------
///                                                 MAIN

int main()
{
    int first;
    int seguirFirst = 0;
    int menu = 0; // Variable del menú de USUARIO/PELICULAS
    int menu1; // Variable de elección del menú USUARIO
    int menu2; // Variable de elección del menú PELICULAS
    int choiceListadoPeliculas;
    char gen[10];
    char mail[50];
    char pass[8];
    int admin = 0;
    int verifMailLogin = 0;
    int verifPasswordLogin = 0;
    Usuario user;
    int seguir = 0;
    int nroID;
    char peliculaABuscar [50];
    Pelicula arregloGenero[50];
    int validosGenero = 0;
    Pelicula arregloGeneroFavorito[50];
    int validosFavorito = 0;
    char generoFavorito[10];
    Pelicula arregloFavoritas[50];
    int validosFavoritas;

    imprimirBienvenida();

    /// Importante para el funcionamiento del sonido:
    // Settings, Compiler, Linker Settings, Other Linker Options, Pegar -lwinmm (con guión incluido)
    // Settings, Compiler, Search Directories, Linkers, Add -> Carpeta del Proyecto
    sonidoLogin();

    // Login y Registro
    while(seguirFirst == 0)
    {
        printf("\nIngrese numero de opcion: ");
        fflush(stdin);
        scanf("%d",&first);

        if(first == 1)
        {
            while (verifMailLogin == 0)
            {
                printf("\nIngrese su e-mail: ");
                fflush(stdin);
                gets(mail);
                verifMailLogin = verificarMailUsuario(mail);
                if (verifMailLogin == 0)
                {
                    printf("El mail ingresado no se encuentra registrado.\n");
                }
            }
            while (verifPasswordLogin == 0)
            {
                printf("\nIngrese su password: ");
                fflush(stdin);
                gets(pass);
                verifPasswordLogin = verificarPasswordUsuario(pass, mail);
                if (verifPasswordLogin == 0)
                {
                    printf("La contrasenia es incorrecta.\n");
                }
            }
            seguirFirst = 1;
        }

        if(first == 2)
        {
            cargarArchivoUsuariosConUnUsuario(nombreUsuarios);
            printf("Usuario cargado con exito.\n");
        }
        if(first!=1 && first!=2)
        {
            printf("\nERROR: la opcion ingresada no existe.\n");
        }
    }

    user = encontrarUser(nombreUsuarios, mail);

    admin = verificarAdmin (user);

    if(admin == 1)
    {
        printf("\n            :::::::::::::: Bienvenido de nuevo ADMINISTRADOR ::::::::::::: \n");
    }

    while(menu != 3 && (menu == 0 || menu == 1 || menu == 2))
    {
        seguir = 0;
        printf("\n                     | 1 - USUARIO || 2 - PELICULAS || 3 - SALIR | \n");
        printf("\nIngrese numero de opcion: ");
        fflush(stdin);
        scanf("%d",&menu);


        while(seguir == 0 && menu != 3)
        {
            if(menu == 1)
            {

                printf("\n    ::: USUARIO :::\n");
                printf("\n* 1 - Alta de usuario");
                printf("\n* 2 - Baja de usuario");
                printf("\n* 3 - Modificacion de datos");
                printf("\n* 4 - Mostrar datos");
                printf("\n* 5 - Volver\n");
                fflush(stdin);
                scanf("%d", &menu1);

                switch(menu1) ///MENU USUARIO
                {
                //ALTA DE USUARIO
                case 1:
                    if(admin == 0) //caso user
                    {
                        if(user.estado == 1)
                        {
                            printf("\nSu usuario ya ha sido dado de alta.\n");
                        }
                        if(user.estado == 0)
                        {
                            altaBajaDeUsuario(nombreUsuarios, user.id, admin, 0);
                        }

                    }

                    if(admin == 1) //caso admin
                    {
                        int choice22;

                        printf("\nDesea dar de alta un usuario que ya esta en el sistema (1) o un usuario nuevo (2): \n");
                        fflush(stdin);
                        scanf("%d", &choice22);
                        if(choice22 == 1)
                        {
                            printf("\nIngrese el ID del usuario a dar de alta.\n");
                            fflush(stdin);
                            scanf("%d", &nroID);

                            altaBajaDeUsuario (nombreUsuarios, nroID, admin, 1);
                        }
                        if(choice22 == 2)
                        {
                            cargarArchivoUsuarios(nombreUsuarios);
                        }

                    }
                    break;

                //BAJA DE USUARIO
                case 2:
                    if(admin == 0) //caso user
                    {
                        altaBajaDeUsuario (nombreUsuarios, user.id, admin, 0);
                    }

                    if(admin == 1) //caso admin
                    {
                        printf("\nIngrese el ID del usuario a dar de baja.\n");
                        fflush(stdin);
                        scanf("%d", &nroID);

                        altaBajaDeUsuario (nombreUsuarios, nroID, admin, 1);
                    }
                    break;

                //MODIFICACION DE DATOS
                case 3:
                    if(admin == 0) //caso user
                    {
                        user = modificarUsuariosEnArchivo (nombreUsuarios, user.id);
                    }

                    if(admin == 1) //caso admin
                    {
                        printf("\nIngrese el ID del usuario a modificar: ");
                        fflush(stdin);
                        scanf("%d",&nroID);

                        modificarUsuariosEnArchivoAdmin (nombreUsuarios, nroID);
                    }
                    break;

                //MOSTRAR DATOS
                case 4:
                    if(admin == 0) //caso user
                    {
                        mostrarUsuario(user);
                    }

                    if(admin == 1) //caso admin
                    {
                        mostrarArchivoUsuarios(nombreUsuarios);
                    }
                    break;

                //VOLVER
                case 5:
                    seguir = 1;

                    break;

                default:
                    printf("\nERROR: el numero ingresado no corresponde a ninguna opcion\n");
                }
            }

            if(menu == 2)
            {
                if(admin == 1)
                {
                    printf("\n    ::: MENU PELICULAS ::: \n");
                    printf("\n* 1 - Listado de peliculas");
                    printf("\n* 2 - Alta de peliculas");
                    printf("\n* 3 - Baja de peliculas");
                    printf("\n* 4 - Modificacion de datos de pelicula");
                    printf("\n* 5 - Consultar por una pelicula");
                    printf("\n* 6 - Volver\n");

                }

                if(admin==0)
                {
                    printf("\n    ::: MENU PELICULAS :::\n");
                    printf("\n* 1 - Listado de peliculas");
                    printf("\n* 2 - Agregar peliculas a mi lista");
                    printf("\n* 3 - Quitar peliculas de mi lista");
                    printf("\n* 4 - Recomendaciones para vos");
                    printf("\n* 5 - Tu lista");
                    printf("\n* 6 - Buscar una pelicula");
                    printf("\n* 7 - Volver\n");

                }

                fflush(stdin);
                scanf("%d", &menu2);

                switch(menu2) ///MENU PELICULAS
                {
                //LISTADO DE PELICULAS
                case 1:
                    printf("\n LISTAR POR: 1 - ORDEN ALFABETICO | 2 - ANIO | 3 - GENERO \n");
                    fflush(stdin);
                    scanf("%d",&choiceListadoPeliculas);

                    if(choiceListadoPeliculas==1)//ORDEN ALFABETICO
                    {
                        printf(" \n   ::: LISTADO ORDENADO POR NOMBRE :::\n");
                        mostrarListadoPorNombre(nombrePeliculas, admin);
                    }

                    if(choiceListadoPeliculas==2)//AÑO
                    {
                        printf(" \n   ::: LISTADO ORDENADO POR ANTIGUEDAD :::\n");
                        mostrarListadoPorAntiguedad(nombrePeliculas, admin);
                    }

                    if(choiceListadoPeliculas==3)//GENERO
                    {
                        printf("\n* Ingrese un genero para filtrar peliculas: ");
                        fflush(stdin);
                        gets(gen);
                        printf(" \n   ::: PELICULAS DEL GENERO INGRESADO :::\n");
                        validosGenero = filtroGenero(nombrePeliculas,arregloGenero,gen);
                        mostrarArreglo(arregloGenero,validosGenero);
                    }
                    if(choiceListadoPeliculas!=1 && choiceListadoPeliculas!=2 && choiceListadoPeliculas!=3)
                    {
                        printf("\nERROR: el numero ingresado no corresponde a ninguna opcion\n");
                    }
                    break;

                //ALTA DE PELICULAS
                case 2:
                    if(admin == 0) //caso user
                    {
                        user = cargarMiListaUsuario(nombreUsuarios, user, admin);
                    }

                    if(admin == 1)//caso admin
                    {
                        int choice22;

                        printf("\nDesea dar de alta una pelicula que ya esta en el sistema (1) o una pelicula nueva (2): \n");
                        fflush(stdin);
                        scanf("%d", &choice22);
                        if(choice22 == 1)
                        {
                            printf("\nIngrese el ID de la pelicula a dar de alta.\n");
                            fflush(stdin);
                            scanf("%d", &nroID);

                            altaBajaDePelicula (nombrePeliculas, nroID, admin);
                        }
                        if(choice22 == 2)
                        {
                            cargarArchivoPeliculas (nombrePeliculas);
                        }
                    }
                    break;

                //BAJA DE PELICULAS
                case 3:
                    if(admin == 0)//caso user
                    {
                        user = bajaMiListaUsuario(nombreUsuarios, user, admin);
                    }

                    if(admin == 1)//caso admin
                    {
                        printf("\nIngrese el ID de la pelicula a dar de baja.\n");
                        fflush(stdin);
                        scanf("%d", &nroID);

                        altaBajaDePelicula (nombrePeliculas, nroID, admin);
                    }
                    break;

                //RECOMENDACIONES
                case 4:

                    if(admin == 0) //case user: mostrar peliculas del genero que más tiene en la lista el usuario
                    {
                        recomendacionesPorGeneroFavorito(nombreUsuarios,user,admin, generoFavorito);
                        validosFavoritas = filtroGenero(nombrePeliculas, arregloFavoritas, generoFavorito);
                        mostrarArreglo(arregloFavoritas, validosFavoritas);

                    }
                    if(admin == 1)//modificamodificarUsuariosEnArchivocion de pelis
                    {
                        printf("\nIngrese el ID de la pelicula a editar.\n");
                        fflush(stdin);
                        scanf("%d", &nroID);

                        modificarPeliculaEnArchivo (nombrePeliculas, nroID, admin);
                    }

                    break;

                //LISTA DEL USUARIO
                case 5:

                    if(admin == 0)//case user
                    {
                        mostrarMiLista(nombreUsuarios, user, admin);
                    }

                    break;

                case 6:
                    if (admin == 0) // case user
                    {
                        printf("\nIngrese el nombre de una pelicula:\n");
                        fflush(stdin);
                        gets(peliculaABuscar);
                        buscarMostrarPeliculaPorNombre(nombrePeliculas,user,admin,peliculaABuscar);

                    }
                    if(admin == 1) //volver menu admin
                    {
                        seguir = 1;
                    }

                //VOLVER
                case 7:
                    if(admin == 0)
                    {
                        seguir = 1; //si es user vuelve atras
                    }


                    break;

                default:
                    printf("\nERROR: el numero ingresado no corresponde a ninguna opcion\n");
                }
            }
            if(menu!=1 && menu!=2 && menu!=3)
            {
                printf("\nERROR: la opcion ingresada no existe.\n");
            }
        }

    }

    return 0;
}

///     ---------------------------------------------------------------------------------------------
///                                              FUNCIONES

///                                            Zona Peliculas

//                                                 Alta
void cargarArchivoPeliculas (char nombrePeliculas[])
{
    FILE * archi;
    archi = fopen(nombrePeliculas, "rb");
    if(archi == NULL)
    {
        archi = fopen(nombrePeliculas, "w+b");
    }
    else
    {
        archi = fopen(nombrePeliculas, "ab");
    }
    cargarVariasPeliculas(nombrePeliculas);
    fclose(archi);
}

void cargarVariasPeliculas (char nombrePeliculas[])
{
    char control = 's';
    Pelicula aux;
    printf("\n******* Bienvenido a la carga de peliculas *******\n");
    FILE * archi;
    while (control == 's')
    {
        archi = fopen(nombrePeliculas, "ab");
        if(archi != NULL)
        {
            aux = cargarPelicula();
            fwrite(&aux, sizeof(Pelicula), 1, archi);

            fclose(archi);
        }
        printf("Desea seguir cargando peliculas? Ingrese (s/n)\n");
        fflush(stdin);
        scanf("%c", &control);
    }
}

Pelicula cargarPelicula ()
{
    int contador = 0;
    int i = 0;
    int verifNombre = 1;
    Pelicula aux;

    contador = contarPeliculasEnArchivo(nombrePeliculas);
    aux.idPelicula = contador + 1;

    while (verifNombre == 1)
    {
        printf("\n* Ingrese nombre de la pelicula: \n");
        fflush(stdin);
        gets(&aux.nombre);
        verifNombre = verificarNombrePelicula(aux);
        if (verifNombre == 1)
        {
            printf("Se ingreso un nombre repetido.\n\n");
        }
    }

    printf("Ingrese anio: \n");
    scanf("%i", &aux.anio);

    printf("Ingrese genero: \n");
    fflush(stdin);
    gets(&aux.genero);

    while (i < 3)
    {
        printf("Ingrese actor/actriz %i: \n", i+1);
        fflush(stdin);
        gets(aux.actores[i]);
        i++;
    }

    printf("Ingrese la calificacion (1 al 5): \n");
    scanf("%i", &aux.calificacion);

    printf("Ingrese el estado: 1 para Activa - 0 para Eliminada \n");
    scanf("%i", &aux.estado);

    return aux;
}

int contarPeliculasEnArchivo (char nombrePeliculas[])
{
    FILE * archi;
    archi = fopen(nombrePeliculas, "rb");
    long int cantidad;

    if(archi != NULL)
    {
        fseek(archi, 0, SEEK_END);
        cantidad = ftell(archi) / sizeof(Pelicula);

        fclose(archi);
    }
    return cantidad;
}

void mostrarArchivoPeliculas (char nombrePeliculas[], int admin)
{
    FILE * archi;
    Pelicula aux;
    archi = fopen(nombrePeliculas, "rb");

    if(archi == NULL)
    {
        printf("No hay peliculas cargadas: \n");
    }
    else
    {
        printf("\n   ::: LISTADO de PELICULAS ::: n\n");
        while(fread(&aux, sizeof(Pelicula),1, archi )>0)
        {
            mostrarPelicula(aux, admin);
        }
        fclose(archi);
    }
}

void mostrarPelicula(Pelicula aux, int admin)
{
    if(admin == 1)
    {
        printf("\n * Id Pelicula: %i \n", aux.idPelicula);
        printf(" * Nombre: %s \n",  aux.nombre);
        printf(" * Anio: %d \n",  aux.anio);
        printf(" * Genero: %s \n",  aux.genero);
        printf(" * Actores: %s, %s y %s \n", aux.actores[0], aux.actores[1], aux.actores[2]);
        printf(" * Calificacion: %i\n", aux.calificacion);
        if(aux.estado == 1)
        {
            printf(" * Estado: disponible\n\n");
        }
        if(aux.estado == 0)
        {
            printf(" * Estado: eliminada\n\n");
        }
        printf("\n------------------------------------------------------------");
    }
    if(admin == 0)
    {
        printf("\n------------------------------------------------------------");
        printf("\n * Nombre: %s \n",  aux.nombre);
        printf(" * Anio: %d \n",  aux.anio);
        printf(" * Genero: %s \n",  aux.genero);
        printf(" * Actores: %s, %s y %s \n", aux.actores[0], aux.actores[1], aux.actores[2]);
        printf(" * Calificacion: %i\n\n", aux.calificacion);
        printf("\n------------------------------------------------------------");
    }
}

//Listado de películas de determinado género
// Mostrar arreglo

void mostrarArreglo(Pelicula arr[], int val)
{
    int i = 0;
    int j = 0;
    while (i < val)
    {
        printf("\n* Nombre de la pelicula : %s\n", arr[i].nombre);
        printf("* Anio: %i\n", arr[i].anio);
        printf("* Genero: %s\n", arr[i].genero);
        printf("* Actores principales: ");
        for (j = 0; j < 3; j++)
        {
            printf("\n-");
            printf(arr[i].actores[j]);
        }
        printf("\n* Calificacion: %i\n", arr[i].calificacion);
        printf("\n----------------------------------------------------------------------------------------------------------------");

        i++;
    }
}

// Pasar varias películas de un genero específico a un arreglo
int filtroGenero (char nombrePeliculas[], Pelicula A[], char genero[])
{
    FILE * archi;

    Pelicula aux;
    int i = 0;

    archi = fopen(nombrePeliculas,"rb");

    if (archi != NULL)
    {
        while(fread(&aux, sizeof(Pelicula), 1, archi) > 0)
        {
            if (pasarPeliculaArreglo(aux, A, i, genero) == 1)
            {
                i++;
            }
        }
        if (i == 0)
        {
            printf("\nNo hay peliculas del genero ingresado.\n");
        }

        fclose(archi);
    }
    return i;
}

// Pasar una película de un género específico a un arreglo
int pasarPeliculaArreglo (Pelicula aux, Pelicula arr[], int i, char genero[])
{
    int flag = 0;
    if (strcmpi(aux.genero,genero) == 0)
    {
        arr[i] = aux;
        flag = 1;
    }

    return flag;
}

// Pasar todas las películas a un arreglo
int pasarArchivoArreglo (char nombrePeliculas[], Pelicula arr[])
{
    FILE * archi;
    Pelicula aux;
    int i = 0;

    archi = fopen(nombrePeliculas,"rb");

    if (archi != NULL)
    {
        while(fread(&aux, sizeof(Pelicula), 1, archi) > 0)
        {
            arr[i] = aux;
            i++;
        }

        fclose(archi);
    }
    return i;
}

// Listar todas las Películas por antigüedad (desde la más nueva a la más vieja)
void mostrarListadoPorAntiguedad (char nombrePeliculas[], int admin)
{
    Pelicula A[50];
    FILE * archi;
    archi = fopen(nombrePeliculas, "rb");

    int validos = 0;
    int i = 0;

    if (archi != NULL)
    {
        validos = pasarArchivoArreglo(nombrePeliculas, A);
        ordenacionSeleccionA(A, validos);

        for (i = validos - 1; i >= 0 ; i--)
        {
            mostrarPelicula(A[i], admin);
            printf("----------------------------------------------------\n");
        }

        fclose(archi);
    }
}

void ordenacionSeleccionA (Pelicula A[], int validos)
{
    int posmenor;
    Pelicula aux;
    int i = 0;
    while (i < validos-1)
    {
        posmenor = posicionMenorA(A, i, validos);
        aux = A[posmenor];
        A[posmenor] = A[i];
        A[i]= aux;
        i++;
    }
}

int posicionMenorA (Pelicula A[], int pos, int validos)
{
    int menor;
    menor = A[pos].anio;
    int posmenor = pos;
    int i = pos + 1;

    while (i < validos)
    {
        if (menor > A[i].anio)
        {
            menor = A[i].anio;
            posmenor = i;
        }
        i++;
    }
    return posmenor;
}

// Listar todas las Películas por orden alfabético (lo ordenado alfabéticamente es el nombre de la Película).
void mostrarListadoPorNombre (char nombreArchivo[], int admin)
{
    Pelicula A[50];

    FILE * archi;
    archi = fopen(nombreArchivo, "rb");

    int validos = 0;
    int i = 0;

    if (archi != NULL)
    {
        validos = pasarArchivoArreglo(nombreArchivo, A);
        ordenacionSeleccionN(A, validos);
        for (i = 0; i < validos; i++)
        {
            mostrarPelicula(A[i], admin);
            printf("----------------------------------------------------\n");
        }

        fclose(archi);
    }
}

void ordenacionSeleccionN (Pelicula A[], int validos)
{
    int posmenor;
    Pelicula aux;
    int i = 0;
    while (i < validos-1)
    {
        posmenor = posicionMenorN(A, i, validos);
        aux = A[posmenor];
        A[posmenor] = A[i];
        A[i]= aux;
        i++;
    }
}

int posicionMenorN (Pelicula A[], int pos, int validos)
{
    char menor[50];
    strcpy(menor, A[pos].nombre);
    int posmenor = pos;
    int i = pos + 1;

    while (i < validos)
    {
        if (strcmpi(menor, A[i].nombre) > 0)
        {
            strcpy(menor, A[i].nombre);
            posmenor = i;
        }
        i++;
    }
    return posmenor;
}

void buscarMostrarPeliculaPorNombre (char nombreUsuarios[], Usuario user, int admin, char nombrePeli[])
{
    Pelicula auxPeli;
    FILE * archiPeli;
    archiPeli = fopen(nombrePeliculas, "rb");
    int flag = 0;

    if (archiPeli != NULL)
    {
        while (flag == 0 && fread(&auxPeli, sizeof(Pelicula), 1, archiPeli) > 0)
        {
            if (strcmpi(auxPeli.nombre, nombrePeli) == 0)
            {
                mostrarPelicula(auxPeli, admin);
                flag = 1;
            }
        }

        if (flag == 0)
        {
            printf("No se encontro la pelicula.\n");
        }
        fclose(archiPeli);
    }
}

//                   Persistencia de datos en Archivos:  Validar si el Usuario o la Película ya existe antes de darlos de alta..
int verificarNombrePelicula (Pelicula dato)
{
    Pelicula aux;
    FILE * archi;
    archi = fopen(nombrePeliculas, "rb");
    int flag = 0;

    if (archi != NULL)
    {
        while(flag == 0 && fread(&aux, sizeof(Pelicula), 1, archi) > 0)
        {
            if (strcmpi(aux.nombre, dato.nombre) == 0)
            {
                flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}

int verificarNombreUsuario (Usuario dato)
{
    Usuario aux;
    FILE * archi;
    archi = fopen(nombreUsuarios, "rb");
    int flag = 0;

    if (archi != NULL)
    {
        while(flag == 0 && fread(&aux, sizeof(Usuario), 1, archi) > 0)
        {
            if (strcmpi(aux.apellidoYnombres, dato.apellidoYnombres) == 0)
            {
                flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}

int verificarPasswordUsuario (char passwordLogin[], char mailLogin[])
{
    Usuario aux;
    FILE * archi;
    archi = fopen(nombreUsuarios, "rb");
    int flag = 0;

    if (archi != NULL)
    {
        while(flag == 0 && fread(&aux, sizeof(Usuario), 1, archi) > 0)
        {
            if (strcmp(passwordLogin, aux.password) == 0 && strcmpi(mailLogin, aux.mail) == 0)
            {
                flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}

int verificarMailUsuario (char mailLogin[])
{
    Usuario aux;
    char choice='0';
    FILE * archi;
    archi = fopen(nombreUsuarios, "rb");
    int flag = 0;

    if (archi != NULL)
    {
        while(flag == 0 && fread(&aux, sizeof(Usuario), 1, archi) > 0)
        {
            if (strcmpi(mailLogin, aux.mail) == 0 && aux.estado == 1)
            {
                flag = 1;
            }

            if (strcmpi(mailLogin, aux.mail) == 0 && aux.estado == 0)
            {
                printf("\nSu usuario ha sido dado de baja, desea darlo de alta? s/n \n");
                fflush(stdin);
                scanf("%c", &choice);
                if(choice == 's')
                {
                    altaBajaDeUsuario(nombreUsuarios, aux.id, 0, 0);
                    flag = 1;
                }
            }
        }
        fclose(archi);
    }
    return flag;
}

Usuario encontrarUser (char nombreUsuarios[], char mail[])
{
    Usuario aux;
    int flag=0;

    FILE * archi;
    archi = fopen(nombreUsuarios, "rb");

    if (archi != NULL)
    {
        while(flag == 0 && fread(&aux, sizeof(Usuario), 1, archi) > 0)
        {
            if (strcmpi(mail, aux.mail) == 0)
            {
                flag = 1;
            }
        }
        fclose(archi);
    }
    return aux;
}

int verificarAdmin (Usuario user)
{
    char admin1[30]="galofazio@gmail.com";
    char admin2[30]="lucaseijo7@gmail.com";
    char admin3[30]="lurdrigz@gmail.com";
    char admin4[30]="carolinaarchuby@hotmail.com";

    int flag=0;

    if(strcmpi(user.mail,admin1)==0 || strcmpi(user.mail,admin2) == 0 || strcmpi(user.mail,admin3) == 0 || strcmpi(user.mail,admin4) == 0)
    {
        flag=1;
    }

    return flag;
}

//      ---------------------------------------------------------------------------------------------
//                                                     Modificacion y Baja Pelicula

void modificarPeliculaEnArchivo (char nombrePeliculas[], int nroPelicula, int admin)
{
    FILE * archi;
    Pelicula aux;
    int flag = 0;
    int choice = 0;
    int nroActor = 0;
    char control = 's';

    archi = fopen(nombrePeliculas, "r+b");

    if (archi != NULL)
    {
        while ((flag == 0 && fread(&aux, sizeof(Pelicula), 1, archi) > 0))
        {
            if (aux.idPelicula == nroPelicula)
            {
                flag = 1;
                mostrarPelicula(aux, admin);
            }
        }

        while (control == 's')
        {
            printf("\nQue desea modificar? Ingrese opcion | NOMBRE: 1 | ANIO: 2 | GENERO: 3 | ACTORES: 4 | CALIFICACION: 5 | ESTADO: 6\n");
            scanf("%i", &choice);

            if (choice == 1)
            {
                printf("\n* Ingrese el nuevo nombre: \n");
                fflush(stdin);
                gets(aux.nombre);
            }
            else if (choice == 2)
            {
                printf("\n* Ingrese el nuevo anio: \n");
                scanf("%i", &aux.anio);
            }
            else if (choice == 3)
            {
                printf("\n* Ingrese el nuevo genero: \n");
                fflush(stdin);
                gets(aux.genero);
            }
            else if (choice == 4)
            {
                printf("\n* Ingrese el numero de actor que desea modificar: \n");
                scanf("%i", &nroActor);
                nroActor = nroActor - 1;
                printf("\n* Ingrese el nombre del nuevo actor: \n");
                fflush(stdin);
                gets(aux.actores[nroActor]);
            }
            else if (choice == 5)
            {
                printf("\n* Ingrese la nueva calificacion: \n");
                scanf("%i", &aux.calificacion);
            }
            else if (choice == 6)
            {
                printf("\n* Ingrese el nuevo estado: \n");
                scanf("%i", &aux.estado);
            }
            else
            {
                printf("\nOpcion incorrecta.\n");
            }

            fseek(archi, sizeof(Pelicula)*(-1), SEEK_CUR);
            fwrite(&aux, sizeof(Pelicula), 1, archi);

            printf("\n* Desea modificar otro aspecto? Ingrese (s/n)\n");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(archi);
    }
}

void altaBajaDePelicula (char nombrePeliculas[], int nroPelicula, int admin)
{
    FILE * archi;
    Pelicula aux;
    int control=1;
    int flag = 0;
    char choice = 0;

    archi = fopen(nombrePeliculas, "r+b");

    if (archi != NULL)
    {
        while ((flag == 0 && fread(&aux, sizeof(Pelicula), 1, archi) > 0))
        {
            if (aux.idPelicula == nroPelicula)
            {
                flag = 1;
                printf("\n ***** Pelicula encontrada *****\n");
                printf("\n");
                mostrarPelicula(aux, admin);
            }
        }

        if(aux.estado == 1)
        {
            printf("\nEsta seguro que desea dar de baja esta pelicula? (s/n) \n");
            fflush(stdin);
            scanf("%c", &choice);

            if(choice == 's')
            {
                aux.estado = 0;

                fseek(archi, sizeof(Pelicula)*(-1), SEEK_CUR);
                fwrite(&aux, sizeof(Pelicula), 1, archi);
            }
            control = 0;
        }


        if(aux.estado == 0 && control!=0)
        {
            printf("\nEsta seguro que desea dar de alta esta pelicula? (s/n) \n");
            scanf("%c", &choice);

            if(choice == 's')
            {
                aux.estado = 1;

                fseek(archi, sizeof(Pelicula)*(-1), SEEK_CUR);
                fwrite(&aux, sizeof(Pelicula), 1, archi);
            }
        }
    }
    fclose(archi);
}
//      ---------------------------------------------------------------------------------------------

///                                                    Zona Usuarios

//                                                          Alta

void cargarArchivoUsuarios (char nombreUsuarios[])    // Carga de usuarios en archivo por parte del admin
{
    FILE * archi;
    archi = fopen(nombreUsuarios, "rb");
    if(archi == NULL)
    {
        archi = fopen(nombreUsuarios, "w+b");
    }
    else
    {
        archi = fopen(nombreUsuarios, "ab");
    }
    cargarVariosUsuariosAdmin(nombreUsuarios);
    fclose(archi);
}
void cargarVariosUsuariosAdmin (char nombreUsuarios[])       // Carga de varios usuarios por parte del admin
{
    char control = 's';
    Usuario aux;
    FILE * archi;
    printf("\n ::: Bienvenido a la carga de usuarios :::\n");
    while (control == 's')
    {
        archi = fopen(nombreUsuarios, "ab");
        if(archi != NULL)
        {
            aux = cargarUsuario();
            fwrite(&aux, sizeof(Usuario), 1, archi);

            fclose(archi);
        }
        printf("Desea seguir cargando usuarios? Ingrese (s/n)\n");
        fflush(stdin);
        scanf("%c", &control);
    }
}

void cargarArchivoUsuariosConUnUsuario (char nombreUsuarios[]) // Para cargar en el archivo el registro de un usuario
{
    FILE * archi;
    archi = fopen(nombreUsuarios, "rb");
    if(archi == NULL)
    {
        archi = fopen(nombreUsuarios, "w+b");
    }
    else
    {
        archi = fopen(nombreUsuarios, "ab");
    }
    cargarVariosUsuarios(nombreUsuarios);
    fclose(archi);
}


void cargarVariosUsuarios (char nombreUsuarios[])           // Para el registro de un usuario
{
    Usuario aux;
    FILE * archi;
    printf("\n ::: Bienvenido a la carga de usuarios :::n");

    archi = fopen(nombreUsuarios, "ab");
    if(archi != NULL)
    {
        aux = cargarUsuario();
        fwrite(&aux, sizeof(Usuario), 1, archi);

        fclose(archi);
    }

}

Usuario cargarUsuario ()
{
    int contador = 0;
    int verifNombre = 1;
    Usuario aux;

    contador = contarUsuariosEnArchivo(nombreUsuarios);
    aux.id = contador + 1;

    while (verifNombre == 1)
    {
        printf("\n* Ingrese apellido y nombres: \n");
        fflush(stdin);
        gets(&aux.apellidoYnombres);
        verifNombre = verificarNombreUsuario(aux);
        if (verifNombre == 1)
        {
            printf("El usuario ya se encuentra registrado.\n\n");
        }
    }

    printf("* Ingrese mail: \n");
    fflush(stdin);
    gets(&aux.mail);

    printf("* Ingrese celular:\nEj: 223-5678910\n");
    fflush(stdin);
    gets(&aux.celular);

    printf("* Ingrese contrasenia | Maximo 7 caracteres: \n");
    fflush(stdin);
    gets(&aux.password);

    aux.estado = 1;

    return aux;
}

int contarUsuariosEnArchivo (char nombreUsuarios[])
{
    FILE * archi;
    archi = fopen(nombreUsuarios, "rb");
    long int cantidad;

    if(archi != NULL)
    {
        fseek(archi, 0, SEEK_END);
        cantidad = ftell(archi) / sizeof(Usuario);

        fclose(archi);
    }
    return cantidad;
}

void mostrarArchivoUsuarios (char nombreUsuarios[])
{
    FILE * archi;
    Usuario aux;
    archi = fopen(nombreUsuarios, "rb");

    if(archi == NULL)
    {
        printf("No hay usuarios cargados: \n");
    }
    else
    {
        printf("\n   ::: Listado de Usuarios ::: n\n");
        while(fread(&aux, sizeof(Usuario),1, archi )>0)
        {
            mostrarUsuario(aux);
            printf("\n------------------------------------------------------------");
        }

        fclose(archi);
    }
}

void mostrarUsuario(Usuario aux)
{
    printf("\n------------------------------------------------------------");
    printf("\nId Usuario: %i \n", aux.id);
    printf("Apellido y Nombres: %s \n",  aux.apellidoYnombres);
    printf("Mail: %s \n",  aux.mail);
    printf("Celular: %s \n", aux.celular);
    printf("Contrasenia: %s \n", aux.password);

    if(aux.estado == 1)
    {
        printf("Estado: activo\n");
    }
    if(aux.estado == 0)
    {
        printf("Estado: inactivo\n");
    }

}

/*      ---------------------------------------------------------------------------------------------     */

//                                  Modificacion y Baja Usuario

void modificarUsuariosEnArchivoAdmin (char nombreUsuarios[], int nroUsuario)  // Modificacion de usuarios para el admin
{
    FILE * archi;
    Usuario aux;
    int flag = 0;
    int choice = 0;
    char control = 's';

    archi = fopen(nombreUsuarios, "r+b");

    if (archi != NULL)
    {
        while ((flag == 0 && fread(&aux, sizeof(Usuario), 1, archi) > 0))
        {
            if (aux.id == nroUsuario)
            {
                flag = 1;
                printf("\n ::: Usuario encontrado :::\n");
                printf("\n");
                mostrarUsuario(aux);
            }
        }

        while (control == 's')
        {
            printf("\nQue desea modificar? Ingrese opcion | NOMBRE: 1 | MAIL: 2 | CELULAR: 3 | CONTRASENIA: 4 | ESTADO: 5\n");
            scanf("%i", &choice);

            if (choice == 1)
            {
                printf("\nIngrese el nuevo nombre: \n");
                fflush(stdin);
                gets(aux.apellidoYnombres);
            }
            else if (choice == 2)
            {
                printf("\nIngrese el nuevo mail: \n");
                fflush(stdin);
                gets(aux.mail);
            }
            else if (choice == 3)
            {
                printf("\nIngrese el nuevo celular: \n");
                fflush(stdin);
                gets(aux.celular);
            }
            else if (choice == 4)
            {
                printf("\nIngrese la nueva contrasenia: \n");
                fflush(stdin);
                gets(aux.password);
            }
            else if (choice == 5)
            {
                printf("\nIngrese el nuevo estado: \n");
                scanf("%i", &aux.estado);
            }
            else
            {
                printf("\nOpcion incorrecta.\n");
            }

            fseek(archi, sizeof(Usuario)*(-1), SEEK_CUR);
            fwrite(&aux, sizeof(Usuario), 1, archi);

            printf("\nDesea modificar otro aspecto? Ingrese (s/n) \n");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(archi);
    }
}

Usuario modificarUsuariosEnArchivo (char nombreUsuarios[], int nroUsuario)  // Modificacion de usuarios para el admin
{
    FILE * archi;
    Usuario aux;
    int flag = 0;
    int choice = 0;
    char control = 's';

    archi = fopen(nombreUsuarios, "r+b");

    if (archi != NULL)
    {
        while ((flag == 0 && fread(&aux, sizeof(Usuario), 1, archi) > 0))
        {
            if (aux.id == nroUsuario)
            {
                flag = 1;
                printf("\n ::: Usuario encontrado :::\n");
                printf("\n");
                mostrarUsuario(aux);
            }
        }

        while (control == 's')
        {
            printf("\nQue desea modificar? Ingrese opcion | NOMBRE: 1 | MAIL: 2 | CELULAR: 3 | CONTRASENIA: 4 \n");
            scanf("%i", &choice);

            if (choice == 1)
            {
                printf("\nIngrese el nuevo nombre: \n");
                fflush(stdin);
                gets(aux.apellidoYnombres);
            }
            else if (choice == 2)
            {
                printf("\nIngrese el nuevo mail: \n");
                fflush(stdin);
                gets(aux.mail);
            }
            else if (choice == 3)
            {
                printf("\nIngrese el nuevo celular: \n");
                fflush(stdin);
                gets(aux.celular);
            }
            else if (choice == 4)
            {
                printf("\nIngrese la nueva contrasenia: \n");
                fflush(stdin);
                gets(aux.password);
            }
            else
            {
                printf("\nOpcion incorrecta.\n");
            }

            fseek(archi, sizeof(Usuario)*(-1), SEEK_CUR);
            fwrite(&aux, sizeof(Usuario), 1, archi);

            printf("\nDesea modificar otro aspecto? Ingrese (s/n) \n");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(archi);
    }
    return aux;
}


void altaBajaDeUsuario (char nombreUsuarios[], int nroUsuario, int admin, int login)
{
    FILE * archi;
    Usuario aux;
    int flag = 0;
    int control = 1;
    char choice = '0';

    archi = fopen(nombreUsuarios, "r+b");

    if (archi != NULL)
    {
        while ((flag == 0 && fread(&aux, sizeof(Usuario), 1, archi) > 0))
        {
            if (aux.id == nroUsuario)
            {
                flag = 1;
                if(login==1)
                {
                    printf("\n ::: Usuario encontrado :::\n");
                    printf("\n");
                    mostrarUsuario(aux);
                }

            }
        }

        if(aux.estado == 1)
        {
            if(admin == 1)
            {
                printf("\nEsta seguro que desea dar de baja este usuario? (s/n) \n");
            }
            if(admin == 0)
            {
                printf("\nEsta seguro que desea dar de baja su usuario? (s/n) \n");
            }
            fflush(stdin);
            scanf("%c", &choice);

            if(choice == 's')
            {
                aux.estado = 0;
                printf(" ::: Se desactivo el usuario exitosamente ::: \n");

                fseek(archi, sizeof(Usuario)*(-1), SEEK_CUR);
                fwrite(&aux, sizeof(Usuario), 1, archi);
            }
            control = 0;
        }

        if(aux.estado == 0 && control!=0)
        {
            if(admin == 1)
            {
                printf("\nEsta seguro que desea dar de alta este usuario? (s/n) \n");
            }
            if(admin == 0)
            {
                printf("\nEsta seguro que desea dar de alta su usuario? (s/n) \n");
            }
            fflush(stdin);
            scanf("%c", &choice);

            if(choice == 's')
            {
                aux.estado = 1;
                printf(" ::: Se activo el usuario exitosamente ::: \n");

                fseek(archi, sizeof(Usuario)*(-1), SEEK_CUR);
                fwrite(&aux, sizeof(Usuario), 1, archi);
            }
        }
    }
    fclose(archi);
}


///                                                     Lista Personal de Películas del Usuario

Usuario cargarMiListaUsuario (char nombreUsuarios[], Usuario user, int admin)
{
    Usuario auxUsu;
    Pelicula auxPeli;
    FILE * archiUsu;
    FILE * archiPeli;
    char nombrePeli[50];
    archiUsu = fopen(nombreUsuarios, "r+b");
    archiPeli = fopen(nombrePeliculas, "r+b");
    int flag1 = 0;
    int flag2 = 0;
    int i = 0;
    char control = 's';

    if (archiUsu != NULL && archiPeli != NULL)
    {
        while ((flag1 == 0 && fread(&auxUsu, sizeof(Usuario), 1, archiUsu) > 0))
        {
            if (auxUsu.id == user.id)
            {
                flag1 = 1;
                mostrarMiLista(nombreUsuarios, user, admin);
                auxUsu = user;
            }
        }

        while (control == 's')
        {
            flag2 = 0;
            rewind(archiPeli);

            printf("Ingrese la pelicula que desee agregar a 'Mi Lista':\n\n");
            fflush(stdin);
            gets(nombrePeli);
            while ((flag2 == 0 && fread(&auxPeli, sizeof(Pelicula), 1, archiPeli) > 0))
            {
                if (auxPeli.idPelicula == auxUsu.miLista[i].idPelicula)
                {
                    i++;
                    rewind(archiPeli);
                }
            }

            rewind(archiPeli);

            while (flag2 == 0 && fread(&auxPeli, sizeof(Pelicula), 1, archiPeli) > 0)
             {
                 if (strcmpi(nombrePeli, auxPeli.nombre) == 0)
                {
                    flag2 = 1;
                    auxUsu.miLista[i] = auxPeli;
                    i++;

                    fseek(archiUsu, sizeof(Usuario)*(-1), SEEK_CUR);
                    fwrite(&auxUsu, sizeof(Usuario), 1, archiUsu);

                    printf(" ::: Se cargo la pelicula exitosamente ::: \n");
                }
             }

            if (flag2 == 0)
            {
                printf("No se encontro la pelicula.\n");
            }
            printf("Desea cargar otra pelicula en la lista? Ingrese (s/n)\n");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(archiPeli);
        fclose(archiUsu);
    }
    return auxUsu;
}

Usuario bajaMiListaUsuario (char nombreUsuarios[], Usuario user, int admin)
{
    Usuario auxUsu;
    Pelicula auxPeli;
    FILE * archiUsu;
    FILE * archiPeli;
    char nombrePeli[50];
    archiUsu = fopen(nombreUsuarios, "r+b");
    archiPeli = fopen(nombrePeliculas, "r+b");
    int flag1 = 0;
    int flag2 = 0;
    int i = 0;
    char control = 's';

    if (archiUsu != NULL && archiPeli != NULL)
    {
        while ((flag1 == 0 && fread(&auxUsu, sizeof(Usuario), 1, archiUsu) > 0))
        {
            if (auxUsu.id == user.id)
            {
                flag1 = 1;
                mostrarMiLista(nombreUsuarios, user, admin);
                auxUsu = user;
            }
        }

        while (control == 's')
        {
            flag2 = 0;
            rewind(archiPeli);

            printf("Ingrese la pelicula que desee quitar de 'Mi Lista':\n\n");
            fflush(stdin);
            gets(nombrePeli);

            i = 0;

            while (flag2 == 0 && i < dimensionMiLista)
             {
                 if (strcmpi(nombrePeli, auxUsu.miLista[i].nombre)  == 0)
                {
                    flag2 = 1;

                    while (i < dimensionMiLista)
                    {
                        auxUsu.miLista[i] = auxUsu.miLista[i+1];
                        i++;
                        fseek(archiUsu, sizeof(Usuario)*(-1), SEEK_CUR);
                        fwrite(&auxUsu, sizeof(Usuario), 1, archiUsu);
                    }
                    printf(" ::: Se quito la pelicula exitosamente ::: \n");
                }
                i++;
             }

            if (flag2 == 0)
            {
                printf("No se encontro la pelicula.\n");
            }
            printf("Desea quitar otra pelicula en la lista? Ingrese (s/n)\n");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(archiPeli);
        fclose(archiUsu);
    }
    return auxUsu;
}

void mostrarMiLista (char nombreUsuarios[], Usuario user, int admin)
{
    Usuario auxUsu;
    Pelicula auxPeli;
    FILE * archiUsu;
    FILE * archiPeli;
    int i = 0;
    int flag = 0;
    archiUsu = fopen(nombreUsuarios, "rb");
    archiPeli = fopen(nombrePeliculas, "rb");

    if(archiUsu != NULL && archiPeli != NULL)
    {
        printf("\n       ::: Mi Lista :::\n\n");
        while ((flag == 0 && fread(&auxUsu, sizeof(Usuario), 1, archiUsu) > 0))
        {
            if (auxUsu.id == user.id)
            {
                flag = 1;
            }
        }

        while(fread(&auxPeli, sizeof(Pelicula), 1, archiPeli) > 0)
        {
            if (auxPeli.idPelicula == auxUsu.miLista[i].idPelicula)
                {
                    mostrarPelicula(auxPeli, admin);
                    i++;
                    rewind(archiPeli);
                }
        }
        fclose(archiPeli);
        fclose(archiUsu);
    }
}

//                                                       Recomendación de Películas
void recomendacionesPorGeneroFavorito (char nombreUsuarios[], Usuario user, int admin, char generoFavorito[])
{
    Usuario auxUsu;
    Pelicula auxPeli;
    int i = 0;
    int flag = 0;
    char accion[10] = "Accion";
    char comedia[10] = "Comedia";
    char drama[10] = "Drama";
    char romantica[15] = "Romantica";
    char suspenso[10] = "Suspenso";
    char terror[10] = "Terror";
    int a = 0;
    int c = 0;
    int d = 0;
    int r = 0;
    int s = 0;
    int t = 0;

    FILE * archiUsu;
    FILE * archiPeli;


    archiUsu = fopen(nombreUsuarios, "rb");
    archiPeli = fopen(nombrePeliculas, "rb");

    if(archiUsu != NULL && archiPeli != NULL)
    {
        while ((flag == 0 && fread(&auxUsu, sizeof(Usuario), 1, archiUsu) > 0))
        {
            if (auxUsu.id == user.id)
            {
                flag = 1;
            }
        }

        while(fread(&auxPeli, sizeof(Pelicula), 1, archiPeli) > 0)
        {
            if(strcmpi(user.miLista[i].genero,accion) == 0)
            {
                a++;
            }
            if(strcmpi(user.miLista[i].genero, comedia) == 0)
            {
                c++;
            }
            if(strcmpi(user.miLista[i].genero,drama) == 0)
            {
                d++;
            }
            if(strcmpi(user.miLista[i].genero,romantica) == 0)
            {
                r++;
            }
            if(strcmpi(user.miLista[i].genero,suspenso) == 0)
            {
                s++;
            }
            if(strcmpi(user.miLista[i].genero,terror) == 0)
            {
                t++;
            }

            i++;
        }

        rewind(archiPeli);

        generoMasVisto(a, c, d, r, s, t, generoFavorito);
    }

    fclose(archiPeli);
    fclose(archiUsu);
}

void generoMasVisto (int a, int c, int d, int r, int s, int t, char generoFavorito[])
{
    if(a > c && a > d && a > r && a > s && a > t)
    {
        strcpy(generoFavorito,"Accion");
    }
    else if(c > d && c > r && c > s && c > t)
    {
        strcpy(generoFavorito,"Comedia");
    }
    else if(d > r && d > s && d > t)
    {
        strcpy(generoFavorito,"Drama");
    }
    else if(r > s && r > t)
    {
        strcpy(generoFavorito,"Romantica");
    }
    else if(s > t)
    {
        strcpy(generoFavorito,"Suspenso");
    }
    else
    {
        strcpy(generoFavorito,"Terror");
    }

}


///                                                          Extras

void imprimirBienvenida()
{
    printf("               888               888            .d88888b.                                              \n");
    printf("               888               888           d88P   Y88b                                             \n");
    printf("               888               888           888     888                                             \n");
    printf("               888       8888b.  88888b.       888     888 88888b.   .d88b.                            \n");
    printf("               888           88b 888  88b      888     888 888  88b d8P  Y8b                           \n");
    printf("               888      .d888888 888  888      888     888 888  888 88888888                           \n");
    printf("               888      888  888 888 d88P      Y88b. .d88P 888  888 Y8b.                               \n");
    printf("               88888888  Y888888 88888P          Y88888P   888  888   Y8888                            \n\n");

    printf("     8888888b.          d8b                             888     888 d8b      888                        \n");
    printf("     888   Y88b         Y8P                             888     888 Y8P      888                        \n");
    printf("     888    888                                         888     888          888                        \n");
    printf("     888   d88P 888d888 888 88888b.d88b.   .d88b.       Y88b   d88P 888  .d88888  .d88b.   .d88b.       \n");
    printf("     8888888P   888P    888 888  888  88b d8P  Y8b       Y88b d88P  888 d88  888 d8P  Y8b d88  88b      \n");
    printf("     888        888     888 888  888  888 88888888        Y88o88P   888 888  888 88888888 888  888      \n");
    printf("     888        888     888 888  888  888 Y8b.             Y888P    888 Y88b 888 Y8b.     Y88..88P      \n");
    printf("     888        888     888 888  888  888   Y8888           Y8P     888   Y88888   Y8888    Y88P        \n\n\n");


    printf("\..................................................................................................\n");
    printf("\..................................................................................................\n");
    printf("\.........................                                     ....................................\n");
    printf("\.........................  | (1)  LOG-IN | (2) REGISTRARSE |  ....................................\n");
    printf("\.........................                                     ....................................\n");
    printf("\..................................................................................................\n");
    printf("\..................................................................................................\n");

}

void sonidoLogin()
{
    PlaySound((LPCSTR)"LabOneSound.wav", NULL, SND_FILENAME | SND_ASYNC );
    sndPlaySound("LabOneSound.wav",1);       // Fondo = 1 Principal = 0
    Sleep(5000);
}
