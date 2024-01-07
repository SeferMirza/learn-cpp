#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <map>
#include <list>
#include <cmath>

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

class Game
{
    public:
        void InitializeGame(const char map[])
        {
            int x = 0;
            int y = 0;
            for (int i = 0; map[i] != '\0'; ++i)
            {
                std::cout << map[i];
                if (map[i] == 'X')
                {
                    sf::RectangleShape rectangle(sf::Vector2f(20.f, 20.f));
                    rectangle.setFillColor(sf::Color::Blue);
                    rectangle.setPosition(x * 20.f, y * 20.f);
                    _walls.push_back(rectangle);
                }
                else if (map[i] == 'Y')
                {
                    sf::RectangleShape rectangle(sf::Vector2f(20.f, 20.f));
                    rectangle.setFillColor(sf::Color::White);
                    rectangle.setPosition(x * 20.f, y * 20.f);
                    _feeds.push_back(rectangle);
                }
                else if (map[i] == 'P')
                {
                    sf::RectangleShape rectangle(sf::Vector2f(20.f, 20.f));
                    rectangle.setFillColor(sf::Color::Red);
                    rectangle.setPosition(x * 20.f, y * 20.f);
                    _theMan = rectangle;
                }

                if (map[i] == '\n')
                {
                    y += 1;
                    x = 0;
                }
                else
                {
                    x += 1;
                }
            }
        }

        void MoveTheMan(Direction direction)
        {
            sf::Vector2f manPosition = _theMan.getPosition();
            switch (direction)
            {
                case top:
                    if (CanMove(manPosition.x, manPosition.y - 1))
                    {
                        _theMan.setPosition(manPosition.x, manPosition.y - 20);
                    }
                    break;
                case bottom:
                    if (CanMove(manPosition.x, manPosition.y + 1))
                    {
                        _theMan.setPosition(manPosition.x, manPosition.y + 20);
                    }
                    break;
                case right:
                    if (CanMove(manPosition.x + 1, manPosition.y))
                    {
                        _theMan.setPosition(manPosition.x + 20, manPosition.y);
                    }
                    break;
                case left:
                    if (CanMove(manPosition.x - 1, manPosition.y))
                    {
                        _theMan.setPosition(manPosition.x - 20, manPosition.y);
                    }
                    break;
                default:
                    break;
            }
        }

        void Draw(sf::RenderWindow &window)
        {
            for (sf::RectangleShape wall : _walls)
            {
                window.draw(wall);
            }
            for (sf::RectangleShape feed : _feeds)
            {
                window.draw(feed);
            }
            window.draw(_theMan);
        }

    private:
        int _level;
        char* _map;
        sf::RectangleShape _theMan;
        std::vector<sf::RectangleShape> _walls;
        std::vector<sf::RectangleShape> _feeds;

        bool CanMove(int targetX, int targetY)
        {
            for (sf::RectangleShape object : _walls)
            {
                sf::Vector2f position = object.getPosition();
                if(position.x == floor(targetX) * 20 && position.y == floor(targetY) * 20)
                {
                    return false;
                }
            }

            return true;
        }
};

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
                        game.MoveTheMan(right);
                        break;
                    case sf::Keyboard::Left:
                        game.MoveTheMan(left);
                        break;
                    case sf::Keyboard::Up:
                        game.MoveTheMan(top);
                        break;
                    case sf::Keyboard::Down:
                        game.MoveTheMan(bottom);
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
