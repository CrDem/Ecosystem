#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "map.h"
#include "Creature.h"

using namespace sf;
class Herbivore: public Creature {
public:
    static std::list<Herbivore*> HerbivoresList;
    static int BRCH;
public:
    Herbivore(Image& image,float X, float Y, float W, float H):Creature(image,X,Y,W,H){
        HerbivoresList.insert(HerbivoresList.end(),this);
        shining = false;
        sprite.setTextureRect(IntRect(8, 7, w, h));
        sprite.setOrigin(16,16);
        sprite.setPosition(x,y);
    }
    ~Herbivore(){
        HerbivoresList.erase(std::find(HerbivoresList.begin(), HerbivoresList.end(), this));
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
            curr->updateDirTo(nearestPlant(curr->x,curr->y,curr->dir));
        }
    }
    static void HerbivoresUpdate(const float currentFrame, const float time);
    static int nearestPlant(float x, float y, int dir);

    void updateDirTo (int DIR) {
        if (DIR<0 || DIR>3) throw std::invalid_argument("net takogo direction alo");
        dir = DIR;
    }
    void nextTexture(float currentFrame);
    static unsigned long long int getAmountOfHerbivores() {
        return HerbivoresList.size();
    };
    bool isOnMap(int x, int y) {
        return (x>32 && y>32 && x<(WIDTH_MAP-1)*32 && y<(HEIGHT_MAP-1)*32);
    }
    //IntRect getRect() { return IntRect(x,y,w-20,h-20); }

private:
    float dx = 0, dy = 0, speed = 0.05;
    int dir = 0, hunger = 0;
    bool shining, stopShining;

    void replication(bool distanceReplication);
    void interactionWithFlowers();
};