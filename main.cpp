
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

// Programa principal
int main() {

    inicializarUsuarios();

    int posicion = login();

    if (posicion != -1) {

        if (usuarios[posicion].rol == 1) {
            cout << "Has ingresado como ADMINISTRADOR." << endl;
        }
        else {
            cout << "Has ingresado como LECTOR." << endl;
        }

    }
    else {
        cout << "Se agotaron los intentos." << endl;
    }

    return 0;
}