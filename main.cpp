#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;

// Global Instances
int const screen_width = 1280;
int const screen_heigth = 720;

class EntityMobile
{
protected:
    bool right_;
    bool down_;
    sf::Texture texture_;
    sf::Texture texture2_;
    sf::Sprite sprite_;
    sf::Sprite sprite_projectile_;
    float posX_, posY_;
    float width_, height_;

public:
    EntityMobile()
    {
        this->right_ = true;
        this->down_ = false;
    }

    void Show(sf::RenderWindow &ventana)
    {
        ventana.draw(this->sprite_);
    }

    // movement

    void MoveLeft(float velocidad)
    {
        if (this->posX_ <= 1)
        {
            this->posX_ = screen_width - this->width_;
        }
        else
        {
            this->posX_ = this->posX_ - velocidad;
        }
    }

    void MoveRight(float velocidad)
    {

        if (this->posX_ > screen_width - this->width_)
        {
            this->posX_ = 1;
        }
        else
        {
            this->posX_ = this->posX_ + velocidad;
        }
    }
    void MoveUp(float velocidad)
    {
        if (this->posY_ <= 1)
        {
            this->posY_ = screen_heigth - this->height_;
        }
        else
        {
            this->posY_ = this->posY_ - velocidad;
        }
    }
    void MoveDown(float velocidad)
    {
        if (this->posY_ >= screen_heigth - this->height_)
        {
            this->posY_ = 1;
        }
        else
        {
            this->posY_ = this->posY_ + velocidad;
        }
    }

    void MoveAutomaticY(sf::RenderWindow &window, float velocidad)
    {

        if (this->posY_ >= -this->height_)
        {
            this->posY_ = this->posY_ - velocidad;

            window.draw(this->sprite_);
        }
        else
        {
            this->down_ = true;
        }

        this->sprite_.setPosition(this->posX_, this->posY_);
    }

    // setters and getters
    float GetHeight()
    {
        return this->height_;
    }
    float GetWidth()
    {
        return this->width_;
    }
    float GetPosX()
    {
        return this->posX_;
    }
    float GetPosY()
    {
        return this->posY_;
    }

    void SetPos(float x, float y)
    {
        this->posX_ = x;
        this->posY_ = y;
        this->sprite_.setPosition(x, y);
    }
};

class Bala : public EntityMobile
{
protected:
    bool in_screen_;

public:
    Bala(float sizeDeseada) : EntityMobile()
    {
        in_screen_ = true;
        this->texture_.loadFromFile("media/laser.png");
        this->sprite_.setTexture(this->texture_);
        float indice_escala = sizeDeseada * 100.0 / this->sprite_.getGlobalBounds().width;
        this->sprite_.setScale(indice_escala * 0.01, indice_escala * 0.01);
        this->width_ = this->sprite_.getGlobalBounds().width;
        this->height_ = this->sprite_.getGlobalBounds().height;
    }
    bool InScreen()
    {
        if (this->down_)
        {
            this->in_screen_ = false;
        }
        return this->in_screen_;
    }
    void SetPos(float x, float y)
    {
        this->posX_ = x;
        this->posY_ = y;
        this->sprite_.setPosition(x, y);
    }
    void UpdateTexture()
    {

        this->sprite_.setTexture(this->texture_);
    }

