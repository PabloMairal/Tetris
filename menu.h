#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

int Menu(sf::RenderWindow& window);
int menuJugadores(sf::RenderWindow& window, sf::Text& currentPlayer);
int menuHighscore(sf::RenderWindow& window);
int cargarJugador(sf::RenderWindow& window);
int seleccionarJugador(sf::RenderWindow& window, sf::Text& currentPlayer, sf::Sound& sfxSeleccion);
int manejarTetris(sf::RenderWindow& window, sf::Text& currentPlayer);

int Menu(sf::RenderWindow& window){
    sf::Texture textureMenu;
    sf::Sprite spriteMenu;
    sf::Music inicioMenu;
    sf::SoundBuffer seleccion;
    sf::Sound sfxSeleccion;
    sf::Font font;
    sf::Text currentPlayer;
    sf::Text Player;
    sf::Text Play;
    sf::Text HighScore;
    sf::Text Exit;
    sf::Text name;

    Jugador jugador;
    ArchivoJugadores arcJugadores("jugadorActual.dat");

    ///inicializa el menu
    textureMenu.loadFromFile("resources/sprite/tetris.png", sf::IntRect(40, 20, 1071, 859));
    spriteMenu.scale(0.6, 0.9);
    spriteMenu.setTexture(textureMenu);
    window.draw(spriteMenu);

    ///carga la fuente
    font.loadFromFile("resources/font/ARCADECLASSIC.TTF");
    currentPlayer.setFont(font);
    Player.setFont(font);
    Play.setFont(font);
    HighScore.setFont(font);
    Exit.setFont(font);

    ///Muestra el jugador actual
    jugador = arcJugadores.leerRegistro(0);
    std::string nombre = jugador.getNombre();
    currentPlayer.setPosition(30,10);
    currentPlayer.setCharacterSize(50);
    currentPlayer.setString(nombre);
    window.draw(currentPlayer);

    ///escribe y posiciona las opciones del menu
    Play.setPosition((window.getSize().x/2)-55,(window.getSize().y/2));
    Play.setCharacterSize(50);
    Play.setString("PLAY");
    Play.setOutlineThickness(5);
    window.draw(Play);

    Player.setPosition((window.getSize().x/2)-85,(window.getSize().y/2)+50);
    Player.setCharacterSize(50);
    Player.setString("PLAYER");
    Player.setOutlineThickness(5);
    window.draw(Player);

    HighScore.setPosition((window.getSize().x/2)-105,(window.getSize().y/2)+105);
    HighScore.setCharacterSize(40);
    HighScore.setString("HIGH SCORE");
    HighScore.setOutlineThickness(5);
    window.draw(HighScore);

    Exit.setPosition((window.getSize().x/2)-55,(window.getSize().y/2)+150);
    Exit.setCharacterSize(50);
    Exit.setString("EXIT");
    Exit.setOutlineThickness(5);
    window.draw(Exit);

    ///inicializa el sonido del menu
    inicioMenu.openFromFile("resources/sounds/mainMenu.ogg");
    inicioMenu.setVolume(50);
    inicioMenu.play();
    inicioMenu.setLoop(true);
    seleccion.loadFromFile("resources/sounds/rotate.ogg");
    sfxSeleccion.setBuffer(seleccion);

    window.display();

    sf::Event event;
    sf::Vector2i posicionMouse;

    while(window.waitEvent(event)){
        window.clear(sf::Color::Black);
        if(event.type==sf::Event::Closed){
            window.close();
            return 0;
        }

        posicionMouse = sf::Mouse::getPosition(window);
        if(event.type == sf::Event::MouseMoved){///logica de resaltar la opcion por la que esta encima el mouse, tipo hover
            if(Play.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                Play.setFillColor(sf::Color::Red);
                Player.setFillColor(sf::Color::White);
                HighScore.setFillColor(sf::Color::White);
                Exit.setFillColor(sf::Color::White);
            }
            else if(Player.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                Play.setFillColor(sf::Color::White);
                Player.setFillColor(sf::Color::Red);
                HighScore.setFillColor(sf::Color::White);
                Exit.setFillColor(sf::Color::White);
            }
            else if(HighScore.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                Play.setFillColor(sf::Color::White);
                Player.setFillColor(sf::Color::White);
                HighScore.setFillColor(sf::Color::Red);
                Exit.setFillColor(sf::Color::White);
            }
            else if(Exit.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                Play.setFillColor(sf::Color::White);
                Player.setFillColor(sf::Color::White);
                HighScore.setFillColor(sf::Color::White);
                Exit.setFillColor(sf::Color::Red);
            }
            else{
                Play.setFillColor(sf::Color::White);
                Player.setFillColor(sf::Color::White);
                HighScore.setFillColor(sf::Color::White);
                Exit.setFillColor(sf::Color::White);
            }
        }
        if(event.type==sf::Event::MouseButtonReleased){
            if(event.mouseButton.button==sf::Mouse::Left){
                if(Play.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                    sfxSeleccion.play();
                    inicioMenu.stop();
                    while(true){
                        int opc=manejarTetris(window, currentPlayer);
                        if(opc==0){
                            return 0;
                        }
                        else if(opc==1){
                            inicioMenu.play();
                            break;
                        }
                    }
                }
                else if(Player.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                    sfxSeleccion.play();
                    int opc=menuJugadores(window, currentPlayer);
                    if(opc==0){
                        return 0;
                    }
                    else if(opc==1){
                        Play.setFillColor(sf::Color::White);
                        Player.setFillColor(sf::Color::White);
                        HighScore.setFillColor(sf::Color::White);
                        Exit.setFillColor(sf::Color::White);
                        window.draw(spriteMenu);
                        window.draw(currentPlayer);
                        window.draw(Play);
                        window.draw(Player);
                        window.draw(HighScore);
                        window.draw(Exit);
                        window.display();
                        continue;
                    }
                    else if(opc==2){
                        return 0;
                    }
                }
                else if(HighScore.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                    sfxSeleccion.play();
                    menuHighscore(window);
                }
                else if(Exit.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                    sfxSeleccion.play();
                    window.close();
                    return 0;
                }
            }
        }
        window.draw(spriteMenu);
        window.draw(currentPlayer);
        window.draw(Play);
        window.draw(Player);
        window.draw(HighScore);
        window.draw(Exit);
        window.display();
    }
    return 0;
}

