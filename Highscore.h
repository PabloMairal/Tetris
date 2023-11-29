#pragma once

class Highscore{
    private:
        char nombre[40];
        int puntaje;
    public:
        Highscore();
        void Mostrar();
        const char* getNombre();
        void setNombre(const char* nombre);
        int getPuntaje();
        void setPuntaje(int puntaje);
        virtual ~Highscore();

};

