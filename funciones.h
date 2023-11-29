#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
//variables globales
const int altura=23;
const int ancho=10;

int tablero[altura][ancho]={0};

Pieza tetromino[4], aux[4], ghost[4], hold[4], nextTetromino[4];

enum tipoTetromino{
    Z=0,
    L=1,
    O=2,
    S=3,
    I=4,
    J=5,
    T=6
};

int figuras[7][4]{      //cada numero se usa para hacer /2(para X) y %2(para Y), esto nos devuelve la posicion en una cuadricula de 4x2 de las piezas
    {2, 4, 5, 7}, //Z   //por ejemplo para la pieza Z quedaria X(0,0,1,1) Y(1,2,2,3), o como coordenadas:(0,1) (0,2) (1,2) (1,3) entonces:
    {3, 5, 7, 6}, //L                                0 1 2 3
    {2, 4, 3, 5}, //O                              0   Q Q
    {3, 5, 4, 6}, //S                              1     Q Q
    {1, 3, 5, 7}, //I
    {2, 5, 3, 7}, //J
    {3, 5, 4, 7} //T
};

std::random_device rd; //semilla aleatoria
std::mt19937 gen(rd()); //generador de numeros aleatorios
std::uniform_int_distribution<int> dist(0, 6); //acota los numeros para que se generen de 0 a 6

//declaracion funciones
int tetris(sf::RenderWindow& window, Highscore* highscore, int cantHighscore, sf::Text& currentPlayer);
int nuevaPieza(Pieza* tetromino);
void holdPieza(bool& holded, bool& firstHold, int& color, int& colorHold);
int inicializarJuego(sf::RenderWindow& window,sf::Texture& texturaPieza, sf::Sprite& spritePieza, sf::Texture& texturaTablero, sf::Sprite& spriteTablero, sf::Texture& texturaGhost, sf::Sprite& spriteGhost, sf::SoundBuffer& singleClear, sf::Sound& sfxSingleClear, sf::SoundBuffer& doubleClear, sf::Sound& sfxDoubleClear, sf::SoundBuffer& tripleClear, sf::Sound& sfxTripleClear, sf::SoundBuffer& tetrisClear, sf::Sound& sfxTetrisClear, sf::SoundBuffer& move, sf::Sound& sfxMove, sf::SoundBuffer& rotate, sf::Sound& sfxRotate, sf::SoundBuffer& colide, sf::Sound& sfxColide, sf::SoundBuffer& landing, sf::Sound& sfxLanding, sf::SoundBuffer& hardDrop, sf::Sound& sfxHardDrop,  sf::SoundBuffer& gameOver, sf::Sound& sfxGameOver, sf::Font& font, sf::Text& text, int& color);
bool manejarEventos(sf::RenderWindow& window, int& direccionX, bool& rotar, float& delay, bool& hardDropState, bool& holded, bool& pausa, bool& mute, sf::Music& music);
bool limite(Pieza* tetromino);
void actualizarMovimiento(int& direccionX, bool& rotar, float& timer, float& delay, bool& hardDropState, bool& holded, bool& firstHold, int& color, int& colorHold, sf::Sound& sfxRotate, sf::Sound& sfxMove, sf::Sound& sfxColide, sf::Sound& sfxLanding, sf::Sound& sfxHardDrop);
void lineaCompleta(sf::Sound& sfxSingleClear, sf::Sound& sfxDoubleClear, sf::Sound& sfxTripleClear, sf::Sound& sfxTetrisClear, int& puntaje, int& cuentaLineas);
void renderizar(sf::RenderWindow& window, sf::Sprite& spritePieza, sf::Sprite& spriteTablero, sf::Texture& texturaGhost, sf::Sprite& spriteGhost, int color, int colorHold, bool firstHold, sf::Text& text, int& puntaje, float temporizador);
bool verificarFinalJuego();
int gameOverScreen(sf::RenderWindow& window, sf::SoundBuffer& gameOver, sf::Sound& sfxGameOver, sf::Font& font);

