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
#include "encriptar_desencriptar.h"
#include <fstream>
#include <string.h>


void usuarios::users(){
    const int semilla = 4, metodo = 2;
    string usuarios_actualizados = "";
    codificar_decodificar dato;
    ifstream Leer;
    ofstream Guardar, Temp;
    string id_buscar = "", id_tmp = "";
    int clave = 0, saldo_transaccional = 0, clave_usuario = 0;
    bool encontrado = false;
    bool ban = false;


    cout << "Bienvenido Usuario." << endl;
    cout << "Por favor ingrese numero de identificacion: ";
    string contendido_archivo;

    try {
        cin >> id_buscar;
        contendido_archivo = dato.decodificar(semilla,metodo,"usuarios");
    }  catch (std :: length_error) {
        cout << "Id muy largo" << endl;
        ban = true;
    }

    if(ban != true){
        //Se decodifica la informacion almacenada en el archivo usuarios.txt
        //Y se guarda en la variable contenido_archivo


        //Se crea el archivo usuarios_decodificados.txt y se almacena en el
        //La informacion contendia en la variable tipo string contenido_archivo
        Guardar.open("../usuarios_decodificados.txt");
        Guardar << contendido_archivo;
        Guardar.close();


        Leer.open("../usuarios_decodificados.txt");
        char linea[300];
        //Se lee la primera linea del archivo
        Leer.getline(linea,sizeof(linea));
        char id[15];

        //Ciclo while hasta que se llegue al final del archivo
        while(!Leer.eof()){
            //For que itera 3 veces por linea debido a que son 3 los datos almacenados
            //id, clave, saldo
            for(int i = 0; i < 3; i++){
                //Se inicializa una variable tipo puntero a char
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
                    saldo_transaccional = atoi(puntero);
                    //Se convierte el puntero a entero y se iguala a clave
                }

            }
            //Se evualua si el id_tmp (id de la linea) es igual al id que ingreso el usuario
            if(id_buscar == id_tmp){
                //Si es igual, se guala la variable bool encontrado a true y se rompe el
                //ciclo while
                encontrado = true;
                break;
            }else{
                //De lo contrario se lee la siguiente linea
                Leer.getline(linea,sizeof(linea));
            }

        }
        Leer.close();
        if(encontrado == false){
            //Si no se encontro el usuario se imprime lo siguiente
            cout << "No se encontro el usuario ingresado." << endl;
        }else{
            //De lo contrario se procede a preguntarle la clave
            cout << "Ingrese la clave: ";
            //Se le pide al usuario la clave
            cin >> clave_usuario;
            //Se evalua si las claves del archivo usuarios_decodificados y la clave
            //ingresada coinciden
            if(clave == clave_usuario){
                //Si coinciden se imprime el siguiente submenu
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
                        //Si el usuario ingresa la opcion 1 se le pide la
                        //cantidad de dinero a retirar, si dicha cantidad mas 1000 COP
                        //Supera el saldo, se imprime fondos insuficientes
                        //De lo contrario, se podra realizar la transaccion con normalidad
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
                        //Si el usuario ingresa la opcion 2
                        //Se evalua si la cuenta tiene mas de 1000 COP
                        //para poder mostrar el salso, de lo contrario, se imprime
                        //"Fondos insuficientes
                        system("CLS");
                        cout << "Usuario " << id_buscar << endl;
                        if(saldo_transaccional >= 1000){
                            cout << "Su saldo es de: $" << saldo_transaccional << endl;
                            saldo_transaccional -= 1000;
                        }else{
                           cout << "Fondos insuficientes" << endl;
                        }
                        session_key = false;
                        break;
                    case 3:
                        //Si el usuario ingresa la ipcion 3, se sale de la cuenta
                        session_key = false;
                        cout << "Gracias por utilizar nuestros servicios :)" << endl;
                        break;
                    default:
                        cout << "Opcion fuera de rango" << endl;
                        break;
                    }
                }
                //Se procede a actualizar la info del archivo users
                //Para ello nuevamnte se realiza el mismo ciclo while con el mismo ciclo
                //for anidado, la unica diferencia es que cuando el id_buscar sea igual al
                //id_tmp se guardara el saldo actualizado
                //Toda la informacion se almacena en la variable tipo string usuario_actualizados
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
                //se codifica el dato almacenado en la variable usuarios_actualizados
                //Y se guarda en una variable tipo string llamada usuarios_actualizados_codificados
                //Para ello se debe tener en cuenta que la funcion codificar, recibe 3 parametros:
                //Int semilla, int metodo, string cadena_a_codificar

                string usuarios_actualizados_codificados;
                bool ban2 = false;
                try {
                    usuarios_actualizados_codificados = dato.codificar(semilla, metodo,usuarios_actualizados);
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
            }else{
                //Si la clave ingresada es diferente a la clave del archivo, se imprime lo sigueinte:
                cout << "Clave incorrecta." << endl;
            }
        }

        //Se remueve el archivo usuarios_decodificados.txt
        remove("../usuarios_decodificados.txt");
    }
}