    bool CatchIntersectionsShoots(EntityMobile &alien)
    {
        sf::FloatRect imagen(alien.GetPosX(), alien.GetPosY(), alien.GetWidth(), alien.GetHeight());
        if (this->sprite_.getGlobalBounds().intersects(imagen))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool CatchIntersectionsShoots(sf::FloatRect imagen)
    {
        if (this->sprite_.getGlobalBounds().intersects(imagen))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Alien : public EntityMobile
{
private:
    //-----------------ATTRIBUTES USED IN ShootDown
    int direction_ = 1;
    sf::Clock clock_move_;
    sf::Time time_passed_move_;
    float sec_passed_move_;

    sf::Clock clock_;
    sf::Time time_elapsed_;
    float sec_passed_;
    int shoot_cooldown_;
    std::vector<Bala> projectile_;
    int ali_velocity_;
    int time_;
    float projectile_vel;

public:
    Alien(float dim) : EntityMobile()
    {
        this->texture_.loadFromFile("media/white-alien.png");
        this->texture2_.loadFromFile("media/white-alien2.png");
        this->sprite_.setTexture(this->texture_);
        float indice_escala = dim * 100.0 / this->sprite_.getGlobalBounds().width;
        this->sprite_.setScale(indice_escala * 0.01, indice_escala * 0.01);
        this->sprite_.setPosition(1, 1);
        this->width_ = this->sprite_.getGlobalBounds().width;
        this->height_ = this->sprite_.getGlobalBounds().height;
        this->posX_ = 1;
        this->posY_ = 1;
        int time_ = 0;
        this->ali_velocity_ = 3;    // 8
        this->shoot_cooldown_ = 10; // 10
        this->projectile_vel = 7;
    }
    //------------------------MOVEMENT ------------------
    void MoveAutomaticX(sf::RenderWindow &window)
    {
        if (this->posY_ < screen_heigth)
        {

            this->time_passed_move_ = this->clock_move_.getElapsedTime();
            this->sec_passed_move_ = this->time_passed_move_.asSeconds();
            // cout<<sec_paseed1_<<endl;
            if (this->direction_ == 1)
            { // 1  +  direccion derecha
                this->posX_ = this->posX_ + this->ali_velocity_;
            }
            // if(this->direction_==3) {   //3  -  direccion izquierda
            // this->posX_=this->posX_-velocidad;
            //}
            if (this->direction_ == 2)
            { // 2 or 4  + direccion abajo
                this->posY_ = this->posY_ + this->ali_velocity_;
            }
            if (this->sec_passed_move_ > 1.5)
            { // 2.5
                this->clock_move_.restart();
                this->direction_++;
            }

            // hacer reloj para cada dirección probablemente para adaptarlo, o bajarle la velocidad del alien
            this->sprite_.setPosition(this->posX_, this->posY_);
            window.draw(this->sprite_);
            if (this->direction_ > 2)
            { //>4
                this->direction_ = 0;
            }
        }
        else
        {
        }
    }
    void Animation()
    {
        this->time_++;
        this->sprite_.setTexture(this->texture_);
        if (this->time_ > 80)
        {
            this->sprite_.setTexture(this->texture2_);
        }
        if (this->time_ > 160)
        {
            this->sprite_.setTexture(this->texture_);
        }
        if (this->time_ > 240)
        {
            this->time_ = 0;
        }
    }

    /*int IncreaseVelocity(float lvl) {
        if (this->ali_velocity_ < 14 && this->ali_velocity_>3)  // 8
            this->ali_velocity_ += (lvl + 2);
        if (this->shoot_cooldown_ > 3) {
            this->shoot_cooldown_ -= (lvl * 2);
        }
        return this->ali_velocity_;
    }*/

    //---------------------SHOOTING
    void ShootDown()
    { // pseudo-aleatorio patrón de disparo automático
        this->time_elapsed_ = this->clock_.getElapsedTime();
        this->sec_passed_ = this->time_elapsed_.asSeconds(); // segundos que han pasado desde que se creo la isntancia de Alien o se reinicio el clock

        int random_count = (rand() * rand()) % this->shoot_cooldown_ + 1;
        // random_count es el tiempo que debe pasar entre un disparo y otro
        // puede ir desde 1 segundo hasta shoot_cooldown + 1 segundos en este caso, se puede modificar

        if (this->sec_passed_ >= random_count)
        {
            // esta parte tiene lo que va a hacer que saque las balas
            if (rand() % 2 == 1)
            {
                Bala balita = Bala(4);
                balita.SetPos(this->posX_ + 0.5 * this->width_, this->posY_ - this->sprite_projectile_.getGlobalBounds().height + this->height_),
                    this->projectile_.push_back(balita);
                this->projectile_[this->projectile_.size() - 1].UpdateTexture();
            }

            // this->projectile_[this->projectile_.size() - 1].UpdateTexture();
            // this->projectile_[this->projectile_.size() - 1].Show(window);
            this->clock_.restart(); // reiniciar clock del alien
        }
    }
    void MoveProjectile_(sf::RenderWindow &window)
    {
        for (int i = 0; i < this->projectile_.size(); i++)
        {
            if (projectile_[i].InScreen())
            {
                projectile_[i].UpdateTexture();
                projectile_[i].MoveAutomaticY(window, -this->projectile_vel);
            }
        }
    }
    void DeleteTrashProjectile()
    {
        if (!this->projectile_.empty())
        {
            if (this->projectile_[0].InScreen() == false)
            {
                this->projectile_.erase(this->projectile_.begin());
            }
        }
    }

    bool CatchIntersections(EntityMobile &ship)
    {
        for (int i = 0; i < this->projectile_.size(); i++)
        {
            if (this->projectile_[i].CatchIntersectionsShoots(ship))
            {
                return true;
            }
        }
        return false;
    }

    void UpdateTexture()
    {

        this->sprite_.setTexture(this->texture_);
    }
};

// End Alien

class SpaceShip : public EntityMobile
{
private:
    float velocityx_;
    std::vector<Bala> projectile_;

public:
    SpaceShip(float dim) : EntityMobile()
    {
        this->velocityx_ = 10; // 10
        this->texture_.loadFromFile("media/plane.png");
        this->sprite_.setTexture(this->texture_);
        float indice_escala = dim * 100.0 / this->sprite_.getGlobalBounds().width;
        this->sprite_.setScale(indice_escala * 0.01, indice_escala * 0.01);
        this->posX_ = 590;
        this->posY_ = 600;
        this->sprite_.setPosition(this->posX_, this->posY_);
        this->width_ = this->sprite_.getGlobalBounds().width;
        this->height_ = this->sprite_.getGlobalBounds().height;
    }

    void Move()
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            this->MoveLeft(this->velocityx_);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            this->MoveRight(this->velocityx_);
        }

        this->sprite_.setPosition(this->posX_, this->posY_);
    }
    bool CatchIntersections(Alien &alien)
    {
        for (int i = 0; i < this->projectile_.size(); i++)
        {
            if (this->projectile_[i].CatchIntersectionsShoots(alien))
            {
                return true;
            }
        }
        return false;
    }

    int CatchIntersections(std::vector<sf::FloatRect> alien)
    {
        for (int i = 0; i < this->projectile_.size(); i++)
        {
            for (int j = 0; j < alien.size(); j++)
            {
                if (this->projectile_[i].CatchIntersectionsShoots(alien[j]))
                {
                    this->projectile_.erase(projectile_.begin() + i);
                    return j;
                }
            }
        }
        return -1;
    }

    void MoveProjectile_(sf::RenderWindow &window)
    {
        for (int i = 0; i < this->projectile_.size(); i++)
        {
            if (projectile_[i].InScreen())
            {
                projectile_[i].UpdateTexture();
                projectile_[i].MoveAutomaticY(window, (this->velocityx_ * 1.6));
            }
        }
    }

    bool ShootUp(sf::RenderWindow &window)
    {
        // window.draw(this->sprite_projectile_);
        // this->sprite_projectile_.setPosition(this->posX_ + 0.5 * this->width_, this->posY_ - this->sprite_projectile_.getGlobalBounds().height);

        if (this->projectile_.size() < 3)
        {
            Bala balita = Bala(4);
            balita.SetPos(this->posX_ + 0.5 * this->width_, this->posY_);

            this->projectile_.push_back(balita);
            // window.draw(ojo);
            // this->projectile_[this->projectile_.size()-1].setPosition(this->sprite_projectile_.getGlobalBounds().height);
            // window.draw(this->projectile_[this->projectile_.size() - 1].GetSprite());

            return true;
        }
        else
        {
            return false;
        }
    }
    void DeleteTrashProjectile()
    {
        if (!this->projectile_.empty())
        {
            if (this->projectile_[0].InScreen() == false)
            {
                this->projectile_.erase(this->projectile_.begin());
            }
        }
    }

    void RestarSpaceShip()
    {
        this->posX_ = 590;
        this->posY_ = 600;
        this->sprite_.setPosition(this->posX_, this->posY_);
        this->projectile_.clear();
    }

    //
    std::vector<Bala> GetProjectile()
    {
        return this->projectile_;
    }
};
// End

class Game
{
private:
    sf::Font font_;
    int current_level_;
    int max_level_ = 3;
    std::vector<Alien> hive_alien_; // controlar spawn aliens con vector
    int limit_screen_alien_;

public:
    bool alive_;
    Game()
    {
        this->font_.loadFromFile("media/KOMIKAP_.ttf");
        this->alive_ = true;
        this->current_level_ = 1;
        this->CreateAlienHive();
        this->limit_screen_alien_ = screen_heigth - 200;
    }
    bool IfAllienInScreen()
    {
        for (int i = 0; i < this->hive_alien_.size(); i++)
        {
            if (this->hive_alien_[i].GetPosY() >= this->limit_screen_alien_)
            {
                return true;
            }
        }
        return false;
    }
    // Getters
    sf::Font GetFont()
    {
        return this->font_;
    }

