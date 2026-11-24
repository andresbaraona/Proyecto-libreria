
#include <iostream>
#include <string>
using namespace std;

// Estructura de los usuarios
struct Usuario {
    int id;
    string nombre;
    string clave;
    int rol;
};

// Estructura de los libros
struct Libro {
    int id;
    string titulo;
    string autor;
    int cantidad;
};

// Estructura de los prestamos
struct Prestamo {
    int id;
    int idLibro;
    string usuario;
    bool activo;
};

// Arreglo de prestamos
Prestamo prestamos[100];
int totalPrestamos = 0;

// Arreglo de libros
Libro libros[100];
int totalLibros = 0;

// Arreglo de usuarios
Usuario usuarios[100];
int totalUsuarios = 0;

// Crear usuarios iniciales
void inicializarUsuarios() {
    usuarios[0] = {1, "admin", "admin123", 1};
    usuarios[1] = {2, "lector", "1234", 2};
    totalUsuarios = 2;
}

// Funcion para iniciar sesion
int login() {
    string nombre;
    string clave;

    cout << "\n===== INICIO DE SESION =====" << endl;

    for (int intento = 1; intento <= 3; intento++) {
        cout << "Usuario: ";
        cin >> nombre;

        cout << "Clave: ";
        cin >> clave;

        for (int i = 0; i < totalUsuarios; i++) {
            if (usuarios[i].nombre == nombre &&
                usuarios[i].clave == clave) {

                cout << "\nBienvenido " << nombre << "!" << endl;
                return i;
            }
        }

        cout << "Usuario o clave incorrectos." << endl;
        cout << "Intento " << intento << " de 3." << endl;
    }

    return -1;
}

// Registrar un nuevo usuario
void registrarUsuario() {
    if (totalUsuarios >= 100) {
        cout << "\nNo se pueden registrar mas usuarios." << endl;
        return;
    }

    string nombre;
    string clave;
    int rol;
    bool existe = false;

    cout << "\n===== REGISTRO DE USUARIO =====" << endl;

    cout << "Ingrese el nombre de usuario: ";
    cin >> nombre;

    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].nombre == nombre) {
            existe = true;
        }
    }

    if (existe == true) {
        cout << "Ese nombre de usuario ya existe." << endl;
    } else {
        cout << "Ingrese la clave: ";
        cin >> clave;

        cout << "\nSeleccione el rol:" << endl;
        cout << "1. Administrador" << endl;
        cout << "2. Lector" << endl;
        cout << "Opcion: ";
        cin >> rol;

        if (rol == 1 || rol == 2) {
            usuarios[totalUsuarios].id = totalUsuarios + 1;
            usuarios[totalUsuarios].nombre = nombre;
            usuarios[totalUsuarios].clave = clave;
            usuarios[totalUsuarios].rol = rol;

            totalUsuarios++;

            cout << "\nUsuario registrado correctamente." << endl;
        } else {
            cout << "\nOpcion de rol no valida." << endl;
        }
    }
}


// Registrar un libro
void registrarLibro() {
    if (totalLibros >= 100) {
        cout << "\nNo se pueden registrar mas libros." << endl;
        return;
    }

    cout << "\n===== REGISTRO DE LIBRO =====" << endl;

    libros[totalLibros].id = totalLibros + 1;

    cout << "Ingrese el titulo del libro: ";
    cin.ignore();
    getline(cin, libros[totalLibros].titulo);

    cout << "Ingrese el autor: ";
    getline(cin, libros[totalLibros].autor);

    cout << "Ingrese la cantidad de ejemplares: ";
    cin >> libros[totalLibros].cantidad;

    if (libros[totalLibros].cantidad > 0) {
        totalLibros++;
        cout << "\nLibro registrado correctamente." << endl;
    } else {
        cout << "\nLa cantidad debe ser mayor que cero." << endl;
    }
}

// Mostrar todos los libros
void listarLibros() {
    cout << "\n===== LISTADO DE LIBROS =====" << endl;

    if (totalLibros == 0) {
        cout << "No hay libros registrados." << endl;
    } else {
        for (int i = 0; i < totalLibros; i++) {
            cout << "\nID: " << libros[i].id << endl;
            cout << "Titulo: " << libros[i].titulo << endl;
            cout << "Autor: " << libros[i].autor << endl;
            cout << "Ejemplares: " << libros[i].cantidad << endl;
        }
    }
}

// Buscar un libro por titulo
void buscarLibro() {
    string titulo;
    bool encontrado = false;

    cout << "\n===== BUSCAR LIBRO =====" << endl;
    cout << "Ingrese el titulo: ";
    cin.ignore();
    getline(cin, titulo);

    for (int i = 0; i < totalLibros; i++) {
        if (libros[i].titulo == titulo) {
            cout << "\nLibro encontrado:" << endl;
            cout << "ID: " << libros[i].id << endl;
            cout << "Titulo: " << libros[i].titulo << endl;
            cout << "Autor: " << libros[i].autor << endl;
            cout << "Ejemplares: " << libros[i].cantidad << endl;

            encontrado = true;
        }
    }

    if (encontrado == false) {
        cout << "\nNo se encontro el libro." << endl;
    }
}


