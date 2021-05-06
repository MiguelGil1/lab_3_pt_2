#include "sudo.h"
#include "encriptar_desencriptar.h"
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>


void sudo::verifying_password(){
    const int semilla = 4, metodo = 2;
    codificar_decodificar dato;
    ifstream Leer;
    ofstream Guardar, Temp;
    string clave_admin = "";
    cout << "Bienvenido Administrador." << endl;
    cout << "Por favor ingrese la clave: ";
    cin >> clave_admin;
    string clave_decodificada = dato.decodificar(semilla,metodo,"sudo");
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
                string id_usuario = "", clave_usuario = "", saldo = "", usuario = "";
                cout << "Registro de usuarios." << endl;
                cout << "Ingrese identificacion: ";
                cin >> id_usuario;

                string contendido_archivo= dato.decodificar(semilla,metodo,"usuarios");
                string id_tmp = "";
                int saldo_transaccional = 0, clave = 0;
                bool encontrado = false;

                Guardar.open("../usuarios_decodificados.txt");
                Guardar << contendido_archivo;
                Guardar.close();

                Leer.open("../usuarios_decodificados.txt");
                char linea[300];
                Leer.getline(linea,sizeof(linea));
                char id[15];
                while(!Leer.eof()){
                    for(int i = 0; i < 3; i++){
                        char *puntero;
                        if(i == 0){
                            puntero = strtok(linea, ",");
                            strcpy(id, puntero);
                            id_tmp = id;
                        }else if(i == 1){
                            puntero = strtok(NULL,",");
                            clave = atoi(puntero);
                        }else if(i == 2){
                            puntero = strtok(NULL,"\n");
                            saldo_transaccional = atoi(puntero);
                        }

                    }
                    if(id_usuario == id_tmp){
                        encontrado = true;
                        break;
                    }else{
                        Leer.getline(linea,sizeof(linea));
                    }

                }
                Leer.close();
                if(encontrado == false){
                    usuario += id_usuario+",";
                    cout << "Ingrese clave (4 digitos): ";
                    cin >> clave_usuario;
                    while(int(clave_usuario.length()) != 4){
                        cout << "La clave debe ser de 4 digitos." << endl;
                        cout << "Ingrese clave (4 digitos): ";
                        cin >> clave;
                    }
                    usuario += clave_usuario + ",";
                    cout << "Ingrese el saldo: ";
                    cin >> saldo;
                    usuario += saldo + "\n";
                    string usuario_codificado = dato.codificar(semilla,metodo,usuario);
                    Guardar.open("../usuarios.txt",ios::app);
                    Guardar << usuario_codificado;
                    Guardar.close();
                    cout << "Usuario creado correctamente!" << endl;
                }else{
                    cout << "Usuario ya existente en la base de datos." << endl;
                }
                remove("../usuarios_decodificados.txt");
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
