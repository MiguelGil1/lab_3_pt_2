/*
 En este archivo .cpp se encuentra la aplicacion de la funcion sudo::verifying_password()
 para la cual se incluye la libreria de esta misma "sudo.h"

 Como el codigo implementado requiere desencriptar la clave del archivo del usuario
 administrador es necesarioi importar la libreria destinada poara estos dos objetivos,
 las cuales serian <fstream> y "encriptar_desencriptar.h".

 En primera instancia se le pide al usuario que ingrese la contrasena de administrador,
 luego se procede a leer la informacion del archivo sudo el cual debe estar en la siguiente ruta
 relativa:

 ../sudo.txt

 Para decodificar la informacion alli almacenada se crea un objeto tipo decodificar_decodificar
 para ello es necesario importar la libreria "encriptar_desencriptar.h", y a dicho objeto
 se incvoca la funcion decodificar(int,int,str) la cual tiene como parametros de entrada
 el siguiente orden:

 -> Int: Representa la semilla de decodificacion, en todo el programa se va a utilizar
         la misma semilla de decodificacion la cual es 4, para ello se crea una variable tipo
         const int i se le asigna el valor de 4
 -> Int: Representa el metodo de decodificacion. Al igual que la semilla de
         decodificacion, a lo largo de todo este programa se utilizara el metodo 2,
         por lo cual se procede acrear una variabel tipo const int y se le asigna el valor 2
  -> String: Representa el nombre del archivo a decodificar, el cual se encontrara en la ruta
             relativa ../sudo.txt

  Dicha funcion retorna un string que representa la informacion del archivo ya deocdificado
  Se evalua si la clave ingresada es igual a la clave que se encuentra en el archivo sudo.

  Si son iguales, se abre sesion como admistrador, de lo contrario se imprime en pantalla
  el mensaje de "Clave incorrecta"

  Luego de que se verifique si la clave es correcta, se porcede a imprimir un submenu
  en el cual el administrador puede decidir entre dos opcines.
  Crear usuarios o salir.

 Para la creacion de usuarios, primero se le pide una identidficacion, se debe tener
 en cuenta que NO se pueden registrar dos usuarios con el mismo documento (id), si
 se ingrese un usuario ya existente, el programa imprimira un mensaje iformando de
 situacion. Si el usuario no esta registrado se procede a pedirle una clave, la cual
 debe ser de 4 digitos, de lo contrario se pedira que se ingrese nuevamenta la contrasena
 Y un saldo.


 Se debe tener en cuenta que para la verificacion de si el usuario ya existe o no,
 se procede a hacer uso de la libreria encriptar?desencriptar, en la cual se va
 a decodificar la informacion contendia en el archivo usuarios.txt, la cual debe estar
 en la siguiente ruta relativa:

 ../usuarios.txt

 Para luego akmacenar la infoirmacion decodificada en un archivo temporal'
 llamado usuarios decodificados.

*/

#include "sudo.h"
#include "encriptar_desencriptar.h"
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>

void sudo::verifying_password(){
    //VARIABLES PARA LA DECODIFICACION DEL ARCHIVO SUDO.
    const int semilla = 4, metodo = 2;

    //SE DELCARA UNA VARIABLE TIPO OBJETO codificar_decodeificar
    codificar_decodificar dato;
    ifstream Leer;
    string clave_admin = "";
    cout << "Bienvenido Administrador." << endl;
    cout << "Por favor ingrese la clave: ";
    cin >> clave_admin;

    //Se obtiene la clave decodificada creando una variabel tipo string
    //Y se invoca la funcion decodificar de la libreria encriptar_desencriptar.h
    string clave_decodificada = dato.decodificar(semilla,metodo,"sudo");

    //Se evalua si la clave ingresada es igual a la que se encuentra en la del archivo sudo.txt
    if(clave_decodificada == clave_admin){
        system("CLS");
        bool session_key = true;
        int opt_admin = 0;
        //Mientras el administrador no elija la opcion 2,
        //Se mostrara el siguiente menu
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
                //Se le pide al usuario que ingrese un id
                cin >> id_usuario;

                //Se dedodifica la informacion contendia en el archivo usuarios
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
