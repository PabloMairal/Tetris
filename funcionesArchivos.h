#ifndef FUNCIONESARCHIVOS_H_INCLUDED
#define FUNCIONESARCHIVOS_H_INCLUDED

bool guardarNombre(const char* nombre){
    Jugador jugador;
    ArchivoJugadores arc;
    int id=arc.buscarUltimoID();
    jugador.setNombre(nombre);
    jugador.setID(id);
    if(arc.grabarRegistro(jugador)){
        return true;
    }
    else{return false;};
}

#endif // FUNCIONESARCHIVOS_H_INCLUDED
