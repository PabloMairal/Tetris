#pragma once

class Jugador{
    private:
        int id;
        char nombre[40];
    public:
        void Mostrar();
        int getID();
        void setID(int id);
        const char* getNombre();
        void setNombre(const char* nombre);
        virtual ~Jugador();
};

