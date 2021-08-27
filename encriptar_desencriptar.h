/*
 Libreria que tiene una clase llamada codificar_decodificar la cual contiene
dos duncones tipo string:

Para hacer uso de esta clase se debe crear un objeto tipo codificar_decodificar
para luego invocar las funciones publicas

string codificar(int,int,string): Recibe tres parametros de entrada, los cuales son:
 -> Int: Representa la semilla de decodificacion, en todo el programa se va a utilizar
         la misma semilla de decodificacion la cual es 4, para ello se crea una variable tipo
         const int i se le asigna el valor de 4
 -> Int: Representa el metodo de decodificacion. Al igual que la semilla de
         decodificacion, a lo largo de todo este programa se utilizara el metodo 2,
         por lo cual se procede acrear una variabel tipo const int y se le asigna el valor 2
  -> String: Representa el string a codificar.

  Dicha funcion retorna un string que representa la informacion del archivo ya codificado.

string decoficar(int,int,string): Recibe tres parametros de entrada, los cuales son:
 -> Int: Representa la semilla de decodificacion, en todo el programa se va a utilizar
         la misma semilla de decodificacion la cual es 4, para ello se crea una variable tipo
         const int i se le asigna el valor de 4
 -> Int: Representa el metodo de decodificacion. Al igual que la semilla de
         decodificacion, a lo largo de todo este programa se utilizara el metodo 2,
         por lo cual se procede acrear una variabel tipo const int y se le asigna el valor 2
  -> String: Representa el nombre del archivo a decodificar

  Dicha funcion retorna un string que representa la informacion del archivo ya deocdificado
*/
#ifndef ENCRIPTAR_DESENCRIPTAR_H
#define ENCRIPTAR_DESENCRIPTAR_H

#include <iostream>

using namespace std;

class codificar_decodificar{
public:
    string codificar(int,int,string);
    string decodificar(int,int,string);
};
#endif // ENCRIPTAR_DESENCRIPTAR_H