// Registrar un prestamo
void prestarLibro() {
    if (totalPrestamos >= 100) {
        cout << "\nNo se pueden registrar mas prestamos." << endl;
        return;
    }

    int idLibro;
    string nombreUsuario;
    int posicionLibro = -1;
    bool usuarioExiste = false;

    cout << "\n===== PRESTAR LIBRO =====" << endl;

    cout << "Ingrese el ID del libro: ";
    cin >> idLibro;

    // Buscar el libro
    for (int i = 0; i < totalLibros; i++) {
        if (libros[i].id == idLibro) {
            posicionLibro = i;
        }
    }

    if (posicionLibro == -1) {
        cout << "No existe un libro con ese ID." << endl;
        return;
    }

    if (libros[posicionLibro].cantidad <= 0) {
        cout << "No hay ejemplares disponibles." << endl;
        return;
    }

    cout << "Ingrese el nombre del lector: ";
    cin >> nombreUsuario;

    // Verificar que el usuario exista y sea lector
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].nombre == nombreUsuario &&
            usuarios[i].rol == 2) {
            usuarioExiste = true;
        }
    }

    if (usuarioExiste == false) {
        cout << "El lector no existe." << endl;
        return;
    }

    // Registrar el prestamo
    prestamos[totalPrestamos].id = totalPrestamos + 1;
    prestamos[totalPrestamos].idLibro = idLibro;
    prestamos[totalPrestamos].usuario = nombreUsuario;
    prestamos[totalPrestamos].activo = true;

    totalPrestamos++;

    // Restar un ejemplar del inventario
    libros[posicionLibro].cantidad--;

    cout << "\nPrestamo registrado correctamente." << endl;
}

// Devolver un libro
void devolverLibro() {
    int idPrestamo;
    bool encontrado = false;

    cout << "\n===== DEVOLVER LIBRO =====" << endl;
    cout << "Ingrese el ID del prestamo: ";
    cin >> idPrestamo;

    for (int i = 0; i < totalPrestamos; i++) {
        if (prestamos[i].id == idPrestamo &&
            prestamos[i].activo == true) {

            for (int j = 0; j < totalLibros; j++) {
                if (libros[j].id == prestamos[i].idLibro) {
                    libros[j].cantidad++;
                }
            }

            prestamos[i].activo = false;
            encontrado = true;

            cout << "\nLibro devuelto correctamente." << endl;
        }
    }

    if (encontrado == false) {
        cout << "\nNo se encontro un prestamo activo con ese ID." << endl;
    }
}

// Funcion de ayuda
void mostrarAyuda() {
    cout << "\n===== AYUDA DEL SISTEMA =====" << endl;
    cout << "Bienvenido al sistema de biblioteca." << endl;
    cout << "\nInstrucciones:" << endl;
    cout << "1. Inicie sesion con su usuario y clave." << endl;
    cout << "2. Seleccione una opcion del menu." << endl;
    cout << "3. El administrador puede registrar usuarios." << endl;
    cout << "4. El lector podra consultar libros y prestamos." << endl;
    cout << "5. Seleccione cerrar sesion para salir del menu." << endl;
    cout << "\nSi tiene problemas, contacte al administrador." << endl;
}

// Mostrar integrantes del proyecto
void mostrarIntegrantes() {
    cout << "\n===== INTEGRANTES DEL PROYECTO =====" << endl;
    cout << "Nombre: Carlos Baraona" << endl;
    cout << "Carnet: 00373424" << endl;
}

// Menu del administrador
void menuAdministrador() {
    int opcion;

    do {
        cout << "\n===== MENU ADMINISTRADOR =====" << endl;
        cout << "1. Registrar usuario" << endl;
        cout << "2. Mostrar ayuda" << endl;
        cout << "3. Registrar libro" << endl;
        cout << "4. Listar libros" << endl;
        cout << "5. Buscar libro" << endl;
        cout << "6. Prestar libro" << endl;
        cout << "7. Devolver libro" << endl;
        cout << "8. Mostrar integrantes" << endl;
        cout << "9. Cerrar sesion" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarUsuario();
                break;

            case 2:
                mostrarAyuda();
                break;

            case 3:
                registrarLibro();
                break;

            case 4:
                listarLibros();
                break;

            case 5:
                buscarLibro();
                break;

            case 6:
                prestarLibro();
                break;

            case 7:
                devolverLibro();
                break;

            case 8:
                mostrarIntegrantes();
                break;

            case 9:
                cout << "\nCerrando sesion..." << endl;
                break;

        

          
            default:
                cout << "\nOpcion no valida." << endl;
        }

    } while (opcion != 9);
}


// Menu del lector
void menuLector() {
    int opcion;

    do {
        cout << "\n===== MENU LECTOR =====" << endl;
        cout << "1. Mostrar ayuda" << endl;
        cout << "2. Cerrar sesion" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarAyuda();
                break;

            case 2:
                cout << "\nCerrando sesion..." << endl;
                break;

            default:
                cout << "\nOpcion no valida." << endl;
        }

    } while (opcion != 2);
}

// Programa principal
int main() {
    inicializarUsuarios();

    int posicion = login();

    if (posicion != -1) {
        if (usuarios[posicion].rol == 1) {
            cout << "Has ingresado como ADMINISTRADOR." << endl;
            menuAdministrador();
        } else {
            cout << "Has ingresado como LECTOR." << endl;
            menuLector();
        }
    } else {
        cout << "\nSe agotaron los intentos." << endl;
    }

    return 0;
}