int menuJugadores(sf::RenderWindow& window, sf::Text& currentPlayer){
    sf::Text newPlayer;
    sf::Text selectPlayer;
    sf::Text menu;
    sf::Text text;
    sf::Font font;
    font.loadFromFile("resources/font/ARCADECLASSIC.TTF");
    newPlayer.setFont(font);
    selectPlayer.setFont(font);
    menu.setFont(font);
    text.setFont(font);

    window.clear(sf::Color::Black);

    newPlayer.setPosition((window.getSize().x/2)-140, window.getSize().y/2-150);
    newPlayer.setCharacterSize(60);
    newPlayer.setString("NEW PLAYER");
    newPlayer.setOutlineThickness(5);
    window.draw(newPlayer);

    selectPlayer.setPosition((window.getSize().x/2)-190, window.getSize().y/2-100);
    selectPlayer.setCharacterSize(60);
    selectPlayer.setString("SELECT PLAYER");
    selectPlayer.setOutlineThickness(5);
    window.draw(selectPlayer);

    menu.setPosition((window.getSize().x/2)-60, window.getSize().y/2-50);
    menu.setCharacterSize(60);
    menu.setString("MENU");
    menu.setOutlineThickness(5);
    window.draw(menu);
    window.display();

    sf::SoundBuffer seleccion;
    sf::Sound sfxSeleccion;
    seleccion.loadFromFile("resources/sounds/rotate.ogg");
    sfxSeleccion.setBuffer(seleccion);
    sf::Event event;
    sf::Vector2i posicionMouse;

    while(window.waitEvent(event)){
        window.clear(sf::Color::Black);
        if(event.type == sf::Event::Closed){
            window.close();
            return 2;
        }

        posicionMouse = sf::Mouse::getPosition(window);

        if(event.type == sf::Event::MouseMoved){

            if(menu.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                newPlayer.setFillColor(sf::Color::White);
                selectPlayer.setFillColor(sf::Color::White);
                menu.setFillColor(sf::Color::Red);
            }
            else if(newPlayer.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                newPlayer.setFillColor(sf::Color::Red);
                selectPlayer.setFillColor(sf::Color::White);
                menu.setFillColor(sf::Color::White);
            }
            else if(selectPlayer.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                menu.setFillColor(sf::Color::White);
                newPlayer.setFillColor(sf::Color::White);
                selectPlayer.setFillColor(sf::Color::Red);
            }
            else{
                menu.setFillColor(sf::Color::White);
                newPlayer.setFillColor(sf::Color::White);
                menu.setFillColor(sf::Color::White);
            }
        }
        if(event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left){
                if(menu.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                    sfxSeleccion.play();
                    return 1;
                }
                else if(newPlayer.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                    sfxSeleccion.play();
                    if(cargarJugador(window)){
                        window.clear(sf::Color::Black);
                        menu.setFillColor(sf::Color::White);
                        newPlayer.setFillColor(sf::Color::White);
                        menu.setFillColor(sf::Color::White);
                        continue;
                    }
                    else{
                        text.setPosition((window.getSize().x/2)-300, window.getSize().y/2-150);
                        text.setCharacterSize(60);
                        text.setOutlineThickness(5);
                        text.setString("PLAYER ALREADY EXIST");
                        window.draw(text);
                        text.setPosition((window.getSize().x/2)-180, window.getSize().y/2+50);
                        text.setCharacterSize(60);
                        text.setOutlineThickness(5);
                        text.setString("PRESS ANY KEY");
                        window.draw(text);
                        window.display();
                        sf::Event event;
                        while(window.waitEvent(event)){
                            if(event.type == sf::Event::Closed){
                                window.close();
                                return 2;
                            }
                            if(event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed){
                                break;
                            }
                        }
                        continue;
                    }
                }
                else if(selectPlayer.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                    sfxSeleccion.play();
                    seleccionarJugador(window, currentPlayer, sfxSeleccion);
                    window.clear();
                    continue;
                }
            }
        }
        window.draw(newPlayer);
        window.draw(selectPlayer);
        window.draw(menu);
        window.display();
    }
    return 2;
}

