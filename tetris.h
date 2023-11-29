#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

int menuHighscore(sf::RenderWindow& window);
int checkHighscore(sf::RenderWindow& window, int puntaje, Highscore* highscore, int cantHighscore, sf::Text currentPlayer, sf::Font& font){
    ArchivoHighscore arcHighscore;
    sf::Text text;
    text.setFont(font);
    sf::Event event;
    if(cantHighscore>1){
        std::string s = currentPlayer.getString();
        const char* nombre = s.c_str();
        std::string aux = std::to_string(puntaje);
        highscore[cantHighscore].setNombre(nombre);
        highscore[cantHighscore].setPuntaje(puntaje);
        for(int i=0; i<cantHighscore; i++){
            if(puntaje>highscore[i].getPuntaje() || cantHighscore<10){
                arcHighscore.vaciarArchivo();
                text.setFont(font);
                text.setCharacterSize(80);
                text.setFillColor(sf::Color::Red);
                text.setOutlineThickness(10);
                text.setPosition(10, 10);
                text.setString("NEW HIGHSCORE!");
                window.draw(text);

                text.setFont(font);
                text.setCharacterSize(80);
                text.setFillColor(sf::Color::White);
                text.setOutlineThickness(10);
                text.setPosition(250, 80);
                text.setString(aux);
                window.draw(text);

                window.display();


                for(int i=0; i<cantHighscore; i++){
                    for(int j=i+1; j<cantHighscore+1; j++){
                        if(highscore[i].getPuntaje()<highscore[j].getPuntaje()){
                            std::swap(highscore[i], highscore[j]);
                        }
                    }
                }
                if(cantHighscore<10){
                    for(int i=0; i<cantHighscore+1; i++){
                        arcHighscore.grabarRegistro(highscore[i]);
                    }
                }
                else{
                    for(int i=0; i<cantHighscore; i++){
                        arcHighscore.grabarRegistro(highscore[i]);
                    }
                }

                while(window.waitEvent(event)){
                    if(event.type == sf::Event::Closed){
                        window.close();
                        return 3;
                    }
                    if(event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed){
                        menuHighscore(window);
                        return 1;
                    }
                }
            }
        }
    }
    else{
        std::string s = currentPlayer.getString();
        const char* nombre = s.c_str();
        text.setFont(font);
        text.setCharacterSize(100);
        text.setOutlineThickness(10);
        text.setPosition((window.getSize().x/2)-220, window.getSize().y/2-300);
        text.setString("NEW HIGHSCORE!");
        window.draw(text);

        text.setFont(font);
        text.setCharacterSize(80);
        text.setOutlineThickness(10);
        text.setPosition((window.getSize().x/2)-220, window.getSize().y/2-200);
        std::string aux = std::to_string(puntaje);
        text.setString(aux);
        window.draw(text);
        window.display();

        highscore[0].setNombre(nombre);
        highscore[0].setPuntaje(puntaje);
        arcHighscore.grabarRegistro(highscore[0]);
        while(window.waitEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
                return 3;
            }
            if(event.type == sf::Event::KeyPressed){
                return 1;
            }
        }
    }
    return 0;
}

