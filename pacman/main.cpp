#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <map>

const char *map = R""""(XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
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
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX)"""";

sf::RectangleShape Wall(int x, int y)
{
    sf::RectangleShape rectangle(sf::Vector2f(20.f, 20.f));
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition(x * 20.f, y * 20.f);

    return rectangle;
}

sf::RectangleShape TheMan(int x, int y)
{
    sf::RectangleShape rectangle(sf::Vector2f(20.f, 20.f));
    rectangle.setFillColor(sf::Color::Yellow);
    rectangle.setPosition(x * 20.f, y * 20.f);

    return rectangle;
}

sf::RectangleShape Feed(int x, int y)
{
    sf::RectangleShape rectangle(sf::Vector2f(20.f, 20.f));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setPosition(x * 20.f, y * 20.f);

    return rectangle;
}

int main()
{
    std::vector<sf::RectangleShape> walls;

    int x = 0;
    int y = 0;
    for (char c = *map; c; c=*++map)
    {
        switch (c)
        {
            case 'X':
                walls.push_back(Wall(x, y));
                break;
            case 'Y':
                walls.push_back(Feed(x, y));
                break;
            default:
                break;
        }

        if (c == '\n')
        {
            y += 1;
            x = 0;
        }
        else
        {
            x += 1;
        }
    }

    sf::RenderWindow window(sf::VideoMode(780, 260), "Pacman");

    int pacmanXPosition = 19;
    int pacmanYPosition = 8;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::End))
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                pacmanXPosition += 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                pacmanXPosition -= 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                pacmanYPosition -= 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                pacmanYPosition += 1;

        }

        window.clear();

        for (sf::RectangleShape wall : walls)
        {
            window.draw(wall);
        }

        window.draw(TheMan(pacmanXPosition, pacmanYPosition));

        window.display();
    }

    return 0;
}
