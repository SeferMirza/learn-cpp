#include <SFML/Graphics.hpp>

class Game
{
public:
    void InitializeGame(const char map[])
    {
        int x = 0;
        int y = 0;
        for (int i = 0; map[i] != '\0'; ++i)
        {
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
                rectangle.setFillColor(sf::Color::Yellow);
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

    void MoveTheMan(int x = 0, int y = 0)
    {
        sf::Vector2f manPosition = _theMan.getPosition();
        sf::Vector2f newPosition = sf::Vector2f(manPosition.x + x, manPosition.y + y);

        if (CanMove(newPosition.x, newPosition.y))
        {
            BaitFeed(newPosition.x, newPosition.y);
            _theMan.setPosition(newPosition.x, newPosition.y);
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
    char *_map;
    sf::RectangleShape _theMan;
    std::vector<sf::RectangleShape> _walls;
    std::vector<sf::RectangleShape> _feeds;

    bool CanMove(int targetX, int targetY)
    {
        for (sf::RectangleShape object : _walls)
        {
            sf::Vector2f position = object.getPosition();
            if (position.x == targetX && position.y == targetY)
            {
                return false;
            }
        }

        return true;
    }
    void BaitFeed(int targetX, int targetY)
    {
        int indexToEraseFeed = 0;
        for (sf::RectangleShape feed : _feeds)
        {
            sf::Vector2f position = feed.getPosition();
            if (position.x == targetX && position.y == targetY)
            {
                if (indexToEraseFeed < _feeds.size())
                {
                    _feeds.erase(_feeds.begin() + indexToEraseFeed);
                }
            }

            indexToEraseFeed += 1;
        }
    }
};
