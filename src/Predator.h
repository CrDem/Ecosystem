//#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Creature.h"

using namespace sf;
class Predator: public Creature {
private:
    static std::list<Predator*> PredatorsList;
public:
    Predator(Image& image,float X, float Y, float W, float H):Creature(image,X,Y,W,H){
        PredatorsList.insert(PredatorsList.end(),this);
        w -= 15; h -= 15;//высота и ширина
        sprite.setTextureRect(IntRect(0, 0, w, h));
        sprite.setOrigin(16,16);
        sprite.setPosition(x,y);
    }

    void update(float time);
    void interactionWithMap();

    static void drawPredators (sf::RenderWindow* window) {
        for (Predator* curr:PredatorsList) {
            window->draw(curr->sprite);
        }
    }
    static void updateDirPredators() {
        for (Predator* curr:PredatorsList) {
            curr->updateDirTo(nearestHerbivore(curr->x,curr->y,curr->dir));
        }
    }
    static int nearestHerbivore(float x, float y, int dir);
    static void PredatorsUpdate(const float currentFrame, const float time);

    void updateDirTo (int DIR) {
        //if (DIR>3 || DIR<0) throw std::invalid_argument("net takogo direction alo");
        dir = DIR;
    }
    void nextTexture(float currentFrame) {
        sprite.setTextureRect(IntRect(32 * (int(currentFrame)%3), 0, 32, 32));
    }
    static unsigned long long int getAmountOfPredators() {
        return PredatorsList.size();
    };
    //IntRect getRect() { return IntRect(x,y,w-20,h-20); }

private:
    float dx = 0, dy = 0, speed = 0.07; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
    int dir{rand()%360}, hunger{0};
    void replication();
    void interactionWithHerbivores();
};