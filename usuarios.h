/*
 En esta libreria se tiene una clase llamada usuaarios, contiene una funcion
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
    void verifying_existence(string);
    void retirar();
    void consultar_saldo();
    void actualizar_info();

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
    codificar_decodificar lib_codificar;
    string id_ingresada;
    bool encontrado;
    bool estado_transaccion;

    //ATRIBUTOS DE USUARIO
    string id;
    int clave_usuario;
    int saldo;
    int saldo_a_retirar;
};

#endif // USUARIOS_H
