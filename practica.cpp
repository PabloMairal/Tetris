#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");  //crea un objeto ventana, VideoMode() define el tamaño, el segundo argumento es el nombre
    sf::RectangleShape piece(sf::Vector2f(400.0f, 50.0f));  //crea un objeto rectangulo, Vector2f define el tamaño del rectangulo
    //piece.setFillColor(sf::Color::Magenta);  //cambia el color de la pieza(piece)
    sf::Texture pieceTexture;
    pieceTexture.loadFromFile("resources/sprite/solidTetris.png");
    piece.setTexture(&pieceTexture);
    piece.setOrigin(sf::Vector2f(50.0f, 50.0f));  //cambia el punto de origen de la pieza

       while (window.isOpen())  //checkea que la ventana esta abierta, sería un while(true) a fines practicos
    {
        sf::Event event;  //crea un evento, que es lo que nos permite hacer cosas en la ventana(cerrarla, escribir, etc)
        while (window.pollEvent(event))//checkea el evento
        {
            switch(event.type)//según el tipo de evento, hacemos cosas distintas
            {

            case sf::Event::Closed://si cerramos la ventana con la X o alt+f4, ese evento se llama Closed
                window.close();//acá cerramos la ventana manualmente, si comentamos esta linea al cerrar la ventana no se cerraría, hay que hacerlo manual
                break;

            case sf::Event::Resized://Resized es el cambio del tamaño de la ventana
                std::cout<<"New window width: " << event.size.width << "New window height: " << event.size.height<< std::endl;//muestra por consola el nuevo tamaño
                break;

            case sf::Event::TextEntered://checkea si entró texto
                if(event.text.unicode<128)//checkea que el texto se encuentre dentro de los primeros 128 caracteres de unicode(letras, numeros, simbolos)
                {
                    printf("%c", event.text.unicode);//escribe en la consola el caracter, si haces un cout te va a escribir el numero de unicode
                }
                break;
            }

        }

        //a partir de acá manipulamos cosas dentro de la ventana, no se necesitan eventos

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))//checkea si se hizo click izquierdo con el mouse
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);//crea un vector de tipo integer para asignarle la posicion del mouse
            piece.setPosition((float)mousePos.x, (float)mousePos.y);//movemos la pieza a la posicion actual del mouse
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))//movemos la pieza con la tecla A, etc
        {
            piece.move(-0.1f, 0.0f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            piece.move(0.1f, 0.0f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            piece.move(0.0f, -0.1f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            piece.move(0.0f, 0.1f);
        }
        window.clear();//limpia la ventana como system("cls")
        window.draw(piece);//dibuja la pieza en el buffer, es como una ventana que no vemos, sería como el valor guardado en una variable antes de imprimirla
        window.display();//imprime en la pantalla lo que esta en el buffer como si fuera un cout
    }


    return 0;
}
