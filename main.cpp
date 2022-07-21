#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
class EntityMobile{
    protected:
    bool right_;
    bool down_;
    sf::Texture texture_;
    sf::Sprite sprite_;
    sf::Sprite sprite_projectile_;
    float posX_, posY_;
    float width_, height_;
    int velocityx_;
    int velocityy_;
    int velocity_alien_x_;
    int velocity_alien_y_;

    //std::vector<sf::Sprite> balas;


    public:
    EntityMobile(float x, float y, std::string image, float sizeDeseada){
        /*
        aqui se crea la logica para darle a el sprite las dimenciones que deseamos como parametro en el constructor
        */
        this->texture_.loadFromFile(image);
        this->sprite_.setTexture(this->texture_);
        float indice_escala;
        indice_escala=sizeDeseada*100.0/this->sprite_.getGlobalBounds().width;
        this->sprite_.setScale(indice_escala*0.01, indice_escala*0.01);
        this-> posX_=x;
        this-> posY_=y;
        this->sprite_.setPosition(x,y);
        this->right_=true;

        /*
        Variable calculo de Velocidad
        */
        //Plane
        this->velocityx_= 5;
        this->velocityy_= 5;
        //Aliens
        this->velocity_alien_x_= 7;
        this->velocity_alien_y_= 7;


        sf::Texture tex;
        tex.loadFromFile("media/laser.png");
        this->sprite_projectile_.setTexture(tex);
        indice_escala=10*100.0/this->sprite_.getGlobalBounds().width;
        this->sprite_projectile_.setScale(indice_escala*0.01, indice_escala*0.01);




        this->width_= this->sprite_.getGlobalBounds().width;
        this->height_= this->sprite_.getGlobalBounds().height;


    }

        void Show(sf::RenderWindow &ventana){
            ventana.draw(this->sprite_);
            }

        void MoveLeft(){
            if(this->posX_<=1){
                this->posX_=1280 - 100;
            }else{
                this->posX_=this->posX_-this->velocityx_;
            }
        }


        void MoveRight(){

            if(this->posX_>1280 -100 ){
                this->posX_=1;
            }else{
                this->posX_=this->posX_+this->velocityx_;
            }
        }
        void MoveUp(){
            if(this->posY_<=1){
                this->posY_=720 -100;
            }else{
                this->posY_=this->posY_-this->velocityx_;
            }
        }
        void MoveDown(){
            if(this->posY_>=720 - 100){
                this->posY_=1;
            }else{
                this->posY_=this->posY_+this->velocityx_;
            }
        }
        void MoveAutomaticX(sf::RenderWindow &window){
            if(this->right_==true){
                if(this->posX_<1280.0 - 100){
                    this->posX_=this->posX_+this->velocity_alien_x_;
                }else{
                    this->right_=false;

                }

            }else{
                if(this->posX_>1.0){
                    this->posX_=this->posX_-this->velocity_alien_x_;
                }else{
                    this->right_=true;

                }
            }
            this->sprite_.setPosition(this->posX_, this->posY_);
            window.draw(this->sprite_);

        }

        void MoveAutomaticY(sf::RenderWindow &window){

                 if(this->posY_<720.0 - 20){
                    this->posY_=this->posY_+this->velocity_alien_y_;
                    window.draw(this->sprite_);
                }else{
                    this->down_=false;

                }


            this->sprite_.setPosition(this->posX_, this->posY_);
        }


    float GetHeight() {
        return this->height_;
    }
    float GetWidth() {
        return this->width_;
    }
    float GetPosX() {
        return this->posX_;
    }
    float GetPosY() {
        return this->posY_;
    }

    bool MovesRight() {
        return this->right_;
    }





};






class Alien:public EntityMobile{
    protected:

    public:
    Alien(float x, float y, std::string image, float dim):EntityMobile(x, y, image, dim){

        }


};










class SpaceShip:public EntityMobile{
private:
    int hp;
    int presed;
    std::vector<sf::Sprite> projectile_;
public:
    SpaceShip(float x, float y, std::string image, float dim):EntityMobile(x, y, image, dim){

        this->hp=2;



        presed =0;

    }



    void Move(){

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            this->MoveLeft();
            //std::cout<< "ancho: " << this->ancho<< "\n";
           // std::cout<< "alto: " << this->alto<< "\n";
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            this->MoveDown();
            //std::cout<< this->GetAncho() << "\n";
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            this->MoveUp();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            this->MoveRight();
        }

        this->sprite_.setPosition(this->posX_, this->posY_);
        //std::cout<< "mover\n";
    }
    void CatchIntersections(Alien &alien){


       sf::FloatRect imagen(alien.GetPosX(), alien.GetPosY(), alien.GetWidth(), alien.GetHeight());
        if (this->sprite_.getGlobalBounds().intersects(imagen)) {
            // std::cout<< "yes\n";

        }
        else {
            // std::cout<< "no\n";
        }

    }

      void ShootUp(sf::RenderWindow& window) {
        //window.draw(this->sprite_projectile_);
        this->sprite_projectile_.setPosition(this->posX_ + 0.5 * this->width_, this->posY_ - this->sprite_projectile_.getGlobalBounds().height);
        this->projectile_.push_back(this->sprite_projectile_);
        //window.draw(ojo);
        //this->projectile_[this->projectile_.size()-1].setPosition(this->sprite_projectile_.getGlobalBounds().height);
        window.draw(this->projectile_[this->projectile_.size() - 1]);




            /*sf::Sprite current_bala;
            sf::Texture imagen;
            imagen.loadFromFile("laser.png");

            current_bala.setTexture(imagen);

            float escala;
            escala=30*100.0/current_bala.getGlobalBounds().width;
            current_bala.setScale(escala*0.01,escala*0.01);

            this->balas[this->cantidad_balas]=current_bala;
            this->balas[this->cantidad_balas].setPosition(this->posX_+0.5*this->ancho, posY_+10);
            window.draw(this->balas[this->cantidad_balas]);
            this->cantidad_balas++;
            */


            //window.draw(this->balas[this->cantidad_balas]);


        }
};
//End


int main(){
    //Parametros de Ventana
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Space Invaders!");
    window.setFramerateLimit(40);

    //Instancias
    SpaceShip ship1(590,600,"media/plane.png",100);
    Alien al1(1,1,"media/white-alien.png",110);
    //Renderizado
    while (window.isOpen()){
        // Process events
        sf::Event event;
        while (window.pollEvent(event)){
        // Close window: exit
            if (event.type == sf::Event::Closed)
            window.close();
        }
    // Clear screen
        window.clear();
        ship1.Move();
        al1.MoveAutomaticX(window);
        ship1.CatchIntersections(al1);
        ship1.Show(window);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
         ship1.ShootUp(window);
        }
        window.display();
    }
    return EXIT_SUCCESS;
}
