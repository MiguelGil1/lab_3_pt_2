#include "usuarios.h"
#include "encriptar_desencriptar.h"
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
void usuarios::users(){
    const int semilla = 4, metodo = 2;
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
}
