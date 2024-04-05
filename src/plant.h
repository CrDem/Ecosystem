#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "map.h"
#include "Creature.h"
#include <list>

using namespace sf;
class Plant: public Creature{
public:
    static std::list<Plant*> PlantsList;
    static int BRCP;
public:
    Plant(Image& image,float X, float Y, float W, float H):Creature(image,X,Y,W,H){
        PlantsList.insert(PlantsList.end(),this);
        w /= 2; h /= 2;
        shining = false;
        readyToProduce = false;
        //sprite.setColor(Color(0,0,0));//заливаем спрайт цветом
        sprite.setTextureRect(IntRect(0, 0, w, h));
        sprite.setOrigin(8,16);
        sprite.setPosition(x,y);
    }
    ~Plant(){
        PlantsList.erase(std::find(PlantsList.begin(), PlantsList.end(), this));
    }

    static void drawPlants (sf::RenderWindow* window) {
        for (Plant* curr:PlantsList) {
            window->draw(curr->sprite);
        }
    }
    bool isOnMap(int x, int y) {
        return (x>32 && y>32 && x<(WIDTH_MAP-1)*32 && y<(HEIGHT_MAP-1)*32);
    }
    static void PlantsUpdate(const float currentFrame, const float time);
    //static unsigned long long int getAmountOfPlants() { return PlantsList.size(); };

private:
    bool shining, readyToProduce;
    int chanceToShine = -1, childrenCouter = 0;
    void update(float time);
    void nextTexture(float currentFrame);
    void replication();
    int crowdCounter();
};