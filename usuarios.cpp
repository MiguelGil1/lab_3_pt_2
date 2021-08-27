/*
 Para la implementacion de la funcion users perteneciente a la libreris usuarios.h
 es necesario incluir las librerias encriptar_desencriptar.h ya que se necesita para
 leer la informacion contenida en el archivo usuarios.txt y decodificarla

 Este archivo debe estar en la siguiente ruta relativa: ../usuarios.txt

 Luego de decodificarla, almacena la informacion obtenida en un archivo temporal
 llamado usuarios_decodifcados.txt

 Todo esto con la intecion de leer cada uno de los usuarios hasta encontrar el id
 del usuario que esta intentando acceder a su cuenta.

 Cuando lo encuentre, guardara sus datos y se redigira a un submenu en el cual el
 usuario tendra la posibilidad de elergit entre 3 opciones:

 Opcion 1: Permite retirar dinero, condiciones: Si la cantidad ingresada a retirar
 mas la couta de manejo (1000 COP) es mayor al saldo no podra retirar.

 Opcion 2: Consultar saldo. Condiciones. Si el usuario tiene menos de mil pesos
 colombianos, no podra consultar su saldo.

 Opcion 3: Salir: El usuario sale de su cuenta,

 Si el usuario ingresa otro numero diferente a 1,2 o 3, se le informara que la
 opcion elegida se encuentra fuera de rango.
*/
#include "usuarios.h"
#include <fstream>
#include <string.h>
string usuarios::getId_ingresada() const{
    return id_ingresada;
}

void usuarios::setId_ingresada(const string &value){
    id_ingresada = value;
}

bool usuarios::getEncontrado() const{
    return encontrado;
}

void usuarios::setEncontrado(bool value){
    encontrado = value;
}

string usuarios::getId() const{
    return id;
}

void usuarios::setId(const string &value){
    id = value;
}

int usuarios::getClave_usuario() const{
    return clave_usuario;
}

void usuarios::setClave_usuario(int value){
    clave_usuario = value;
}

int usuarios::getSaldo() const{
    return saldo;
}

void usuarios::setSaldo(int value){
    saldo = value;
}

int usuarios::getSaldo_a_retirar() const{
    return saldo_a_retirar;
}

void usuarios::setSaldo_a_retirar(int value){
    saldo_a_retirar = value;
}

bool usuarios::getEstado_transaccion() const{
    return estado_transaccion;
}

void usuarios::setEstado_transaccion(bool value){
    estado_transaccion = value;
}

void usuarios::verifying_existence(string id_usuario){
    ifstream Leer;
    ofstream Guardar;
    const int semilla = 4, metodo = 2;

    //Se dedodifica la informacion contendia en el archivo usuarios
    //string id_usuario = getId_ingresada();
    string id_tmp = "";
    setEncontrado(false);
    int saldo_transaccional = 0, clave = 0;

    //Se abre el archivo usuarios_decodificados.txt y se guarda la info
    //de los usuarios decodificados.
    string contendido_archivo = lib_codificar.decodificar(semilla,metodo,"usuarios");
    if(contendido_archivo == ""){
        cout << "Acceso denegado!\nNo hay usuarios registrados en la DB del ATM." << endl;
    }else{
        Guardar.open("../usuarios_decodificados.txt");
        Guardar << contendido_archivo;
        Guardar.close();
        bool find_usr = false;

        //Se abre el archivo usuarios_decodifucados.txt
        Leer.open("../usuarios_decodificados.txt");
        char linea[300];
        Leer.getline(linea,sizeof(linea));
        char id[15];
        //Se lee el archivo hasta que se llegue al final del mismo
        while(!Leer.eof()){
            //Se crea un for que iterara 3 veces ya que son 3 los datos a leer
            //Id, clace, saldo
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
            //Se evalua si el id leido es igual al id a actualizar
            if(id_usuario == id_tmp){
                //Si se encuentra se iguala la variable tipo bool encontrado a true
                setEncontrado(true);
                find_usr = true;
                //Le envia a los atributos privados cada una de las caracteristicas del usuario
                //id, clave y saldo
                setId(id_tmp);
                setClave_usuario(clave);
                setSaldo(saldo_transaccional);
                break;
            }else{
                //De lo contrario se lee la sigueinte linea
                Leer.getline(linea,sizeof(linea));
            }
        }
        Leer.close();
        if(find_usr == false){
            //Sie el usuario no se encuentra se elimina el archivo
            remove("../usuarios_decodificados.txt");
        }
    }
}
void usuarios::retirar(){
    //Obtiene el saldo que el usuario desea retirar
    int retirar_saldo = getSaldo_a_retirar();
    //Obtiene el saldo actual
    int saldo_transaccional = getSaldo();
    //Se verifica si el saldo que se desa retirar + 100 es menor o igual al saldo actual
    if((retirar_saldo+1000) <= saldo_transaccional){
        //Si lo es, se procede a retirar el dinero y se le envia true a estado_transaccion
        saldo_transaccional -= (1000 + retirar_saldo);
        setEstado_transaccion(true);
        setSaldo(saldo_transaccional);
    }else{
        //De lo contrario se le envia false a estado_trnsaccion
        setEstado_transaccion(false);
    }
}
void usuarios::consultar_saldo(){
    //Trae el saldo actual de lacuenta
    int saldo_transaccional = getSaldo();
    //Evalua si el saldo es mayor o igual a 1000
    if(saldo_transaccional >= 1000){
        //Si lo es, le resta 1000 al saldo actual y lleva true a estado_transaccion
        saldo_transaccional -= 1000;
        setEstado_transaccion(true);
        setSaldo(saldo_transaccional);
    }else{
        //De lo contrario lleva false al estado_transaccion
        setEstado_transaccion(false);
    }
}

