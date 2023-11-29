#pragma once
#include <iostream>
#include <cstring>
#include "Highscore.h"
class ArchivoHighscore{
    private:
        char nombre[13];
    public:
        ArchivoHighscore(const char* nombre="Highscore.dat");
        Highscore leerRegistro(int pos);
        int contarRegistros();
        bool grabarRegistro(Highscore reg);
        void vaciarArchivo();
        virtual ~ArchivoHighscore();
};
