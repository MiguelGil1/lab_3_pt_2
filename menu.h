/*
 Libreria que tiene como principal funcionamiento la gestion del menu principal
 del software del cajero electronico, la cual cuenta con una clase llamada menu
 para su utilidad solo se debe tener en cuenta que se debe incluir la libreria.

 La libreria cuenta con una funcion publica tipo void llamada menu_principal,
 esta funcion es la encargada de imprimir y gestionar el menu principal del usuario.
 El cual puede ingresar a varias opciones:
 Opcion 1: Usuario administrador
 Opcion 2: Usaior generico
 Opcion 3: Salir del ATM

Ademas de esto, tambien tenemos la funcion publica tipo void llamada
llamaniento_de_funcionalidades, la cual, gestiona y se encarga de llamar
 las funcionalidades diferentes del ATM
*/
#ifndef MENU_H
#define MENU_H
#include <iostream>
#include "sudo.h"
#include "usuarios.h"
using namespace std;

class menu{
public:
    void menu_principal();
    bool llamamiento_de_funcionalidades();

    int getOpcion_menu_principal() const;
    void setOpcion_menu_principal(int value);

private:
    int opcion_menu_principal;//Variable que se encarga de almacenar la opcion
    //ingresada porel usuario en el menu principal

    sudo lib_sudo;//Variabel tipo objeto sudo
    usuarios lib_usuarios;//Variable tipo objeto usuarios
};

#endif // MENU_H
