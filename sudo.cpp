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
#include <string.h>

string sudo::getClave_sudo_ingresada() const{
    return clave_sudo_ingresada;
}

void sudo::setClave_sudo_ingresada(const string &value){
    clave_sudo_ingresada = value;
}

bool sudo::getKey_clave() const{
    return key_clave;
}

void sudo::setKey_clave(bool value){
    key_clave = value;
}

string sudo::getId_a_registrar() const
{
    return id_a_registrar;
}

void sudo::setId_a_registrar(const string &value){
    id_a_registrar = value;
}

bool sudo::getEncontrado() const{
    return encontrado;
}

void sudo::setEncontrado(bool value){
    encontrado = value;
}

string sudo::getUsuario_a_registrar() const{
    return usuario_a_registrar;
}

void sudo::setUsuario_a_registrar(const string &value){
    usuario_a_registrar = value;
}

void sudo::verifying_password(){
    //VARIABLES PARA LA DECODIFICACION DEL ARCHIVO SUDO.
    const int semilla = 4, metodo = 2;
    string clave_admin;
    string clave_decodificada;
    bool ban = false;

    try {
        //Se obtiene la clave decodificada creando una variabel tipo string
        //Y se invoca la funcion decodificar de la libreria encriptar_desencriptar.h
        clave_admin = getClave_sudo_ingresada();
        clave_decodificada = lib_codificar.decodificar(semilla,metodo,"sudo");
    }  catch (std :: length_error) {
        cout << "Clave ingresada fuera de rango." << endl;
        ban = true;
    }

    //Se evalua si la clave ingresada es igual a la que se encuentra en la del archivo sudo.txt
    if(clave_decodificada == clave_admin and ban != true){
        setKey_clave(true);
    }else{
        setKey_clave(false);
    }
}

