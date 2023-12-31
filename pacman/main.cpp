#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <map>
#include <list>

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

bool CanMove(std::vector<sf::RectangleShape> objects, int targetX, int targetY)
{
    for (sf::RectangleShape object : objects)
    {
        sf::Vector2f position = object.getPosition();
        if(position.x == targetX && position.y == targetY)
        {
            return false;
        }
    }

    return true;
}

void BaitFeed(std::vector<sf::RectangleShape>& feeds, int targetX, int targetY)
{
    int indexToEraseFeed = 0;
    for (sf::RectangleShape feed : feeds)
    {
        sf::Vector2f position = feed.getPosition();
        if(position.x == targetX && position.y == targetY)
        {
            if (indexToEraseFeed < feeds.size()) {
                feeds.erase(feeds.begin() + indexToEraseFeed);
            }
        }

        indexToEraseFeed += 1;
    }
}

int main()
{
    std::vector<sf::RectangleShape> walls;
    std::vector<sf::RectangleShape> feeds;

    int x = 0;
    int y = 0;
    for (char c = *map; c; c=*++map)
    {
        if (c == 'X')
        {
            walls.push_back(Wall(x, y));
        }
        else if (c == 'Y')
        {
            feeds.push_back(Feed(x, y));
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
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if (CanMove(walls, (pacmanXPosition + 1) * 20, pacmanYPosition * 20))
                {
                    BaitFeed(feeds, (pacmanXPosition + 1) * 20, pacmanYPosition * 20);
                    pacmanXPosition += 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if (CanMove(walls, (pacmanXPosition - 1) * 20, pacmanYPosition * 20))
                {
                    BaitFeed(feeds, (pacmanXPosition - 1) * 20, pacmanYPosition * 20);
                    pacmanXPosition -= 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if (CanMove(walls, pacmanXPosition * 20, (pacmanYPosition - 1) * 20))
                {
                    BaitFeed(feeds, pacmanXPosition * 20, (pacmanYPosition - 1) * 20);
                    pacmanYPosition -= 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                if (CanMove(walls, pacmanXPosition * 20, (pacmanYPosition + 1) * 20))
                {
                    BaitFeed(feeds, pacmanXPosition * 20, (pacmanYPosition + 1) * 20);
                    pacmanYPosition += 1;
                }
            }
        }

        window.clear();

        for (sf::RectangleShape wall : walls)
        {
            window.draw(wall);
        }

        for (sf::RectangleShape feed : feeds)
        {
            window.draw(feed);
        }

        window.draw(TheMan(pacmanXPosition, pacmanYPosition));

        window.display();
    }

    return 0;
}
