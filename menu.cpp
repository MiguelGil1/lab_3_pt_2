#include "menu.h"
#include "encriptar_desencriptar.h"
#include "sudo.h"
#include "usuarios.h"
void menu::gui(){
    sudo administrador;
    usuarios users;
    int opt;
    bool key = true;
    while(key == true){
        cout << "Bienvenido a su cajero electronico." << endl;
        cout << "1.) Ingresar como administrador." << endl;
        cout << "2.) Ingresar como usuario." << endl;
        cout << "3.) Salir." << endl;
        cout << "Seleccione una opcion: ";
        cin >> opt;

        switch (opt) {
        case 1:{
            system("CLS");
            administrador.verifying_password();
            break;
        }
        case 2:{
            system("CLS");
            users.users();
            break;
        }
        case 3:
            cout << "Gracias por utilizar nuestros servicios :)" << endl;
            key = false;
            break;
        default:
            cout << "Opcion fuera de rango.\nIntente de nuevo." << endl;
            break;
        }
        if(opt != 3){
            system("PAUSE");
            system("CLS");
        }
    }
}