int gameOverScreen(sf::RenderWindow& window, int puntaje, Highscore* highscore, int cantHighscore, sf::Text& currentPlayer, sf::SoundBuffer& gameOver, sf::Sound& sfxGameOver, sf::Font& font, sf::SoundBuffer& rotate, sf::Sound& sfxrotate){
    sfxGameOver.play();
    sf::Text text;
    sf::Text menu;
    sf::Text restart;
    sf::Text exit;
    menu.setFont(font);
    restart.setFont(font);
    exit.setFont(font);
    text.setFont(font);
    int opc=checkHighscore(window, puntaje, highscore, cantHighscore, currentPlayer, font);
    if(opc==3){
        return 4;
    }
    else if(opc==1){
        return 1;
    }
    else{}
    text.setPosition((window.getSize().x/2)-220, window.getSize().y/2-300);
    text.setCharacterSize(100);
    text.setString("GAME OVER");
    text.setOutlineThickness(10);
    window.draw(text);

    menu.setPosition((window.getSize().x/2)-70, window.getSize().y/2-150);
    menu.setCharacterSize(60);
    menu.setString("MENU");
    menu.setOutlineThickness(5);
    window.draw(menu);

    restart.setPosition((window.getSize().x/2)-120, window.getSize().y/2-100);
    restart.setCharacterSize(60);
    restart.setString("RESTART");
    restart.setOutlineThickness(5);
    window.draw(restart);

    exit.setPosition((window.getSize().x/2)-70, window.getSize().y/2-50);
    exit.setCharacterSize(60);
    exit.setString("EXIT");
    exit.setOutlineThickness(5);
    window.draw(exit);

    window.display();

    sf::Event event;
    sf::Vector2i posicionMouse;

    while(window.waitEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
            return 4;
        }

        posicionMouse = sf::Mouse::getPosition(window);

        if(event.type == sf::Event::MouseMoved){

            if(menu.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                menu.setFillColor(sf::Color::Red);
                restart.setFillColor(sf::Color::White);
                exit.setFillColor(sf::Color::White);
            }
            else if(restart.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                menu.setFillColor(sf::Color::White);
                restart.setFillColor(sf::Color::Red);
                exit.setFillColor(sf::Color::White);
            }
            else if(exit.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                menu.setFillColor(sf::Color::White);
                restart.setFillColor(sf::Color::White);
                exit.setFillColor(sf::Color::Red);
            }
            else{
                menu.setFillColor(sf::Color::White);
                restart.setFillColor(sf::Color::White);
                exit.setFillColor(sf::Color::White);
            }
            window.draw(text);
            window.draw(menu);
            window.draw(restart);
            window.draw(exit);
            window.display();
        }
        if(event.type == sf::Event::MouseButtonReleased){
            if(event.mouseButton.button == sf::Mouse::Left){
                if(menu.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                    sfxrotate.play();
                    window.clear();
                    return 1;
                }
                else if(restart.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                    sfxrotate.play();
                    return 2;
                }
                else if(exit.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                    sfxrotate.play();
                    window.close();
                    return 0;
                }
            }
        }
    }
    return 0;
}
int tetris(sf::RenderWindow& window, Highscore* highscore, int cantHighscore, sf::Text& currentPlayer){

    sf::Texture texturaPieza;
    sf::Sprite spritePieza;
    sf::Texture texturaTablero;
    sf::Sprite spriteTablero;
    sf::Texture texturaGhost;
    sf::Sprite spriteGhost;

    sf::Music music;
    music.openFromFile("resources/sounds/Tetris99music.ogg");
    music.setVolume(50);
    music.play();
    music.setLoop(true);

    sf::SoundBuffer singleClear;
    sf::Sound sfxSingleClear;
    sf::SoundBuffer doubleClear;
    sf::Sound sfxDoubleClear;
    sf::SoundBuffer tripleClear;
    sf::Sound sfxTripleClear;
    sf::SoundBuffer tetrisClear;
    sf::Sound sfxTetrisClear;
    sf::SoundBuffer rotate;
    sf::Sound sfxRotate;
    sf::SoundBuffer move;
    sf::Sound sfxMove;
    sf::SoundBuffer colide;
    sf::Sound sfxColide;
    sf::SoundBuffer landing;
    sf::Sound sfxLanding;
    sf::SoundBuffer hardDrop;
    sf::Sound sfxHardDrop;
    sf::SoundBuffer gameOver;
    sf::Sound sfxGameOver;

    sf::Font font;
    sf::Text text;

    for(int i=0;i<altura;i++){
        for(int j=0;j<ancho;j++){
            tablero[i][j]=0;
        }
    }
    int colorNext=1;
    int color=inicializarJuego(window, texturaPieza, spritePieza, texturaTablero, spriteTablero, texturaGhost, spriteGhost, singleClear, sfxSingleClear, doubleClear, sfxDoubleClear, tripleClear, sfxTripleClear, tetrisClear, sfxTetrisClear, move, sfxMove, rotate, sfxRotate, colide, sfxColide, landing, sfxLanding, hardDrop, sfxHardDrop, gameOver, sfxGameOver, font, text, colorNext);
    int colorHold=0;
    int puntaje=0;
    int direccionX=0;
    int cuentaLineas=0;
    int nivel=1;
    float totalPausa=0;
    float timer=0;
    float dificultad=0.9;
    float delay=dificultad;
    float temporizador;
    bool rotar=false;
    bool hardDropState=false;
    bool pausa=false;
    bool mute=false;
    bool holded=false;
    bool firstHold=false;
    bool jugando=true;

    sf::Clock clock;
    sf::Clock tempClock;

    while(jugando){
        float time=clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        if(pausa==false){
            temporizador=tempClock.getElapsedTime().asSeconds();
            temporizador-=totalPausa;

            actualizarMovimiento(direccionX, rotar, timer, delay, hardDropState, holded, firstHold, color, colorHold, colorNext, sfxRotate, sfxMove, sfxColide, sfxLanding, sfxHardDrop);
            lineaCompleta(sfxSingleClear, sfxDoubleClear, sfxTripleClear, sfxTetrisClear, puntaje, cuentaLineas);
            actualizarDificultad(dificultad, cuentaLineas, nivel);

            direccionX=0;//lo dejamos en 0 para que no siga avanzando infinitamente
            rotar=0;//lo mismo pero con la rotacion
            delay=dificultad; //reinicia el delay para que vuelva a la velocidad normal

            if(verificarFinalJuego()==false){
                jugando=false;
                break;
            }

            renderizar(window, spritePieza, spriteTablero, texturaGhost, spriteGhost, color, colorHold, firstHold, colorNext, text, puntaje, temporizador, nivel, cuentaLineas);
        }
        else{
            totalPausa=tempClock.getElapsedTime().asSeconds()-temporizador;
        }

        if(manejarEventos(window, direccionX, rotar, delay, hardDropState, holded, pausa, mute, music)==false){
            return 0;
        }
    }

    music.setVolume(10);
    int opc=gameOverScreen(window, puntaje, highscore, cantHighscore, currentPlayer, gameOver, sfxGameOver, font, rotate, sfxRotate);

    return opc;
}

#endif // TETRIS_H_INCLUDED
