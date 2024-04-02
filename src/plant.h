#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Creature.h"
#include <list>

using namespace sf;
class Plant: public Creature{
public:
    static std::list<Plant*> PlantsList;
    static int BRC;
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
    ~Plant(){ std::cout << "huy\n";}

    static void drawPlants (sf::RenderWindow* window) {
        for (Plant* curr:PlantsList) {
            window->draw(curr->sprite);
        }
    }
    static void PlantsUpdate(const float currentFrame, const float time);
    //static unsigned long long int getAmountOfPlants() { return PlantsList.size(); };

private:
    bool shining, readyToProduce;
    int chanceToShine = -1, crowd = 0;
    void update(float time);
    void nextTexture(float currentFrame);
    void replication();
};