int nuevaPieza(Pieza* tetromino){
    int nTetromino=dist(gen);
    int color=nTetromino;
    if(color!=tipoTetromino::I){
        for(int i=0; i<4; i++) {
            tetromino[i].setX((figuras[nTetromino][i]/2)+3);
            tetromino[i].setY(figuras[nTetromino][i]%2);
        }
    }
    else{
        for(int i=0; i<4; i++){
            tetromino[i].setX((figuras[nTetromino][i]/2)+3);
            tetromino[i].setY(figuras[nTetromino][i]%2-1);
        }
    }

    return color;
}

void holdPieza(bool& holded, bool& firstHold, int& color, int& colorHold, int& colorNext){
    if(holded && firstHold){
        for(int i=0; i<4; i++){
            std::swap(hold[i],tetromino[i]);
            hold[i].setX((figuras[color][i]/2)+3);
            hold[i].setY((figuras[color][i]%2));
        }
        std::swap(color, colorHold);
        holded=false;
        firstHold=true;
    }
    else if(holded && firstHold==false){
        for(int i=0; i<4; i++){
            hold[i]=tetromino[i];
            hold[i].setX((figuras[color][i]/2)+3);
            hold[i].setY((figuras[color][i]%2));
        }
        colorHold=color;
        color=colorNext;
        for(int i=0; i<4; i++){
            tetromino[i]=nextTetromino[i];
        }
        colorNext=nuevaPieza(nextTetromino);
        holded=false;
        firstHold=true;
    }
}

int inicializarJuego(sf::RenderWindow& window,sf::Texture& texturaPieza, sf::Sprite& spritePieza, sf::Texture& texturaTablero, sf::Sprite& spriteTablero, sf::Texture& texturaGhost, sf::Sprite& spriteGhost, sf::SoundBuffer& singleClear, sf::Sound& sfxSingleClear, sf::SoundBuffer& doubleClear, sf::Sound& sfxDoubleClear, sf::SoundBuffer& tripleClear, sf::Sound& sfxTripleClear, sf::SoundBuffer& tetrisClear, sf::Sound& sfxTetrisClear, sf::SoundBuffer& move, sf::Sound& sfxMove, sf::SoundBuffer& rotate, sf::Sound& sfxRotate, sf::SoundBuffer& colide, sf::Sound& sfxColide, sf::SoundBuffer& landing, sf::Sound& sfxLanding, sf::SoundBuffer& hardDrop, sf::Sound& sfxHardDrop,  sf::SoundBuffer& gameOver, sf::Sound& sfxGameOver, sf::Font& font, sf::Text& text, int& colorNext){

    //inicializa las texturas
    texturaPieza.loadFromFile("resources/sprite/solidTetris.png");
    texturaTablero.loadFromFile("resources/sprite/board.png");
    texturaGhost.loadFromFile("resources/sprite/ghostTetris.png");
    font.loadFromFile("resources/font/ARCADECLASSIC.TTF");
    spritePieza.setTexture(texturaPieza);
    spriteTablero.setTexture(texturaTablero);
    spriteGhost.setTexture(texturaGhost);
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(40);

    //inicializa sonidos
    singleClear.loadFromFile("resources/sounds/singleClear.ogg");
    sfxSingleClear.setBuffer(singleClear);
    doubleClear.loadFromFile("resources/sounds/doubleClear.wav");
    sfxDoubleClear.setBuffer(doubleClear);
    tripleClear.loadFromFile("resources/sounds/tripleClear.ogg");
    sfxTripleClear.setBuffer(tripleClear);
    tetrisClear.loadFromFile("resources/sounds/tetrisClear.ogg");
    sfxTetrisClear.setBuffer(tetrisClear);
    rotate.loadFromFile("resources/sounds/rotate.ogg");
    sfxRotate.setBuffer(rotate);
    move.loadFromFile("resources/sounds/move.ogg");
    sfxMove.setBuffer(move);
    colide.loadFromFile("resources/sounds/colide.ogg");
    sfxColide.setBuffer(colide);
    landing.loadFromFile("resources/sounds/landing.ogg");
    sfxLanding.setBuffer(landing);
    hardDrop.loadFromFile("resources/sounds/hardDrop.wav");
    sfxHardDrop.setBuffer(hardDrop);
    gameOver.loadFromFile("resources/sounds/gameOver.wav");
    sfxGameOver.setBuffer(gameOver);

    //primer tetromino
    colorNext = nuevaPieza(nextTetromino);//crea el proximo tetromino
    return nuevaPieza(tetromino); //devuelve el color para dibujar el primer tetromino con el color correcto
}

