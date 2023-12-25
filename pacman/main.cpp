#include <SFML/Graphics.hpp>

int main()
{
    sf::Window window(sf::VideoMode(800, 600), "My window");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::End))
        {
            // left key is pressed: move our character
            window.close();
        }
    }

    return 0;
}