void sudo::verifying_existence(){
    ifstream Leer;
    ofstream Guardar;
    const int semilla = 4, metodo = 2;

    //Se dedodifica la informacion contendia en el archivo usuarios
    string id_usuario = getId_a_registrar();
    string id_tmp = "";
    setEncontrado(false);
    int saldo_transaccional = 0, clave = 0;

    //Se abre el archivo usuarios_decodificados.txt y se guarda la info
    //de los usuarios decodificados.
    string contendido_archivo = lib_codificar.decodificar(semilla,metodo,"usuarios");
    Guardar.open("../usuarios_decodificados.txt");
    Guardar << contendido_archivo;
    Guardar.close();

    //Se abre el archivo usuarios_decodifucados.txt
    Leer.open("../usuarios_decodificados.txt");
    char linea[300];
    Leer.getline(linea,sizeof(linea));
    char id[15];
    //Se lee el archivo hasta que se llegue al final del mismo
    while(!Leer.eof()){
        //Se crea un for que iterara 3 veces ya que son 3 los datos a leer
        //Id, clace y saldo
        for(int i = 0; i < 3; i++){
            char *puntero;
            if(i == 0){
                //strtok recibe dos parametros, ek primero es la linea que queremos dividir
                //El segundo va a ser el separador y la funcion retorna un puntero
                puntero = strtok(linea, ",");
                strcpy(id, puntero);
                //Se iguala id_tmp al id leido
                id_tmp = id;
            }else if(i == 1){
                //Homolagamente se realiza lo mismo, solo que se le pasa como puntero NULL
                puntero = strtok(NULL,",");
                //Se convierte el puntero a entero y se iguala a clave
                clave = atoi(puntero);
            }else if(i == 2){
                //Homolagamente se realiza lo mismo, solo que se le pasa como puntero NULL
                puntero = strtok(NULL,"\n");
                //Se convierte el puntero a entero
                saldo_transaccional = atoi(puntero);
                //Se convierte el puntero a entero y se iguala a saldo_transaccional
            }
        }
        //Se evalua si el id leido es igual al id a registrar
        if(id_usuario == id_tmp){
            //Si se encuentra se iguala la variable tipo bool encontrado a true
            setEncontrado(true);
            break;
        }else{
            //De lo contrario se lee la sigueinte linea
            Leer.getline(linea,sizeof(linea));
        }
    }
    Leer.close();
    remove("../usuarios_decodificados.txt");
}
void sudo::sign_in(){
    ifstream Leer;
    ofstream Guardar;
    string usuario_ingr = getUsuario_a_registrar();
    const int semilla = 4, metodo = 2;
    string usuario_codificado = lib_codificar.codificar(semilla,metodo,usuario_ingr);
    Guardar.open("../usuarios.txt",ios::app);
    Guardar << usuario_codificado;
    Guardar.close();
}
/*
        bool session_key = true;
        int opt_admin = 0;

        while (session_key){

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
                string id_tmp = "";
                int saldo_transaccional = 0, clave = 0;
                bool encontrado = false;

                if(usuarios > 0){
                    //Se abre el archivo usuarios_decodificados.txt y se guarda la info
                    //de los usuarios decodificados.
                    string contendido_archivo= lib_codificar.decodificar(semilla,metodo,"usuarios");
                    Guardar.open("../usuarios_decodificados.txt");
                    Guardar << contendido_archivo;
                    Guardar.close();


                    //Se abre el archivo usuarios_decodifucados.txt
                    Leer.open("../usuarios_decodificados.txt");
                    char linea[300];
                    Leer.getline(linea,sizeof(linea));
                    char id[15];
                    //Se lee el archivo hasta que se llegue al final del mismo
                    while(!Leer.eof()){
                        //Se crea un for que iterara 3 veces ya que son 3 los datos a leer
                        //Id, clace y saldo
                        for(int i = 0; i < 3; i++){
                            char *puntero;
                            if(i == 0){
                                //strtok recibe dos parametros, ek primero es la linea que queremos dividir
                                //El segundo va a ser el separador y la funcion retorna un puntero
                                puntero = strtok(linea, ",");
                                strcpy(id, puntero);
                                //Se iguala id_tmp al id leido
                                id_tmp = id;
                            }else if(i == 1){
                                //Homolagamente se realiza lo mismo, solo que se le pasa como puntero NULL
                                puntero = strtok(NULL,",");
                                //Se convierte el puntero a entero y se iguala a clave
                                clave = atoi(puntero);
                            }else if(i == 2){
                                //Homolagamente se realiza lo mismo, solo que se le pasa como puntero NULL
                                puntero = strtok(NULL,"\n");
                                //Se convierte el puntero a entero
                                saldo_transaccional = atoi(puntero);
                                //Se convierte el puntero a entero y se iguala a saldo_transaccional
                            }

                        }
                        //Se evalua si el id leido es igual al id a registrar
                        if(id_usuario == id_tmp){
                            //Si se encuentra se iguala la variable tipo bool encontrado a true
                            encontrado = true;
                            break;
                        }else{
                            //De lo contrario se lee la sigueinte linea
                            Leer.getline(linea,sizeof(linea));
                        }
                    }
                    Leer.close();
                }else{
                    usuarios++;
                }
                //Si encontrado es diferente de true, se procede a pedir la clavr
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
                    string usuario_codificado = lib_codificar.codificar(semilla,metodo,usuario);
                    Guardar.open("../usuarios.txt",ios::app);
                    Guardar << usuario_codificado;
                    Guardar.close();
                    cout << "Usuario creado correctamente!" << endl;
                }else{
                    cout << "Usuario ya existente en la base de datos." << endl;
                }
                //Se remueve el usuario temporal usuarios_decodificados.txt
                remove("../usuarios_decodificados.txt");
                break;
            }
            case 2:
                //Si el usuario selecciona la opcion 2, se procede cerrar sesion
                //Igualanfo la variabel tipo bool session_key a false

            default:
                //Si el usuario ingrese una opcion diferente a 1 o 2 se procede
                //a imprimir en pantalla "Opcion fuera de rango"
                //Para luego imprimir nueamente el submenu

            }

        }
*/