bool manejarEventos(sf::RenderWindow& window, int& direccionX, bool& rotar, float& delay, bool& hardDropState, bool& holded, bool& pausa, bool& mute, sf::Music& music){
    sf::Event event;
    if(pausa){
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                window.close();
                return false;
            }
            else if(event.type==sf::Event::KeyPressed){
                if(event.key.code==sf::Keyboard::P){
                    pausa=false;
                    music.play();
                    return true;
                }
                else if(event.key.code==sf::Keyboard::Escape){
                    return false;
                }
            }
        }
        return true;
    }
    while(window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            window.close();
            return false;
        }
        if(event.type == sf::Event::KeyPressed){
            switch(event.key.code){
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    rotar=true;
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    direccionX=-1;
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    direccionX=1;
                    break;
                case sf::Keyboard::Space:
                    hardDropState=true;
                    break;
                case sf::Keyboard::C:
                    holded=true;
                    break;
                case sf::Keyboard::Escape:
                    return false;
                case sf::Keyboard::M:
                    if(mute){
                        mute=false;
                        music.setVolume(50);
                    }
                    else{
                        mute=true;
                        music.setVolume(0);
                    }
                    break;
                case sf::Keyboard::P:
                        pausa=true;
                        music.pause();
                    break;
                default:
                    break;
            }
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        delay=0.03;
    }
    return true;
}

bool limite(Pieza* tetromino){
    for(int i=0; i<4; i++){
        int x=tetromino[i].getX();
        int y=tetromino[i].getY();
        if(x<0 || x>=ancho || y>=altura){
            return false;
        }
        else if(tablero[y][x]){
            return false;
        }
    }
    return true;
}


void actualizarMovimiento(int& direccionX, bool& rotar, float& timer, float& delay, bool& hardDropState, bool& holded, bool& firstHold, int& color, int& colorHold, int& colorNext, sf::Sound& sfxRotate, sf::Sound& sfxMove, sf::Sound& sfxColide, sf::Sound& sfxLanding, sf::Sound& sfxHardDrop){
    //movimiento <<<< >>>>
    for(int i=0; i<4; i++){
        tetromino[i].setX(tetromino[i].getX()+direccionX);
    }
    if(!limite(tetromino)){
        for(int i=0; i<4; i++){
            tetromino[i].setX(tetromino[i].getX()-direccionX);
        }
        sfxColide.play();
    }

    if(direccionX!=0){
        sfxMove.play();
    }
    holdPieza(holded, firstHold, color, colorHold, colorNext);
    //logica de rotar el tetromino, selecciona como la central la segunda pieza(posicion 1) y reacomoda las coordenadas de cada una
    if(rotar){
        if(color!=tipoTetromino::O){
            Pieza centro=tetromino[1];

            for(int i=0; i<4; i++){
                int x=tetromino[i].getX();
                int y=tetromino[i].getY();
                int nuevaX=centro.getX() - y + centro.getY();
                int nuevaY=centro.getY() + x - centro.getX();
                aux[i].setX(nuevaX);
                aux[i].setY(nuevaY);
            }

            if(limite(aux)){//si la rotacion es valida, asigna los valores al tetromino original
                for(int i=0; i<4; i++) {
                    tetromino[i]=aux[i];
                }
            }
            else if(color==tipoTetromino::I){
                for(int i=0; i<4; i++){//colision pared derecha
                    int x=aux[i].getX();
                    aux[i].setX(x-2);
                }
                if(limite(aux)){
                    for(int i=0; i<4; i++) {
                        tetromino[i]=aux[i];
                    }
                }
                else{
                    for(int i=0; i<4; i++){//colision pared izquierda
                        int x=aux[i].getX();
                        aux[i].setX(x+4);
                    }
                    if(limite(aux)){
                        for(int i=0; i<4; i++) {
                            tetromino[i]=aux[i];
                        }
                    }
                }
            }
            else{
                for(int i=0; i<4; i++){//colision pared derecha
                    int x=aux[i].getX();
                    aux[i].setX(x-1);
                }
                if(limite(aux)){
                    for(int i=0; i<4; i++) {
                        tetromino[i]=aux[i];
                    }
                }
                else{
                    for(int i=0; i<4; i++){//colision pared izquierda
                        int x=aux[i].getX();
                        aux[i].setX(x+2);
                    }
                    if(limite(aux)){
                        for(int i=0; i<4; i++) {
                            tetromino[i]=aux[i];
                        }
                    }
                }

            }
        }
        sfxRotate.play();
    }

    //tetromino ghost
    for(int i=0; i<4; i++){
        ghost[i].setX(tetromino[i].getX());
        ghost[i].setY(tetromino[i].getY());
    }
    while(limite(ghost)){
        for(int i=0; i<4; i++){
            ghost[i].setY(ghost[i].getY()+1);
        }
    }
    for(int i=0;i<4;i++){
        ghost[i].setY(ghost[i].getY()-1);
    }
    //hardDrop
    if(hardDropState){
        for(int i=0; i<4; i++){
            int x=ghost[i].getX();
            int y=ghost[i].getY();
            tablero[y][x]=color+1;
        }
        sfxHardDrop.play();
        sf::sleep(sf::milliseconds(125));
        sfxLanding.play();
        hardDropState=false;
        for(int i=0; i<4; i++){
            tetromino[i]=nextTetromino[i];
        }
        color=colorNext;
        colorNext=nuevaPieza(nextTetromino);
// timer=1; no me acuerdo por qué estaba, lo dejo por las dudas comentado :P
    }
    //el timer que genera la caida de la pieza
    if(timer>delay){
        for(int i=0 ; i<4; i++){//guarda la ultima posicion de la pieza
            aux[i]=tetromino[i];
            tetromino[i].setY(tetromino[i].getY()+1);
        }
        if(!limite(tetromino)){//checkea que no se haya pasado de los limites, si se paso, le asigna al tablero la ultima posicion valida
            for(int i=0; i<4; i++){
                int x=aux[i].getX();
                int y=aux[i].getY();
                tablero[y][x]=color+1;
                sfxLanding.play();
            }
        for(int i=0; i<4; i++){
            tetromino[i]=nextTetromino[i];
        }
        color=colorNext;
        colorNext=nuevaPieza(nextTetromino);
        }
        timer=0;
    }
}