void usuarios::actualizar_info(){
    ifstream Leer;
    ofstream Guardar, Temp;
    const int semilla = 4, metodo = 2;

    string usuarios_actualizados = "";
    string id_tmp = "", id_buscar = getId();
    int saldo_transaccional = getSaldo();

    //Se procede a actualizar la info del archivo users
    //Para ello nuevamnte se realiza el mismo ciclo while con el mismo ciclo
    //for anidado, la unica diferencia es que cuando el id_buscar sea igual al
    //id_tmp se guardara el saldo actualizado
    //Toda la informacion se almacena en la variable tipo string usuario_actualizados
    Leer.open("../usuarios_decodificados.txt");
    char linea[300];
    Leer.getline(linea,sizeof(linea));
    char id[15];
    //Se lee el archivo hasta llegar al fin de el mismo
    while(!Leer.eof()){
        //Se crea un for que iterara 3 veces ya que son 3 los datos a leer
        //Id, clace, saldo
        for(int i = 0; i < 3; i++){
            char *puntero;
            if(i == 0){
                //strtok recibe dos parametros, ek primero es la linea que queremos dividir
                //El segundo va a ser el separador y la funcion retorna un puntero
                puntero = strtok(linea, ",");
                strcpy(id, puntero);
                id_tmp = id;
                //Se le aniae la info del usuario
                usuarios_actualizados += id_tmp + ",";
            }else if(i == 1){
                puntero = strtok(NULL,",");
                string clave = "";
                clave = puntero;
                //Se le aniae la info del usuario
                usuarios_actualizados += clave + ",";
            }else if(i == 2){
                if(id_buscar == id_tmp){
                    //Se evalua si el usuario con la sesion activa es igual al usuario en el que se esta iterando
                    string saldo = "";
                    //Se actualiza el saldo
                    saldo = to_string(saldo_transaccional);
                    usuarios_actualizados += saldo + "\n";
                }else{
                    //De lo contario se pone el mismo saldo
                    puntero = strtok(NULL,"\n");
                    string saldo = "";
                    saldo = puntero;
                    usuarios_actualizados += saldo + "\n";
                }

            }
        }
        //Se lee una nueva linea
        Leer.getline(linea,sizeof(linea));
    }
    Leer.close();
    //se codifica el dato almacenado en la variable usuarios_actualizados
    //Y se guarda en una variable tipo string llamada usuarios_actualizados_codificados
    //Para ello se debe tener en cuenta que la funcion codificar, recibe 3 parametros:
    //Int semilla, int metodo, string cadena_a_codificar

    string usuarios_actualizados_codificados;
    bool ban2 = false;
    try {
        usuarios_actualizados_codificados = lib_codificar.codificar(semilla, metodo,usuarios_actualizados);
    }  catch (std :: length_error) {
        cout << "Error\nInformacion codificada demasiado larga." << endl;
        ban2 = true;
    }

    if(ban2 != true){
        //Se guarda en un archivo llamado temp.txt la info codificada
        Temp.open("../temp.txt");
        Temp << usuarios_actualizados_codificados;
        Leer.close();
        Temp.close();

        //Se remueve el archivo usuarios.txt y se renombra el archivo temp.txt
        //por usuarios.txt
        remove("../usuarios.txt");
        rename("../temp.txt","../usuarios.txt");
    }
    //Se remueve el archivo usuarios_decodificados.txt
    remove("../usuarios_decodificados.txt");
}
