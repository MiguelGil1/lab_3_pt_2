/*
 Para la implementacion de la funcion gui de la clase menu, se debe tener en cuenta
 que se debe incluir las librerias menu.h, sudo.h y usuarios.h ya que seran
 necesarias a la hora de seleccionar la opcion en el submenu

 Cuando el usuario selecciona la opcion 1: Se invoca la funcion verifying_password
 de la libreria sudo para el registro de usuarios

 Cuando el usuario seleccione la opcion 2: Se invoca la duncion users de la libreria
 usuarios.h para realializar retiros y consulta de saldos

 Cuando el usuario selecciona la opcion 3: El programa finaliza
*/

#include "menu.h"
#include "sudo.h"
#include "usuarios.h"

int menu::getOpcion_menu_principal() const{
    return opcion_menu_principal;
}

void menu::setOpcion_menu_principal(int value){
    opcion_menu_principal = value;
}

int menu::getTipo_mensaje_usuarios() const{
    return tipo_mensaje_usuarios;
}

void menu::setTipo_mensaje_usuarios(int value){
    tipo_mensaje_usuarios = value;
}

void menu::menu_principal(){
    int opt;
    bool key = true;
    while(key == true){
        cout << "Bienvenido a su cajero electronico." << endl;
        cout << "1.) Ingresar como administrador." << endl;
        cout << "2.) Ingresar como usuario." << endl;
        cout << "3.) Salir." << endl;
        //Se le pide que seleccione una de las opciones
        cout << "Seleccione una opcion: ";
        cin >> opt;
        setOpcion_menu_principal(opt);
        key = llamamiento_de_funcionalidades();
    }
}
bool menu::llamamiento_de_funcionalidades(){
    //Se crean objetos tipo sudo y usuarios
    sudo administrador;
    usuarios users;
    int opt = getOpcion_menu_principal();
    switch (opt) {
    case 1:{
        system("CLS");
        //Si la opcion ingresada es la 1 se invoca la funcion
        //verifying_password() de la libreria sudo.h
        administrador.verifying_password();
        break;
    }
    case 2:{
        system("CLS");
        //Si la opcion ingresada es la 2 se invoca la funcion
        //users() de la libreria usuarios.h
        users.users();
        break;
    }
    case 3:
        //Si la opcion ingresada fue la 3 se imprime el siguiente mensaje
        cout << "Gracias por utilizar nuestros servicios :)" << endl;
        //Y se iguala la variable booleana key a false para poder salir del while
        return false;
        break;
    default:
        //Si la opcion ingresada fue la 3 se imprime el sigueinte mensaje
        cout << "Opcion fuera de rango.\nIntente de nuevo." << endl;
        break;
    }
    if(opt != 3){
        system("PAUSE");
        system("CLS");
    }
    return true;
}

void menu::gui_usuarios(){
    cout << "Bienvenido Usuario." << endl;
    cout << "Por favor ingrese numero de identificacion: ";
}

void menu::mensajes_usuarios(){
    usuarios users;
    int msj = getTipo_mensaje_usuarios();
    switch (msj){
    case 1:
        cout << "No se encontro el usuario ingresado." << endl;
        break;
    case 2:
        cout << "Ingrese la clave: ";
        int clave_ingresada = 0;
        //Se le pide al usuario la clave
        cin >> clave_ingresada;
        users.setClave_ingresada(clave_ingresada);
        break;
    }
}

