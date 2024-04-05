#include "Plant.h"
#include <iostream>

std::list<Plant*> Plant::PlantsList;
int Plant::BRCP;

void Plant::nextTexture(float currentFrame) {
    if (shining)
        sprite.setTextureRect(IntRect(32 * int(currentFrame/8), 0, 32, 32));

    if (reproductable) {
        if (int(currentFrame / 8) == 0) chanceToShine = rand() % 10;
        if (chanceToShine == 0 || PlantsList.size()<10) shining = true;
        else shining = false;

        if (int(currentFrame / 8) == 2 && shining) readyToProduce = true;
        if (int(currentFrame / 8) == 0 && readyToProduce) {
            if (PlantsList.size()>10) readyToProduce = false;
            if(BRCP<30) {
                replication();
                BRCP++;
            }
            shining = false;
        }
    }
}

void Plant::replication() {
    Image image;
    image.loadFromFile("C:/Users/Anton/CLionProjects/erg/Ecosystem/textures/flower texture.png");
    for (int i = 0; i < 3; ++i) {
        int dist = 30;
        if (rand()%10 == 0 || PlantsList.size() < 10) dist = rand()%1000;
        int deg = rand()%360;
        int childX = dist*cos(deg), childY = dist*sin(deg);
        if (isOnMap(x+childX, y+childY)) new Plant(image,x+childX, y+childY, 32, 32);
    }
    childrenCouter+=3;
    if(childrenCouter>=6) reproductable = false;
}

void Plant::update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
{
    lifeTimer+=time;
    if (lifeTimer>75000) alive = false;
    if (PlantsList.size() > 200)
        if (crowdCounter() > 7)
            alive = false;
    //std::cout << PlantsList.size() << '\n';
}

void Plant::PlantsUpdate(const float currentFrame, const float time) {
    bool needNew = false;
    for (Plant* curr:PlantsList) {
        if (curr->alive) {
            curr->update(time);
            curr->nextTexture(currentFrame);
        } else {
            curr->deathTimer += time / 2;
            sf::Uint8 gradient = 255 - curr->deathTimer;
            curr->sprite.setColor(Color(gradient, gradient, gradient));
            if (curr->deathTimer > 255) {
                delete curr;
                needNew = true;
                break;
            }
        }
    }
    if (needNew) { PlantsUpdate(currentFrame,time); return; }
    BRCP = 0;
}

int Plant::crowdCounter() {
    int crowd = 0;
    for (Plant* flower: Plant::PlantsList) {
        if (flower->getRect().intersects(this->getRect()) && flower->isAlive()) {
            crowd++;
        }
    }
    return crowd;
}