    int GetCurrentLevel()
    {
        return this->current_level_;
    }

    int GetMaxLevel()
    {
        return this->max_level_;
    }

    void HudShoots(sf::RenderWindow &window, int balas)
    {
        sf::Text text("Ammo: ", this->font_, 20);
        text.setPosition(1120, 200);
        window.draw(text);
        std::string last_balas(std::to_string(3 - balas));
        sf::Text nbalas(last_balas, this->font_, 20);
        nbalas.setPosition(1260, 200);
        window.draw(nbalas);
    }
    void HudLvl(sf::RenderWindow &window)
    {
        sf::Text text("Level: ", this->font_, 20);
        text.setPosition(1120, 175);
        window.draw(text);
        std::string lvl_str(std::to_string(this->current_level_));
        sf::Text lvl_num(lvl_str, this->font_, 20);
        lvl_num.setPosition(text.getPosition().x + 140, text.getPosition().y);
        window.draw(lvl_num);
    }

    void CallVictory(sf::RenderWindow &window, sf::Sound &bcksound)
    {
        // sf::Text text("Felicidades\nGanaste", this->font_, 50);
        sf::Text text;
        text.setFont(this->font_);
        text.setCharacterSize(50);
        text.setPosition(300, 200);

        if (this->current_level_ >= this->max_level_)
        {
            text.setCharacterSize(40);
            text.setString("VICTORY!!! \nGAME OVER \n(Hold C to see credits) \n(Press R to restart) \n(Press Enter to close) \n");
            text.setFillColor(sf::Color::Green);
            window.draw(text);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            {
                window.clear();
                text.setCharacterSize(25);
                text.setFillColor(sf::Color::White);
                text.setString("Created by: \nLoa, Juan pi, Juancho, Pablito, Miguel, \n Yael, Roger, Derek");
                window.draw(text);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                this->RestartGame(bcksound);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                window.close();
            }
        }
        else
        {
            text.setString("Congrats! \nLevel passed \n(Enter to continue)");
            window.draw(text);
        }

        window.draw(text);
    }

