/*
 CLAVE DE ADMINISTRADOR: 1001249237

 DOCUMENTACION DEL ARCHIVO MAIN.
 Para el main solo es necesario importar la libreria menu.h, esta libreria contiene
 una funcion tipo void publica llamada gui. Seguido a eso, se llama una
 variable tipo menu para luego invocar la funcion gui no tiene ningun parametro
 de entrada.
*/
#include <iostream>
#include "menu.h"

using namespace std;

int main(){
    menu mostrar_menu;
    mostrar_menu.menu_principal();
    return 0;
}