int menuHighscore(sf::RenderWindow& window){
    ArchivoHighscore arcHighscore;

    sf::Font font;
    font.loadFromFile("resources/font/ARCADECLASSIC.TTF");
    sf::Text* jugadores;
    sf::Text* puntajes;
    int cantHighscore=arcHighscore.contarRegistros();
    if(cantHighscore>0){
        jugadores = new sf::Text[cantHighscore];
        if(jugadores==nullptr){
            exit(1);
        }

        puntajes = new sf::Text[cantHighscore];
        if(puntajes==nullptr){exit(1);}
    }
    else{
        return 1;
    }

    float espacioEntreBotones = 50.0f;
    float posicionXInicial = (window.getSize().x / 2)-200;
    float posicionYInicial = 10;


    for(int i=0; i<cantHighscore; i++){
        sf::Text jugador;
        std::string nombre=arcHighscore.leerRegistro(i).getNombre();

        jugador.setFont(font);
        jugador.setString(std::to_string(i + 1) + " " + nombre);
        jugador.setPosition(posicionXInicial, posicionYInicial + i * espacioEntreBotones);
        jugador.setCharacterSize(50);
        jugador.setOutlineThickness(5);

        sf::Text points;
        std::string puntaje=std::to_string(arcHighscore.leerRegistro(i).getPuntaje());
        points.setFont(font);
        points.setString(puntaje);
        points.setPosition(posicionXInicial+220, posicionYInicial + i * espacioEntreBotones);
        points.setCharacterSize(50);
        points.setOutlineThickness(5);

        jugadores[i]=jugador;
        puntajes[i]=points;
    }
    window.clear(sf::Color::Black);
    for(int i=0; i<cantHighscore; i++){
        window.draw(jugadores[i]);
        window.draw(puntajes[i]);
    }
    window.display();
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
                delete[] jugadores;
                delete[] puntajes;
                return 0;
            }
            if(event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonReleased){
                delete[] jugadores;
                delete[] puntajes;
                return 1;
            }
        }

    }
    delete[] jugadores;
    delete[] puntajes;
    return 1;
}
int cargarJugador(sf::RenderWindow& window){
    sf::Font font;
    sf::Text user;
    sf::Text name;
    sf::RectangleShape rectangulo(sf::Vector2f(200.f,40.f));

    ///dibuja el rectangulo para cargar

    rectangulo.setFillColor(sf::Color(0, 0, 0, 225));
    rectangulo.setOutlineThickness(2.0f);
    rectangulo.setOutlineColor(sf::Color::White);
    rectangulo.setPosition((window.getSize().x/2)-100,(window.getSize().y/2));

    font.loadFromFile("resources/font/ARCADECLASSIC.TTF");
    user.setFont(font);
    user.setPosition((window.getSize().x/2)-55,(window.getSize().y/2)-70);
    user.setCharacterSize(50);
    user.setString("USER");
    user.setOutlineThickness(5);
    user.setFillColor(sf::Color::White);

    ///carga el nombre

    name.setFont(font);
    name.setPosition((window.getSize().x/2)-95,(window.getSize().y/2));
    name.setCharacterSize(30);

    sf::Event event;
    sf::String nameAux;
    Jugador jugador;
    ArchivoJugadores arc;

    window.clear(sf::Color::Black);
    window.draw(user);
    window.draw(rectangulo);
    window.draw(name);
    window.display();

    while(window.waitEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
            return 0;
        }
        if(event.type == sf::Event::TextEntered){
            if(event.text.unicode<122 && event.text.unicode!=13){
                if(event.text.unicode==8 && nameAux.getSize()>0){ /// 8 => backspace
                    nameAux.erase(nameAux.getSize()-1, 1); /// para borrar el desde el ultimo caracter
                }
                else if(nameAux.getSize()<5){
                    nameAux += static_cast<char>(event.text.unicode);/// para cargar caracter por caracter
                }
                name.setString(nameAux);
            }
            if(event.text.unicode==13){ /// 13 => enter
                std::string aux=nameAux.toAnsiString();
                for(char &c : aux){
                    c = std::toupper(c);
                }
                const char* nombre=aux.c_str();
                if(guardarNombre(nombre)){
                    return 1;
                }
                else{
                    return 0;
                }
            }
        }
        window.clear(sf::Color::Black);
        window.draw(user);
        window.draw(rectangulo);
        window.draw(name);
        window.display();
    }
    return 0;
}

