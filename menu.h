/*
 Libreria que tiene como principal fiuncionamiento la gestion del menu principal
 del software del cajero electronico, la cual cuenta con una clase llamada menu
 para su utilidad solo se debe tener en cuenta que se debe incluir la libreria.

 La libreria cuenta con una funcion publica tipo void llamada gui, esta funcion es
 la que en escencia gestiona el menu
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
    void gui_usuarios();
    void mensajes_usuarios();
    void mensajes_sudo();
    int getOpcion_menu_principal() const;
    void setOpcion_menu_principal(int value);
    int getTipo_mensaje_usuarios() const;
    void setTipo_mensaje_usuarios(int value);
    int getTipo_mensaje_sudo() const;
    void setTipo_mensaje_sudo(int value);
    int ingresar_contrasena_usuario();

private:
    int opcion_menu_principal;
    int tipo_mensaje_usuarios;
    int tipo_mensaje_sudo;
    sudo lib_sudo;
    usuarios lib_usuarios;
};

#endif // MENU_H
