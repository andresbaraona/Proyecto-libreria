
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

// Menu del administrador
void menuAdministrador() {
    int opcion;

    do {
        cout << "\n===== MENU ADMINISTRADOR =====" << endl;
        cout << "1. Registrar usuario" << endl;
        cout << "2. Mostrar ayuda" << endl;
        cout << "3. Cerrar sesion" << endl;
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
                cout << "\nCerrando sesion..." << endl;
                break;

            default:
                cout << "\nOpcion no valida." << endl;
        }

    } while (opcion != 3);
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