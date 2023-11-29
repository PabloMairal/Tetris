#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstring>
#include <random>
#include <cmath>
#include "Pieza.h"
#include "jugador.h"
#include "ArchivoJugadores.h"
#include "Highscore.h"
#include "ArchivoHighscore.h"
#include "funcionesArchivos.h"
#include "funciones.h"
#include "tetris.h"
#include "menu.h"


int main(){
    sf::RenderWindow window;
    window.create(sf::VideoMode(600, 720), "Tetris");
    Menu(window);

    return 0;
}
