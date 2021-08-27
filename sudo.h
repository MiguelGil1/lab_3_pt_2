/*
    CLAVE DE USUARIO ADMINISTRADOR: 1001249237
    En esta libreria se tiene una clase llamada sudo, la cual cuanta con una funcion
    publica tipo void llamada verifying_password la cual no tiene ningun parametro
    de entrada.
    Condiciones de uso:
    -> Esta funcion tiene como principal objetivo la verificacion de la clave administrador
       por lo que al invocarla, le pide al usuario que ingrese la clave
       Por lo cual lo que se procede a hacer es a pedir por pantalla la la contrasena
       , luego se lee el archivo sudo.txt que debe estar unicado en esta direccion relativa:

       ../sudo.txt

       se decodifica la informacion alli almacenada y se compara con la clave ingresada
       si son iguales se le da acceso al usuario admistrador para poder registrar usuarios
       en el banco
       De lo contrario se imprimira el mensaje de clave incorrecta
       Para su usuo solo se dede crear un objeto tipo sudo, y con el nombre de la variable
       escrita se puede invocar la funcion verifying_password
*/
#ifndef SUDO_H
#define SUDO_H
#include <iostream>
#include "encriptar_desencriptar.h"
#include <fstream>
using namespace std;

class sudo{
public:
    void verifying_password();//Verifica si la clave ingresada por sudo concuerda
    //con la que hay enel archivo
    void verifying_existence();//Verifica si el suario a registrar existe en la db del ATM
    void sign_in();//Metodo que se encarga de registrar en la db del ATM al usuario

    //Metodo setter y getter de los atributos privados
    string getClave_sudo_ingresada() const;
    void setClave_sudo_ingresada(const string &value);

    bool getKey_clave() const;
    void setKey_clave(bool value);

    string getId_a_registrar() const;
    void setId_a_registrar(const string &value);

    bool getEncontrado() const;
    void setEncontrado(bool value);

    string getUsuario_a_registrar() const;
    void setUsuario_a_registrar(const string &value);

private:
    //Se crea objeto codificar_decodificar a utulizar en esta clase
    codificar_decodificar lib_codificar;

    string clave_sudo_ingresada;//Almacena un string con la clave que ingresa el usuario sudo
    string id_a_registrar;//String que almacena elid a registrar en la db
    string usuario_a_registrar;//String quer almacena la info del usuario que se va a registrar
    bool key_clave;//Booleano que almacena true si las claves suo ingresada y la clave decodificada coinciden, de lo contrario, almacena false
    bool encontrado;//Bool que almacena true si se encientra el usario, de lo contrario false
};

#endif // SUDO_H
