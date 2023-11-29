#pragma once
#include "jugador.h"
#include <cstring>
#include <iostream>
class ArchivoJugadores{
    private:
        char nombre[13];
    public:
        ArchivoJugadores(const char* nombre="jugadores.dat");
        Jugador leerRegistro(int pos);
        int contarRegistros();
        bool grabarRegistro(Jugador reg);
        int getPos(int id);
        int buscarUltimoID();
        bool existeJugador(Jugador jugador);
        bool grabarJugadorActual(Jugador jugador);
        virtual ~ArchivoJugadores();

};