    void CallGameOver(sf::RenderWindow &window)
    {
        this->alive_ = false;
        sf::Text text("Game\nOver", this->font_, 100);
        text.setPosition(530, 160);
        window.draw(text);
        sf::Text text2("Continuar?\nY/N", this->font_, 40);
        text2.setPosition(630, 460);
        window.draw(text2);
    }

    void NextLvl(sf::RenderWindow &window)
    {
        if (this->current_level_ < this->max_level_)
        {

            this->current_level_ = this->current_level_ + 1;
        }
        this->hive_alien_.clear();
        this->CreateAlienHive();
        this->MoveAliens(window);
    }

    void RestartGame(sf::Sound &bcksound)
    {
        this->alive_ = true;
        this->current_level_ = 1;
        this->hive_alien_.clear();
        bcksound.play();
        this->CreateAlienHive();
    }

    // cargando musica de fondo
    sf::SoundBuffer Music()
    {
        sf::SoundBuffer star_wars;
        if (!star_wars.loadFromFile("media/imperial_starwars.wav"))
        {
            std::cout << "ERROR\n";
        }

        return star_wars;
    }

    // cargando sonido de laser
    sf::SoundBuffer DisparoSound()
    {
        sf::SoundBuffer sonido_tata;
        if (!sonido_tata.loadFromFile("media/nave_starwars2.wav"))
        {
            std::cout << "ERROR\n";
        }
        return sonido_tata;
    }

    // control de spawn, movimiento y disparo de aliens

    void CreateAlienHive()
    {
        int num_aliens = this->current_level_ + 4;
        while (this->hive_alien_.size() < num_aliens)
        {
            this->SpawnAlien();
        }
    }
    void SpawnAlien()
    {
        Alien ali = Alien(110);
        if (this->hive_alien_.size() == 0)
        {
            ali.SetPos(1, 1);
        }
        else
        {
            float pos_x = this->hive_alien_[this->hive_alien_.size() - 1].GetPosX() + 100; // 150   altura del vector de los aliens
            float pos_y = this->hive_alien_[this->hive_alien_.size() - 1].GetPosY();
            if (pos_x > 1250 - 150)
            {
                pos_x = 1;
                pos_y = this->hive_alien_[this->hive_alien_.size() - 1].GetPosY() + ali.GetHeight() + 15; // 30
            }
            ali.SetPos(pos_x, pos_y);
        }
        this->hive_alien_.push_back(ali);
    }
    void MoveAliens(sf::RenderWindow &window)
    {

        for (int i = 0; i < this->hive_alien_.size(); i++)
        {
            // this->hive_alien_[i].StartMovement(window, lvl);
            this->hive_alien_[i].MoveAutomaticX(window);
            this->hive_alien_[i].Animation();
        }
    }
    void ShootAliens(sf::RenderWindow &window)
    {
        for (int i = 0; i < this->hive_alien_.size(); i++)
        {
            this->hive_alien_[i].ShootDown();
            this->hive_alien_[i].MoveProjectile_(window);
            this->hive_alien_[i].DeleteTrashProjectile();
        }
    }

