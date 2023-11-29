#include <cstring>
#include <iostream>
#include "Highscore.h"

Highscore::Highscore(){
}
void Highscore::Mostrar(){
    std::cout<<nombre<<std::endl;
    std::cout<<puntaje<<std::endl;
}
const char* Highscore::getNombre(){
    return nombre;
}
void Highscore::setNombre(const char* nombre){
    strcpy(this->nombre, nombre);
}
int Highscore::getPuntaje(){
    return puntaje;
}
void Highscore::setPuntaje(int puntaje){
    this->puntaje=puntaje;
}

Highscore::~Highscore(){
}
