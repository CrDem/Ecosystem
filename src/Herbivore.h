#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Creature.h"

using namespace sf;
class Herbivore: public Creature {
public:
    static std::list<Herbivore*> HerbivoresList;
public:
    Herbivore(Image& image,float X, float Y, float W, float H):Creature(image,X,Y,W,H){
        HerbivoresList.insert(HerbivoresList.end(),this);
        w -= 20; h -= 20;//высота и ширина
        //image.loadFromFile("C:/Users/Anton/CLionProjects/erg/Ecosystem/textures/Herbivore texture.png");
        //texture.loadFromImage(image);
        //sprite.setTexture(texture);
        //sprite.setColor(Color(100,100,255));//заливаем спрайт цветом

        //x = X; y = Y;//координата появления спрайта
        sprite.setTextureRect(IntRect(0, 0, w, h));
        sprite.setOrigin(16,16);
        sprite.setPosition(x,y);
        //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу.
        //IntRect - приведение типов
    }

    void update(float time);
    void interactionWithMap();

    static void drawHerbivores (sf::RenderWindow* window) {
        for (Herbivore* curr:HerbivoresList) {
            window->draw(curr->sprite);
        }
    }
    static void updateDirHerbivores() {
        for (Herbivore* curr:HerbivoresList) {
            int chance = rand()%5;
            if (chance==0) curr->updateDirTo(rand()%4);
        }
    }
    static void HerbivoresUpdate(const float currentFrame, const float time);

    void updateDirTo (int DIR) {
        if (DIR<0 || DIR>3) throw std::invalid_argument("net takogo direction alo");
        dir = DIR;
    }
    void nextTexture(float currentFrame) {
        sprite.setTextureRect(IntRect(32 * (int(currentFrame)/6), 0, 32, 32));
    }
    static unsigned long long int getAmountOfHerbivores() {
        return HerbivoresList.size();
    };
    //IntRect getRect() { return IntRect(x,y,w-20,h-20); }

private:
    float dx = 0, dy = 0, speed = 0.05; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
    int dir = 0, hunger = 0;
    //Image image;
    //Texture texture;
    //Sprite sprite;

    void replication();
    void interactionWithFlowers();
};