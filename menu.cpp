/*
 Para la implementacion de la funcion gui de la clase menu_principal, se debe tener en cuenta
 que se debe incluir la libreria menu.h.

 Cuando el usuario selecciona la opcion 1: Se le lleva al atributo privado de la clase
 opcion_menu_principal un uno

 Cuando el usuario seleccione la opcion 2: Se le lleva al atributo privado de la clase
 opcion_menu_principal un dos

 Cuando el usuario selecciona la opcion 3: Se le lleva al atributo privado de la clase
 opcion_menu_principal un tres

 -----------------------
Segun la opcion elegida por el usuario, se invoacara la funcion correspondiente
en el metodo llamamiento_de_funcionalidades, el cual retorna true, si el usuario
selecciono una opcion diferente a la 3, de lo contrario retornara false
*/

#include "menu.h"

int menu::getOpcion_menu_principal() const{
    return opcion_menu_principal;
}

void menu::setOpcion_menu_principal(int value){
    opcion_menu_principal = value;
}

void menu::menu_principal(){
    int opt;
    bool key = true;
    /*! SE IMPRIME EL SIGUEINTE MENU PRINCIPAL EL CUAL SE IMPRIMIRA HASTA QUE
     la variable booleana key sea igual a false
    */
    while(key == true){
        cout << "Bienvenido a su cajero electronico." << endl;
        cout << "1.) Ingresar como administrador." << endl;
        cout << "2.) Ingresar como usuario." << endl;
        cout << "3.) Salir." << endl;
        //Se le pide que seleccione una de las opciones
        cout << "Seleccione una opcion: ";
        cin >> opt;
        //Se envia a la variable privada opcion_menu_principal la opcion oingresada por el usuario
        setOpcion_menu_principal(opt);
        //SE ACTUALIZA LA VARIABLE KEY LLAMANDO EL METODO LLAMAMIENTO DE FUNCIONALIDADES
        key = llamamiento_de_funcionalidades();
    }
}
bool menu::llamamiento_de_funcionalidades(){
    //Se crea una variable entera tipo int llamada opt la cual le da el valor del
    //atributo privado opcion_menu_principal
    int opt = getOpcion_menu_principal();

    //Se crea un switch casa con la variable opt
    switch (opt) {
    //Si opt = 1, se ingresara al submenu de administrador
    case 1:{
        system("CLS");

        string clave;
        //SE IMPRIME EL SIGUEINTE SUBMENU:
        cout << "Bienvenido Administrador." << endl;
        cout << "Por favor ingrese la clave: ";
        cin >> clave;
        //De la clase sudo se llaman los metodos setClave_sudo_ingresada y verifyien_Password
        lib_sudo.setClave_sudo_ingresada(clave);
        lib_sudo.verifying_password();
        //Se crea variable booleana key la cual obtiene el valor de la variable
        //privada key_clave, si la clave ingresada por el admin fue erronea
        //sera false, de lo contrario, adquirira un valor de true.
        bool key = lib_sudo.getKey_clave();

        //Si las contrasenas coinciden, se puede acceder como usuario sudo
        if(key == true){
            system("CLS");
            bool session_key = true;
            int opt_admin = 0;
            //Mientras el administrador no elija la opcion 2,
            //Se mostrara el siguiente menu
            while(session_key){
                //Se imprime el menu principal del partado sudo
                cout << "Bienvenido Administrador." << endl;
                cout << "1.) Registrar usuario." << endl;
                cout << "2.) Salir." << endl;
                cout << "Seleccione una opcion: ";
                cin >> opt_admin;
                //Se craa un switch / case para simular LA OPCION QUE TOME EL USUARIO SUDO
                switch (opt_admin) {
                case 1:{
                    system("CLS");
                    string id = "", clave = "", saldo = "", usuario = "";
                    //Se le pide a sudo que ingrese un docuemto a registrar en el ATM
                    cout << "Registro de usuarios." << endl;
                    cout << "Ingrese identificacion: ";
                    cin >> id;
                    //Se le lleva al atributo privado id_a_registrar de la clase sudo
                    //el id a registrar
                    lib_sudo.setId_a_registrar(id);
                    //Se llama el metodo veryfying_existance de la clase sudo para
                    //validar si el docuemto ingresado es ya existente en la base de datos
                    lib_sudo.verifying_existence();
                    //Se crea variabel booleana llamada key_usr la cual
                    //trea el valor del atributo privado de la clase sudo
                    //Si el docuemto se encontr la variable vba a ser igual a true, de lo
                    //contrario sera igual a false
                    bool key_usr = lib_sudo.getEncontrado();
                    if(key_usr == false){
                        //Si key_usr es false, es decir, el docuento ingresado,
                        //No existe en la base de datos del ATM, se procede
                        //a pedir contrasena y saldo
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
                        //Si key_usr es igual a true, es decir, el docuemto
                        //ingresado es exitente en la base de datos del ATM
                        //se procede a impriir el sigueinte msj
                        cout << "Usuario ya existente en la base de datos." << endl;
                    }
                    break;
                }
                case 2:{
                    //SI EL USUARIO SUDO ELIGE LA OPCION 2, SE SALE
                    //DE LA SESION SUDO
                    cout << "Cerrando sesion..." << endl;
                    session_key = false;
                    break;
                }
                default:{
                    //Si la opcion ingresada por le usuario sudo es diferente a 1 y 2
                    //Se imprimira el sigueinte mensaje
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
            //De lo contrario no se podra ingresar y se devolvera al menu inicial
            cout << "Clave incorrecta" << endl;
        }
        break;
    }
    //Si opt = 2, se ingresa al submenu de usuario generico
    case 2:{
        string id = "";
        system("CLS");
        //SE LE PIDE AL USUARIO QUE INGRESE EL DOCUEMENTO DEL TITULAR DE LA CUENTA
        cout << "Bienvenido Usuario." << endl;
        cout << "Por favor ingrese numero de identificacion: ";
        cin >> id;
        //lib_usuarios.setId_ingresada(id);
        //Se llama el metodo de la clase usuarios verifying_existance y se le
        //lleva como parametro el id que el usuario ingreso
        //En dicho metodo se valida si el id ingresado existe en la base de datos del ATM
        lib_usuarios.verifying_existence(id);

        //Se crea variabel booleana llamada key, la cual tiene el valor
        //del atributo privado de la clase usuarios, Encontrado, el cual,
        //sera true si se encontro el suario, de lo contrario, false
        bool key = lib_usuarios.getEncontrado();
        if(key == true){
            //Si key es igual a tru, es decir que el id ingresado existe en la base
            //de datos del ATM y se procede a pedir la ocntrasena
            int clave_ingresada;
            cout << "Ingrese la clave: ";
            cin >> clave_ingresada;
            int clave = lib_usuarios.getClave_usuario();
            if(clave == clave_ingresada){
                //Si la clve ingresada coincide con la clave registrada en la db del ATM
                //se le da acceso alusuario y se imprime el sigueinte mensaje
                system("cls");
                int opt_usuario = 0;
                cout << "Bienvenido usuario " << id << ", que desea realizar?" << endl;
                cout << "1.) Retirar dinero." << endl;
                cout << "2.) Consultar Saldo." << endl;
                cout << "3.) Salir." << endl;
                cout << "Seleccione una opcion: ";
                cin >> opt_usuario;
                //SE CREA UN SWITCH / CASE CON LAS DIFERENTES OPCINES (RETIRAR, CONSULTAR SALDO Y SALIR)
                switch (opt_usuario) {
                case 1:{
                    //Si el usuario eligio la opion 1, retirar, se le pide cuanto diner
                    //va a retirar
                    system("cls");
                    int retirar = 0;
                    cout << "Usuario " << id << endl;
                    cout << "Por favor ingrese el dinero a retirar: $ ";
                    cin >> retirar;
                    //Se le lleva al atrubuto privado de la clase usuario saldo_a_retirar
                    //la variable rertirar
                    lib_usuarios.setSaldo_a_retirar(retirar);
                    //Por medio del metodo retirar de la clase suarios se valida
                    //si el suario tiene fondos suficientes para validar la transaccion
                    lib_usuarios.retirar();
                    //Si el suario tiene fondos suficientes, estaod sera igual a true
                    //de lo contrario, sera igual a false
                    bool estado = lib_usuarios.getEstado_transaccion();
                    if(estado == true){
                        //Si estado igual a true, es decir, se tienen fondos
                        //sufiencites para efecruar el retir
                        int saldo_post_transaccion = lib_usuarios.getSaldo();
                        cout << "Retiro exitoso!" << endl;
                        cout << "Saldo actual: $" << saldo_post_transaccion << endl;
                    }else{
                        //si estaod igual a false, es decir que se tiene
                        //fondos insuficientes se redirige al menu principal y
                        //se imprime el siguiente mensaje
                        cout << "Fondos insuficientes" << endl;
                    }
                    lib_usuarios.actualizar_info();
                    break;
                }
                case 2:{
                    //La opcion dos es consultar el saldo
                    system("cls");
                    system("CLS");
                    cout << "Usuario " << id << endl;
                    //Con el metodo consultar_saldo de la clase usuarios, se valida
                    //si el saldoactual - 1000 es mayot o igual a 0
                    lib_usuarios.consultar_saldo();
                    //Si el suario tiene fondos suficientes, estaod sera igual a true
                    //de lo contrario, sera igual a false
                    bool estado = lib_usuarios.getEstado_transaccion();
                    if(estado == true){
                        //Si el saldo actual - 1000 es mayor o igual a 0, se
                        //procede a decir cuanto dinero tiene el suuario en la cuenta
                        int saldo_post_transaccion = lib_usuarios.getSaldo();
                        cout << "Su saldo es de: $" << saldo_post_transaccion + 1000 << endl;
                    }else{
                        //Si el saldo actual es 0 no se podra realizar la consulta de saldo
                        cout << "Fondos insuficientes" << endl;
                    }
                    lib_usuarios.actualizar_info();
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
                //Si no coinciden ambas claves, se deviulve al usuario al menu principal
                remove("../usuarios_decodificados.txt");//Se elimina el archivo de usuarios_deco
                cout << "Clave incorrecta." << endl;
            }
        }else{
            //Si key es igual a FALSE, es decir que no se encontro el usuario
            // ingresado, se imprime el sigueinte msj y se devuewlve al menu principal
            cout << "No se encontro el usuario ingresado." << endl;
        }
        break;
    }
    //Si opt = 3, salimos del programa
    case 3:
        //Si la opcion ingresada fue la 3 se imprime el siguiente mensaje
        cout << "Gracias por utilizar nuestros servicios :)" << endl;
        //Y se iguala la variable booleana key a false para poder salir del while
        return false;
        break;
    //Si 1 < opt < 3, se ingresa al caso por defecto
    default:
        //Si la opcion ingresada fue la 3 se imprime el sigueinte mensaje
        cout << "Opcion fuera de rango.\nIntente de nuevo." << endl;
        break;
    }
    if(opt != 3){
        //Se limpia la consola
        system("PAUSE");
        system("CLS");
    }
    //SI LA OPCION DEL MENU ES DIFERENTE A 3 SE RETORNA TRUE
    return true;
}