    void DellTrashAllienShut()
    {
        if (hive_alien_.empty())
        {
        }
        else
        {
            for (int i = 0; i < this->hive_alien_.size(); i++)
            {
                this->hive_alien_[i].DeleteTrashProjectile();
            }
        }
    }

    void ColissionsWShip(sf::RenderWindow &window, SpaceShip &ship1, sf::Sound &bcksound)
    {
        for (int i = 0; i < this->hive_alien_.size(); i++)
        {
            if (this->hive_alien_[i].CatchIntersections(ship1) || this->IfAllienInScreen())
            {
                window.clear();
                bcksound.stop();
                this->CallGameOver(window);
            }
        }
    }

    std::vector<sf::FloatRect> AliensBalasPos()
    {
        std::vector<sf::FloatRect> alien_balas_pos;
        sf::FloatRect current;
        for (int i = 0; i < this->hive_alien_.size(); i++)
        {
            sf::FloatRect current(this->hive_alien_[i].GetPosX(), this->hive_alien_[i].GetPosY(), this->hive_alien_[i].GetHeight(), this->hive_alien_[i].GetWidth());
            alien_balas_pos.push_back(current);
        }
        return alien_balas_pos;
    }

    void ColisionShipToAlien(SpaceShip &ship1)
    {
        int pos = ship1.CatchIntersections(this->AliensBalasPos());

        if (pos != -1)
        {

            this->hive_alien_.erase(this->hive_alien_.begin() + pos);
        }
    }

    bool IsHiveAlive()
    {
        if (this->hive_alien_.size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{

    // Parametros de Ventana
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_heigth), "Space Invaders!");
    window.setFramerateLimit(50);

    // Instancias
    SpaceShip ship1(100);
    Game game1;

    // musica de fondo
    // game1.ReproducirMusica();
    sf::SoundBuffer fondo = game1.Music();
    sf::Sound bcksound;
    bcksound.setBuffer(fondo);
    bcksound.setLoop(true);
    bcksound.play();

    // sonido de disparo
    // sf::SoundBuffer star_wars;
    sf::SoundBuffer laser_sound = game1.DisparoSound();
    sf::Sound sound;
    sound.setBuffer(laser_sound);

    // Temporal
    bool time_stamp_bool = false;
    bool AllClear = false;
    // Renderizado
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        if (game1.alive_ == false)
        {
            // nEXT

            if (AllClear == true)
            {
                game1.CallVictory(window, bcksound);
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))))
                {
                    game1.NextLvl(window);
                    AllClear = false;
                    // game1.RestartGame();

                    ship1.RestarSpaceShip();
                    game1.alive_ = true;
                }
            }
            else
            {
                // Over
                game1.CallGameOver(window);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) || (event.type == sf::Event::Closed))
                {
                    window.close();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    window.clear();
                    game1.RestartGame(bcksound);
                    ship1.RestarSpaceShip();
                }
            }
        }
        else
        {
            game1.HudShoots(window, ship1.GetProjectile().size());
            game1.HudLvl(window);
            game1.ColisionShipToAlien(ship1);
            ship1.Show(window);
            ship1.Move();
            game1.MoveAliens(window);
            game1.ShootAliens(window);
            game1.ColissionsWShip(window, ship1, bcksound);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (time_stamp_bool == false)
                {
                    if (ship1.ShootUp(window))
                    {
                        sound.play();
                    }
                }
                time_stamp_bool = true;
            }
            else
            {
                time_stamp_bool = false;
            }
            ship1.MoveProjectile_(window);
            ship1.DeleteTrashProjectile();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {
                AllClear = true;
                game1.alive_ = false;
            }

            if (game1.IsHiveAlive())
            {
                AllClear = true;
                game1.alive_ = false;
            }
        }
        window.display();
    }
    return EXIT_SUCCESS;
}
