#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>

const char *map = R""""(
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
X   Y    XXXX     Y       XXXX   Y    X
X XXXXXX XXXX XXXXXXXXXXX XXXX XXXXXX X
X XXXXXX XXXX XXXXXXXXXXX XXXX XXXXXX X
X                                     X
XXXXXXXX XXXX XXXXXDXXXXX XXXX XXXXXXXX
XXXXXXXX XXXX X         X XXXX XXXXXXXX
XXXXXXXX XXXX XXXXXXXXXXX XXXX XXXXXXXX
X                                     X
X XXXXXX XXXX XXXXXXXXXXX XXXX XXXXXX X
X XXXXXX XXXX XXXXXXXXXXX XXXX XXXXXX X
X   Y    XXXX      Y      XXXX   Y    X
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
)"""";

sf::RectangleShape Wall(int x, int y)
{
    sf::RectangleShape rectangle(sf::Vector2f(20.f, 20.f));
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition(index * 30.f, 0.f);

    return rectangle;
}

int main()
{
    for (char c = *map; c; c=*++map) {
        std::cout << c;
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pacman");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::End))
                window.close();
        }

        window.clear();
        for (size_t i = 0; i < 40; i++)
        {
            window.draw(Wall(i));
        }

        window.display();
    }

    return 0;
}
