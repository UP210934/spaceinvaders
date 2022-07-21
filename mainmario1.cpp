#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 400), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Texture texture_1;
        if (!texture_1.loadFromFile("media/background_tree.jpg"))
            return EXIT_FAILURE;
        sf::Sprite sprite_back(texture_1);
        sprite_back.setPosition(0,0);

        //Koopa
        sf::Texture texture;
        if (!texture.loadFromFile("media/koopa_txt.jpg"))
            return EXIT_FAILURE;
        sf::Sprite sprite(texture);

             sprite.setPosition(1,1);
        window.clear();
         // Draw the sprite
        window.draw(sprite_back);
        window.draw(sprite);
        //window.draw(shape);
        window.display();
    }

    return 0;
}
