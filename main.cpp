/*
 CLAVE DE ADMINISTRADOR: 1001249237
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include "encriptar_desencriptar.h"

using namespace std;
const int metodo = 2;
const int semilla = 4;

int main()
{
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
            codificar_decodificar dato;
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
                    if(opt != 2){
                        system("PAUSE");
                        system("CLS");
                    }
                }
            }else{
               cout << "Clave incorrecta" << endl;
            }
            break;
        }
        case 2:{
            system("CLS");
            string usuarios_actualizados = "";
            codificar_decodificar dato;
            ifstream Leer;
            ofstream Guardar, Temp;
            string id_buscar = "", id_tmp = "";
            int clave = 0, saldo_transaccional = 0, clave_usuario = 0;
            bool encontrado = false;


            cout << "Bienvenido Usuario." << endl;
            cout << "Por favor ingrese numero de identificacion: ";
            cin >> id_buscar;
            string contendido_archivo= dato.decodificar(semilla,metodo,"usuarios");


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
                if(id_buscar == id_tmp){
                    encontrado = true;
                    break;
                }else{
                    Leer.getline(linea,sizeof(linea));
                }

            }
            Leer.close();
            if(encontrado == false){
                cout << "No se encontro el usuario ingresado." << endl;
            }else{
                cout << "Ingrese la clave: ";
                cin >> clave_usuario;
                if(clave == clave_usuario){
                    int opt_usuario = 0;
                    bool session_key = true;
                    system("CLS");
                    while(session_key){
                        cout << "Bienvenido usuario " << id_buscar << endl;
                        cout << "1.) Retirar dinero." << endl;
                        cout << "2.) Consultar Saldo." << endl;
                        cout << "3.) Salir." << endl;
                        cout << "Seleccione una opcion: ";
                        cin >> opt_usuario;
                        switch (opt_usuario) {
                        case 1:{
                            system("CLS");
                            int retirar = 0;
                            cout << "Usuario " << id_buscar << endl;
                            cout << "Por favor ingrese el dinero a retirar: $ ";
                            cin >> retirar;
                            if((retirar+1000) <= saldo_transaccional){
                                saldo_transaccional -= (1000 + retirar);
                                cout << "Retiro exitoso!" << endl;
                                cout << "Saldo actual: $" << saldo_transaccional << endl;
                            }else{
                                cout << "Fondos insuficientes" << endl;
                            }
                            session_key = false;
                            break;
                        }
                        case 2:
                            system("CLS");
                            cout << "Usuario " << id_buscar << endl;
                            if(saldo_transaccional >= 1000){
                                cout << "Su saldo es de: $" << saldo_transaccional << endl;
                            }else{
                               cout << "Fondos insuficientes" << endl;
                            }
                            saldo_transaccional -= 1000;
                            session_key = false;
                            break;
                        case 3:
                            session_key = false;
                            cout << "Gracias por utilizar nuestros servicios :)" << endl;
                            break;
                        default:
                            cout << "Opcion fuera de rango" << endl;
                            break;
                        }
                    }
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
                                usuarios_actualizados += id_tmp + ",";
                            }else if(i == 1){
                                puntero = strtok(NULL,",");
                                string clave = "";
                                clave = puntero;
                                usuarios_actualizados += clave + ",";
                            }else if(i == 2){
                                if(id_buscar == id_tmp){
                                    string saldo = "";
                                    saldo = to_string(saldo_transaccional);
                                    usuarios_actualizados += saldo + "\n";
                                }else{
                                    puntero = strtok(NULL,"\n");
                                    string saldo = "";
                                    saldo = puntero;
                                    usuarios_actualizados += saldo + "\n";
                                }

                            }
                        }
                        Leer.getline(linea,sizeof(linea));
                    }
                    Leer.close();
                    string usuarios_actualizados_codificados = dato.codificar(semilla, metodo,usuarios_actualizados);
                    Temp.open("../temp.txt");
                    Temp << usuarios_actualizados_codificados;
                    Leer.close();
                    Temp.close();
                    remove("../usuarios.txt");
                    rename("../temp.txt","../usuarios.txt");
                }else{
                    cout << "Clave incorrecta." << endl;
                }
            }
            remove("../usuarios_decodificados.txt");
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
    return 0;
}
