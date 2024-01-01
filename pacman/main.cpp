#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <map>
#include <list>
#include <cmath>

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

bool CanMove(std::vector<sf::RectangleShape>& objects, int targetX, int targetY)
{
    for (sf::RectangleShape object : objects)
    {
        sf::Vector2f position = object.getPosition();
        if(position.x == floor(targetX) * 20 && position.y == floor(targetY) * 20)
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
        if(position.x == (floor(targetX) * 20) && position.y == (floor(targetY) * 20))
        {
            if (indexToEraseFeed < feeds.size())
            {
                feeds.erase(feeds.begin() + indexToEraseFeed);
            }
        }

        indexToEraseFeed += 1;
    }
}

enum Direction { right, top, left, bottom, stable };

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
    window.setFramerateLimit(30);

    float pacmanXPosition = 19;
    float pacmanYPosition = 8;
    Direction direction = right;

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
                        if (CanMove(walls, (pacmanXPosition + 1), pacmanYPosition))
                        {
                            BaitFeed(feeds, (pacmanXPosition + 1), pacmanYPosition);
                            direction = right;
                        }
                        break;
                    case sf::Keyboard::Left:
                        if (CanMove(walls, (pacmanXPosition - 1), pacmanYPosition))
                        {
                            BaitFeed(feeds, (pacmanXPosition - 1), pacmanYPosition);
                            direction = left;
                        }
                        break;
                    case sf::Keyboard::Up:
                        if (CanMove(walls, pacmanXPosition, (pacmanYPosition - 1)))
                        {
                            BaitFeed(feeds, pacmanXPosition, (pacmanYPosition - 1));
                            direction = top;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (CanMove(walls, pacmanXPosition, (pacmanYPosition + 1)))
                        {
                            BaitFeed(feeds, pacmanXPosition, (pacmanYPosition + 1));
                            direction = bottom;
                        }
                        break;
                    default:
                        break;
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

        switch (direction)
        {
            case top:
                if (CanMove(walls, pacmanXPosition, (pacmanYPosition - 1)))
                {
                    pacmanYPosition -= 0.15;
                }
                break;
            case bottom:
                if (CanMove(walls, pacmanXPosition, (pacmanYPosition + 1)))
                {
                    pacmanYPosition += 0.15;
                }
                break;
            case right:
            if (CanMove(walls, (pacmanXPosition + 1), pacmanYPosition))
                {
                    pacmanXPosition += 0.15;
                }
                break;
            case left:
            if (CanMove(walls, (pacmanXPosition - 1), pacmanYPosition))
                {
                    pacmanXPosition -= 0.15;
                }
                break;
            default:
                break;
        }

        window.draw(TheMan(pacmanXPosition, pacmanYPosition));

        window.display();
    }

    return 0;
}
