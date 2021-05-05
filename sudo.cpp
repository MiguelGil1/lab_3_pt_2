#include "sudo.h"
#include "encriptar_desencriptar.h"
#include <fstream>

codificar_decodificar dato;
int semilla = 4; int metodo = 2;

void sudo::verifying_password(string clave_decodificada, string clave_admin){
    if(clave_decodificada == clave_admin){
        system("CLS");
        bool session_key = true;
        int opt_admin = 0;
        while (session_key){
            cout << "Bienvenido Administrador." << endl;
            cout << "1.) Registrar usuario." << endl;
            cout << "2.) Salir." << endl;
            cout << "Seleccione una opcion: ";
            cin >> opt_admin;
            switch (opt_admin) {
            case 1:{
                system("cls");
                ofstream Guardar;
                string id = "", clave = "", saldo = "", usuario = "";
                cout << "Registro de usuarios." << endl;
                cout << "Ingrese identificacion: ";
                cin >> id;
                usuario += id+",";
                cout << "Ingrese clave (4 digitos): ";
                cin >> clave;
                while(int(clave.length()) != 4){
                    cout << "La clave debe ser de 4 digitos." << endl;
                    cout << "Ingrese clave (4 digitos): ";
                    cin >> clave;
                }
                usuario += clave + ",";
                cout << "Ingrese el saldo: ";
                cin >> saldo;
                usuario += saldo + "\n";
                string usuario_codificado = dato.codificar(semilla,metodo,usuario);
                Guardar.open("../usuarios.txt",ios::app);
                Guardar << usuario_codificado;
                Guardar.close();
                cout << "Usuario creado correctamente!" << endl;
                break;
            }
            case 2:
                cout << "Cerrando sesion" << endl;
                session_key = false;
                break;
            default:
                cout << "Opcion fuera de rango." << endl;
                break;
            }
            if(opt_admin != 2){
                system("PAUSE");
                system("CLS");
            }
        }
    }else{
       cout << "Clave incorrecta" << endl;
    }
}
