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
using namespace std;

class sudo{
public:
    void verifying_password();
    string getClave_sudo_ingresada() const;
    void setClave_sudo_ingresada(const string &value);
    bool getKey_clave() const;
    void setKey_clave(bool value);

private:
    codificar_decodificar lib_codificar;
    string clave_sudo_ingresada;
    bool key_clave;
};

#endif // SUDO_H