int seleccionarJugador(sf::RenderWindow& window, sf::Text& currentPlayer, sf::Sound& sfxSeleccion){
    Jugador jugador;
    ArchivoJugadores arcJugadores;
    ArchivoJugadores arcJugadorActual("jugadorActual.dat");
    int cantJugadores = arcJugadores.contarRegistros();

    sf::Font font;
    font.loadFromFile("resources/font/ARCADECLASSIC.TTF");
    sf::Text* jugadores;

    jugadores = new sf::Text[cantJugadores];
    float espacioEntreBotones = 50.0f;

    for(int i=0; i<cantJugadores; i++){
        sf::Text boton;
        std::string nombre=arcJugadores.leerRegistro(i).getNombre();
        boton.setFont(font);
        boton.setString("Jugador " + std::to_string(i + 1) + " " + nombre);
        boton.setPosition(120, 10 + i * espacioEntreBotones);
        boton.setCharacterSize(50);
        boton.setOutlineThickness(5);
        window.draw(boton);
        window.display();
        jugadores[i]=boton;
    }

    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            sf::Vector2i posicionMouse = sf::Mouse::getPosition(window);
            if(event.type == sf::Event::MouseMoved){
                for(int i=0; i<cantJugadores; i++){
                    jugadores[i].setFillColor(sf::Color::White);
                    if(jugadores[i].getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                        jugadores[i].setFillColor(sf::Color::Red);
                    }
                }
            }

            if(event.type == sf::Event::MouseButtonPressed){
                sfxSeleccion.play();
                for(int i=0; i<cantJugadores; i++) {
                    if(jugadores[i].getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)){
                        jugador=arcJugadores.leerRegistro(i);
                        std::string nombre=jugador.getNombre();
                        currentPlayer.setString(nombre);
                        arcJugadorActual.grabarJugadorActual(jugador);
                        window.clear();
                        delete[] jugadores;
                        return 0;
                    }
                }
            }
        }

        window.clear();
        for(int i=0; i<cantJugadores; i++){
            window.draw(jugadores[i]);
        }
        window.display();
    }

    return -1; // En caso de que la ventana se cierre sin seleccionar un jugador
}


int manejarTetris(sf::RenderWindow& window, sf::Text& currentPlayer){
    Highscore* highscore;
    ArchivoHighscore arcHighscore;
    int cantHighscore = arcHighscore.contarRegistros();
    if(cantHighscore>0){
        highscore = new Highscore[cantHighscore+1];
        for(int i=0; i<cantHighscore; i++){
            highscore[i]=arcHighscore.leerRegistro(i);
        }
    }
    else{
        cantHighscore=1;
        highscore = new Highscore[cantHighscore];
    }

    while(true){
        int opc = tetris(window, highscore, cantHighscore, currentPlayer);
        if(opc==1){
            delete[] highscore;
            return 1;//vuelve al menu
        }
        else if(opc==2){//reinicia el juego
            continue;
        }
        else{
            return 0; //cierra el juego, se puede hacer desde acá o desde donde se llama a la función manejarTetris
        }
    }
    delete[] highscore;
    return 1; //devuelve 1 cuando vuelve al menu, no debería de llegar acá igualmente
}
#endif // MENU_H_INCLUDED
