#include <cstring>
#include "jugador.h"

//void Jugador::Mostrar(){
//    std::cout<<"ID: "<<id<<std::endl;
//    std::cout<<"Nombre: "<<nombre<<std::endl;
//}
int Jugador::getID(){
    return id;
}

void Jugador::setID(int id){
    this->id=id;
}

const char* Jugador::getNombre(){
    return nombre;
}
void Jugador::setNombre(const char* nombre){
    strcpy(this->nombre, nombre);
}


Jugador::~Jugador(){
}
