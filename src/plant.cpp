#include "Plant.h"
#include <iostream>

std::list<Plant*> Plant::PlantsList;
int Plant::BRC;

void Plant::nextTexture(float currentFrame) {
    if (shining)
        sprite.setTextureRect(IntRect(32 * int(currentFrame/8), 0, 32, 32));

    if (reproductable) {
        if (int(currentFrame / 8) == 0) chanceToShine = rand() % 20;
        if (chanceToShine == 0) shining = true;
        else shining = false;

        if (int(currentFrame / 8) == 2 && shining) readyToProduce = true;
        if (int(currentFrame / 8) == 0 && readyToProduce) {
            readyToProduce = false;
            if(BRC<20) {
                replication();
                BRC++;
            }
            shining = false;
        }
    }
}

void Plant::replication() {
    int dist = 30;
    Image image;
    image.loadFromFile("C:/Users/Anton/CLionProjects/erg/Ecosystem/textures/flower texture.png");
    for (int i = 0; i < 3; ++i) {
        int deg = rand()%360;
        int childX = dist*cos(deg), childY = dist*sin(deg);
        if (isOnMap(x+childX, y+childY)) new Plant(image,x+childX, y+childY, 32, 32);
    }
    reproductable = false;
}

void Plant::update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
{
    lifeTimer+=time;
    if (lifeTimer>75000) alive = false;
}

void Plant::PlantsUpdate(const float currentFrame, const float time) {
    std::list<Plant *>::iterator curr;
    /*for (curr = PlantsList.begin(); curr != PlantsList.end();) {
        if ((*curr)->alive) {
            (*curr)->nextTexture(currentFrame);
            (*curr)->update(time);
            curr++;
        } else {
            (*curr)->deathTimer += time / 2;
            sf::Uint8 gradient = 255 - (*curr)->deathTimer;
            (*curr)->sprite.setColor(Color(gradient, gradient, gradient));
            if ((*curr)->deathTimer > 255) {
                PlantsList.erase(curr);
                delete (*curr);
            } else curr++;
        }
    }*/
    for (curr = PlantsList.begin(); curr != PlantsList.end(); curr++) {
        (*curr)->nextTexture(currentFrame);
        (*curr)->update(time);
        if (!(*curr)->alive) {
            PlantsList.erase(curr);
            delete (*curr);
        }
    }
    //if (BRC != 0) std::cout << BRC << '\n';
    BRC = 0;
}