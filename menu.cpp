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
    //sudo administrador;
    int opt = getOpcion_menu_principal();
    switch (opt) {
    case 1:{
        system("CLS");
        string clave;
        cout << "Bienvenido Administrador." << endl;
        cout << "Por favor ingrese la clave: ";
        cin >> clave;
        lib_sudo.setClave_sudo_ingresada(clave);
        lib_sudo.verifying_password();
        bool key = lib_sudo. getKey_clave();

        if(key == true){
            system("CLS");
            bool session_key = true;
            int opt_admin = 0;
            //Mientras el administrador no elija la opcion 2,
            //Se mostrara el siguiente menu
            while(session_key){
                cout << "Bienvenido Administrador." << endl;
                cout << "1.) Registrar usuario." << endl;
                cout << "2.) Salir." << endl;
                cout << "Seleccione una opcion: ";
                cin >> opt_admin;
                switch (opt_admin) {
                case 1:{
                    system("CLS");
                    string id = "", clave = "", saldo = "", usuario = "";
                    cout << "Registro de usuarios." << endl;
                    cout << "Ingrese identificacion: ";
                    cin >> id;
                    lib_sudo.setId_a_registrar(id);
                    lib_sudo.verifying_existence();
                    bool key_usr = lib_sudo.getEncontrado();
                    if(key_usr == false){
                        usuario += id +",";
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
                        lib_sudo.setUsuario_a_registrar(usuario);
                        lib_sudo.sign_in();
                        cout << "Usuario creado correctamente!" << endl;
                    }else{
                        cout << "Usuario ya existente en la base de datos." << endl;
                    }
                    break;
                }
                case 2:{
                    cout << "Cerrando sesion..." << endl;
                    session_key = false;
                    break;
                }
                default:{
                    cout << "Opcion fuera de rango." << endl;
                    break;
                }
                }
                if(opt_admin != 2){
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
        string id = "";
        system("CLS");
        cout << "Bienvenido Usuario." << endl;
        cout << "Por favor ingrese numero de identificacion: ";
        cin >> id;
        //lib_usuarios.setId_ingresada(id);
        lib_usuarios.verifying_existence(id);
        bool key = lib_usuarios.getEncontrado();
        if(key == true){
            int clave_ingresada;
            cout << "Ingrese la clave: ";
            cin >> clave_ingresada;
            int clave = lib_usuarios.getClave_usuario();
            if(clave == clave_ingresada){
                system("cls");
                int opt_usuario = 0;
                cout << "Bienvenido usuario " << id << ", que desea realizar?" << endl;
                cout << "1.) Retirar dinero." << endl;
                cout << "2.) Consultar Saldo." << endl;
                cout << "3.) Salir." << endl;
                cout << "Seleccione una opcion: ";
                cin >> opt_usuario;
                switch (opt_usuario) {
                case 1:{
                    system("cls");
                    int retirar = 0;
                    cout << "Usuario " << id << endl;
                    cout << "Por favor ingrese el dinero a retirar: $ ";
                    cin >> retirar;
                    lib_usuarios.setSaldo_a_retirar(retirar);
                    lib_usuarios.retirar();
                    bool estado = lib_usuarios.getEstado_transaccion();
                    if(estado == true){
                        int saldo_post_transaccion = lib_usuarios.getSaldo();
                        cout << "Retiro exitoso!" << endl;
                        cout << "Saldo actual: $" << saldo_post_transaccion + 1000 << endl;
                    }else{
                        cout << "Fondos insuficientes" << endl;
                    }
                    break;
                }
                case 2:{
                    system("cls");
                    system("CLS");
                    cout << "Usuario " << id << endl;
                    lib_usuarios.consultar_saldo();
                    bool estado = lib_usuarios.getEstado_transaccion();
                    if(estado == true){
                        int saldo_post_transaccion = lib_usuarios.getSaldo();
                        cout << "Su saldo es de: $" << saldo_post_transaccion + 1000 << endl;
                    }else{
                        cout << "Fondos insuficientes" << endl;
                    }
                   break;
                }
                case 3:{
                    cout << "Gracias por utilizar nuestros servicios :)" << endl;
                    cout << "Cerrando sesion..." << endl;
                    break;
                }
                default:{
                    cout << "Opcion fuera de rango." << endl;
                    break;
                }
                }
            }else{
                cout << "Clave incorrecta." << endl;
            }
        }else{
            cout << "No se encontro el usuario ingresado." << endl;
        }
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
