/*
 En esta libreria se tiene una clase llamada usuarios, contiene una funcion
 publica tipo void llamada users la cual no tiene parametros de entrada
 y se encarga del la interaccion con funcionalidad de usuarios estandar, los
 cuales tienen el poder de ingresar a su cuenta para consultar su saldo y
 retirar dinero.

 Para su uso es necesario incluir esta libreria y crear un objeto tipo usuarios
*/
#ifndef USUARIOS_H
#define USUARIOS_H
#include <iostream>
#include "encriptar_desencriptar.h"
using namespace std;

class usuarios{
public:
    void verifying_existence(string);//VERIFICA LA EXISTENCIA DE UN USUARIO
    void retirar();//Verifica si se puede retirar el dinero
    void consultar_saldo();//Verifica si se puede consultar el saldo
    void actualizar_info();//Actualiza la info de lois usuarios

    //Metodos setter y getter
    string getId_ingresada() const;
    void setId_ingresada(const string &value);

    bool getEncontrado() const;
    void setEncontrado(bool value);

    string getId() const;
    void setId(const string &value);

    int getClave_usuario() const;
    void setClave_usuario(int value);

    int getSaldo() const;
    void setSaldo(int value);

    int getSaldo_a_retirar() const;
    void setSaldo_a_retirar(int value);

    bool getEstado_transaccion() const;
    void setEstado_transaccion(bool value);

private:
    //SE CREAN OBJETOS DE LAS DEMAS LIBRERIAS A UTILIZAR EN ESTA CLASE
    codificar_decodificar lib_codificar;

    string id_ingresada;//String que almacena el id_ingresado por el usuario
    bool encontrado;//Booleno que es tru si se encontro el usuario en la db delo contrario sera false
    bool estado_transaccion;//Boooleanao que sera true si se puede ralizar la transaccion, de lo contrario sera false

    //ATRIBUTOS DE USUARIO
    string id;
    int clave_usuario;
    int saldo;
    int saldo_a_retirar;
};

#endif // USUARIOS_H
