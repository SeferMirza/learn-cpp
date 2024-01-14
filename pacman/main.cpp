#include <SFML/Graphics.hpp>

#include "game.cpp"

const char map[] = R"(XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
X   Y    XXXX      Y      XXXX    Y   X
X XXXXXX XXXX XXXXXXXXXXX XXXX XXXXXX X
X XXXXXX XXXX XXXXXXXXXXX XXXX XXXXXX X
X                                     X
XXXXXXXX XXXX XXXXXDXXXXX XXXX XXXXXXXX
XXXXXXXX XXXX X         X XXXX XXXXXXXX
XXXXXXXX XXXX XXXXXXXXXXX XXXX XXXXXXXX
X                  P                  X
X XXXXXX XXXX XXXXXXXXXXX XXXX XXXXXX X
X XXXXXX XXXX XXXXXXXXXXX XXXX XXXXXX X
X   Y    XXXX      Y      XXXX    Y   X
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX)";

int main()
{
    sf::RenderWindow window(sf::VideoMode(780, 260), "Pacman");
    window.setFramerateLimit(30);

    Game game;
    game.InitializeGame(map);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Right:
                    game.MoveTheMan(20, 0);
                    break;
                case sf::Keyboard::Left:
                    game.MoveTheMan(-20, 0);
                    break;
                case sf::Keyboard::Up:
                    game.MoveTheMan(0, -20);
                    break;
                case sf::Keyboard::Down:
                    game.MoveTheMan(0, 20);
                    break;
                default:
                    break;
                }
            }
        }

        window.clear();

        game.Draw(window);

        window.display();
    }

    return 0;
}
