#include <SFML/Graphics.hpp>
#include<iostream>
#include<cstdlib>

class ScreenSaverIMG {
private:
    position;


    SetPosition(int x,int y){
        this->position
    }
public:
    ScreenSaverIMG(){
    }

};


sf::Texture cambiarcolor(){
    sf::Texture a;
     std::cout<<random;
        if(random == 0){
                return &texture();
        }
         else if(random == 1){
                rect.setTexture(texture2,false);
        }
         else if(random == 2){
                rect.setTexture(texture3,false);
        }
        else if(random == 3){
                rect.setTexture(texture4,false);
        }


return a;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "My Program");
    window.setFramerateLimit(60);

    //Textura

     sf::Texture texture;
        if (!texture.loadFromFile("media/download.png"))
            return EXIT_FAILURE;
        sf::Sprite rect(texture);
        sf::Texture texture2;
        if (!texture2.loadFromFile("media/downloadimg.png"))
            return EXIT_FAILURE;

        sf::Texture texture3;
        if (!texture3.loadFromFile("media/downloadred.png"))
            return EXIT_FAILURE;

        sf::Texture texture4;
        if (!texture4.loadFromFile("media/downloadrblue.png"))
            return EXIT_FAILURE;


    //sf::RectangleShape rect;

    sf::Vector2f rectanglePosition(600, 350);


    rect.setPosition(rectanglePosition);
    //rect.setSize(sf::Vector2f(100, 100));

    float xVelocity = 4;
    float yVelocity = 4;
    int imgcount = 0;



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        int random = rand() % 4;
        std::cout<<random;
        //"physics"
        if (rectanglePosition.x < 0 || rectanglePosition.x > 1280 - 216){
            xVelocity *= -1;
              //Randomize

        if(random == 0){
                rect.setTexture(texture,false);
        }
         else if(random == 1){
                rect.setTexture(texture2,false);
        }
         else if(random == 2){
                rect.setTexture(texture3,false);
        }
        else if(random == 3){
                rect.setTexture(texture4,false);
        }



        }
        if (rectanglePosition.y < 0 || rectanglePosition.y > 720 - 94) {
            yVelocity *= -1;
              //Randomize

        if(random == 0){
                rect.setTexture(texture,false);
        }
         else if(random == 1){
                rect.setTexture(texture2,false);
        }
         else if(random == 2){
                rect.setTexture(texture3,false);
        }
        else if(random == 3){
                rect.setTexture(texture4,false);
        }

        }



        rectanglePosition.x += xVelocity;
        rectanglePosition.y += yVelocity;
        rect.setPosition(rectanglePosition);

        //sf::Vector2f igualarposicion(rect.getPosition().x,rect.getPosition().y);
         //std::cout<<"Posicion x: "<<igualarposicion.x<<"  y:"<<igualarposicion.y<<std::endl;
        window.clear();



        //render

        window.draw(rect);
        window.display();
    }



    return 0;
}