void lineaCompleta(sf::Sound& sfxSingleClear, sf::Sound& sfxDoubleClear, sf::Sound& sfxTripleClear, sf::Sound& sfxTetrisClear, int& puntaje, int& cuentaLineas){
    //checkea si se completo una linea y reacomoda el tablero
    int linea=0;//contador de lineas para el puntaje
    int fila=altura-1;
    for(int i=altura-1; i>0; i--){//revisa filas
        int cuentaPiezas=0;
        for(int j=0; j<ancho; j++){//revisa columnas
            if(tablero[i][j]){
                cuentaPiezas++;
            }
            tablero[fila][j]=tablero[i][j];
        }
        if(cuentaPiezas<ancho){
            fila--;
        }
        else{
            linea++;
            cuentaLineas++;//contador general de lineas
        }
    }

    if(linea==1){
        linea*=100;
        sfxSingleClear.play();
    }
    else if(linea==2){
        linea*=150;
        sfxDoubleClear.play();
    }
    else if(linea==3){
        linea*=200;
        sfxTripleClear.play();
    }
    else if(linea==4){
        linea*=400;
        sfxTetrisClear.play();
    }
    puntaje+=linea;
}

void actualizarDificultad(float& dificultad, int lineas, int& nivel) {
    if(lineas>=10 && lineas<20){
        dificultad = 0.7;
        nivel=2;
    }
    else if(lineas>=20 && lineas<30){
        dificultad=0.6;
        nivel=3;
    }
    else if(lineas>=30 && lineas<40){
        dificultad=0.5;
        nivel=4;
    }
    else if(lineas>=40 && lineas<50){
        dificultad=0.4;
        nivel=5;
    }
    else if(lineas>=50 && lineas<60){
        dificultad=0.3;
        nivel=6;
    }
    else if(lineas>=60 && lineas<70){
        dificultad=0.2;
        nivel=7;
    }
    else if(lineas>=70 && lineas<80){
        dificultad=0.15;
        nivel=8;
    }
    else if(lineas>=80 && lineas<90) {
        dificultad = 0.1;
        nivel = 9;
    }
    else if(lineas>90) {
        dificultad = 0.09;
        nivel = 10;
    }
}

