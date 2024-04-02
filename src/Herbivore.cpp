#include "Herbivore.h"
#include <iostream>
#include "plant.h"

std::list<Herbivore*> Herbivore::HerbivoresList;

void Herbivore::update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
{
    lifeTimer+=time;
    //if (lifeTimer>100000) alive = false;
    switch (dir)
    {
        case 0: dx = speed; dy = 0; break;
        case 1: dx = -speed; dy = 0; break;
        case 2: dx = 0; dy = speed; break;
        case 3: dx = 0; dy = -speed; break;
    }
    x += dx*time;
    y += dy*time;
    sprite.setPosition(x,y);
    interactionWithFlowers();
    if (hunger>3) {
        hunger = 0;
        replication();
    }
    interactionWithMap();
}

void Herbivore::interactionWithMap()//ф-ция взаимодействия с картой
{
    if (TileMap[int(y / 32)][int(x / 32)] == '0' ||
            TileMap[int(y / 32)][int(x / 32)] == '1' ||
            TileMap[int(y / 32)][int(x / 32)] == '2' ||
            TileMap[int(y / 32)][int(x / 32)] == '3')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
    {
        if (dy>0 && y>HEIGHT_MAP*16) { dir=3; }
        if (dy<0 && y<HEIGHT_MAP*16) { dir=2; }
        if (dx>0 && x>WIDTH_MAP*16) { dir=1; }
        if (dx<0 && x<WIDTH_MAP*16) { dir=0; }
    }
}

void Herbivore::interactionWithFlowers() {
    for (Plant* flower: Plant::PlantsList) {
        if (flower->getRect().intersects(this->getRect()) && flower->isAlive()) {
            flower->kill();
            hunger++;
            break;
        }
    }
}

void Herbivore::replication() {
    int dist = 30;
    int deg = rand()%360;
    Image image;
    image.loadFromFile("C:/Users/Anton/CLionProjects/erg/Ecosystem/textures/herbivore texture.png");
    int childX = dist*cos(deg), childY = dist*sin(deg);
    if (isOnMap(x+childX, y+childY)) new Herbivore(image,x+childX, y+childY, 32, 32);
}

void Herbivore::HerbivoresUpdate(const float currentFrame, const float time) {
    std::list<Herbivore *>::iterator curr;
    for (curr = HerbivoresList.begin(); curr != HerbivoresList.end(); curr++) {
        (*curr)->nextTexture(currentFrame);
        (*curr)->update(time);
        if (!(*curr)->alive) {
            HerbivoresList.erase(curr);
            delete (*curr);
        }
    }
}
