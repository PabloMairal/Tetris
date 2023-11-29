#include "ArchivoJugadores.h"

ArchivoJugadores::ArchivoJugadores(const char *nombre){
        strcpy(this->nombre, nombre);
}
Jugador ArchivoJugadores::leerRegistro(int pos){
    Jugador reg;
    FILE *pJugador;
    pJugador=fopen(nombre, "rb");
    if(pJugador==NULL) return reg;
    fseek(pJugador, sizeof reg*pos,0);
    fread(&reg, sizeof reg,1, pJugador);
    fclose(pJugador);
    return reg;
}
int ArchivoJugadores::contarRegistros(){
    FILE *pJugador;
    pJugador=fopen(nombre, "rb");
    if(pJugador==NULL) return -1;
    fseek(pJugador, 0,2);
    int tam=ftell(pJugador);
    fclose(pJugador);
    return tam/sizeof(Jugador);
}
bool ArchivoJugadores::grabarRegistro(Jugador reg){
    FILE *pJugador;
    pJugador=fopen(nombre, "ab");
    if(pJugador==NULL) return false;
    if(existeJugador(reg)==false){
        fwrite(&reg, sizeof reg, 1, pJugador);
        fclose(pJugador);
        return true;
    }
    fclose(pJugador);
    return false;
}

int ArchivoJugadores::getPos(int id){
    FILE *pJugador;
    Jugador jugador;
    pJugador=fopen(nombre, "rb");
    int pos;
    if(pJugador==NULL){
        return -2;
    }

    while(fread(&jugador, sizeof(Jugador),1 , pJugador)){
        if(jugador.getID()==id){
            pos=(ftell(pJugador)/sizeof(Jugador))-1;
            fclose(pJugador);
            return pos;
        }
    }

    fclose(pJugador);
    return -1;
}
int ArchivoJugadores::buscarUltimoID(){
    Jugador jugador;
    FILE *pJugador;
    pJugador=fopen(nombre, "rb");
    int id=1;
    if(pJugador==NULL){
        return id;
    }
    while(fread(&jugador, sizeof(Jugador), 1, pJugador)){
        if(jugador.getID()>id){
            id=jugador.getID();
        }
    }
    fclose(pJugador);
    return id+1;
}

bool ArchivoJugadores::existeJugador(Jugador jugador){
    FILE *pJugador;
    Jugador aux;
    pJugador=fopen(nombre, "rb");
    if(pJugador==NULL) return false;
    while(fread(&aux, sizeof(Jugador), 1, pJugador)){
        if(strcmp(jugador.getNombre(), aux.getNombre())==0){
            return true;
        }
    }
    return false;
}

bool ArchivoJugadores::grabarJugadorActual(Jugador jugador){
    FILE *pJugador;
    pJugador=fopen(nombre, "wb");
    if(pJugador==NULL) return false;
    if(existeJugador(jugador)==false){
        fwrite(&jugador, sizeof(Jugador), 1, pJugador);
        fclose(pJugador);
        return true;
    }
    fclose(pJugador);
    return false;
}

ArchivoJugadores::~ArchivoJugadores(){

}