void renderizar(sf::RenderWindow& window, sf::Sprite& spritePieza, sf::Sprite& spriteTablero, sf::Texture& texturaGhost, sf::Sprite& spriteGhost, int color, int colorHold, bool firstHold, int colorNext, sf::Text& text, int& puntaje, float temporizador, int nivel, int cuentaLineas){
    window.clear(sf::Color::Black);
    int x=(window.getSize().x-ancho*30)/2;
    int y=(window.getSize().y-altura*30)/2;
    spriteTablero.setPosition(x, y);
    window.draw(spriteTablero);

    //dibujamos las piezas que estan en el tablero
    for(int i=0; i<altura; i++){
        for(int j=0;j<ancho;j++){
            if (tablero[i][j] == 0) continue;
            spritePieza.setTextureRect(sf::IntRect((tablero[i][j]-1)*30, 0, 30, 30));
            spritePieza.setPosition(x+j*30, y+i*30);
            window.draw(spritePieza);
        }
    }
    //dibujamos el tetromino hold
    int posX=-100;
    int posY=210;
    if(colorHold==tipoTetromino::I){posX=-70; posY=180;}
    if(firstHold){
        for(int i=0; i<4; i++){
            spritePieza.setTextureRect(sf::IntRect(colorHold*30, 0, 30, 30));
            spritePieza.setPosition(posX+hold[i].getX()*30,posY+hold[i].getY()*30);
            window.draw(spritePieza);
        }
    }
    //dibujamos el nextTetromino
    posX=350;
    posY=210;
    if(colorNext==tipoTetromino::I){posX=380; posY=210;}
    for(int i=0; i<4; i++){
        spritePieza.setTextureRect(sf::IntRect(colorNext*30, 0, 30, 30));
        spritePieza.setPosition(posX+nextTetromino[i].getX()*30,posY+nextTetromino[i].getY()*30);
        window.draw(spritePieza);
    }
    //dibujamos el tetromino
    for(int i=0; i<4; i++){
        spritePieza.setTextureRect(sf::IntRect(color*30, 0, 30, 30));
        spritePieza.setPosition(x+tetromino[i].getX()*30, y+tetromino[i].getY()*30);
        window.draw(spritePieza);
    }
    //dibujamos el tetromino ghost
    for (int i=0; i<4; i++){
        spriteGhost.setTextureRect(sf::IntRect(color*30, 0, 30, 30));
        spriteGhost.setPosition(x+ghost[i].getX()*30, y+ghost[i].getY()*30);
        window.draw(spriteGhost);
    }
    //texto
    text.setPosition(20, 15);
    text.setString("SCORE");
    window.draw(text);
    text.setPosition(20, 50);
    std::string s = std::to_string(puntaje);
    text.setString(s);
    window.draw(text);
    text.setPosition(20, 85);
    text.setString("TIME");
    window.draw(text);
    text.setPosition(20, 120);
    int intTemporizador=temporizador;
    s = std::to_string(intTemporizador);
    text.setString(s);
    window.draw(text);
    text.setPosition(20, 155);
    text.setString("HOLD");
    window.draw(text);
    text.setPosition(470, 15);
    text.setString("LEVEL");
    window.draw(text);
    text.setPosition(470, 50);
    s = std::to_string(nivel);
    text.setString(s);
    window.draw(text);
    text.setPosition(470, 85);
    text.setString("LINES");
    window.draw(text);
    text.setPosition(470, 120);
    s = std::to_string(cuentaLineas);
    text.setString(s);
    window.draw(text);
    text.setPosition(470, 155);
    text.setString("NEXT");
    window.draw(text);

    window.display();//actualiza la pantalla
}

bool verificarFinalJuego(){
    for(int i=0; i<ancho; i++){
        if(tablero[0][i]!=0){ //si llegamos a la primera linea de arriba, o se genera el tetromino donde ya existen piezas, pierde
            return false;
        }
    }
    for(int i=0; i<4; i++){
        int x = tetromino[i].getX();//revisa las posiciones X e Y
        int y = tetromino[i].getY();
        if(tablero[y][x]){
            return false;
        }
    }
    return true;
}



#endif // FUNCIONES_H_INCLUDED
