#include "plant.h"
#include "map.h"
#include <iostream>

std::set<Plant*> Plant::plantsList;

void Plant::update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
{
    if (int(y / 32)<0 || int(x / 32)<0 || int(y / 32)>=HEIGHT_MAP || int(x / 32)>=WIDTH_MAP) delete this;

    switch (dir)
    {
        case 0: dx = speed; dy = 0; sprite.setRotation(90.f);  break;
        case 1: dx = -speed; dy = 0; sprite.setRotation(-90.f);  break;
        case 2: dx = 0; dy = speed; sprite.setRotation(180.f);  break;
        case 3: dx = 0; dy = -speed;  sprite.setRotation(0.f); break;
    }
    interactionWithMap();
    x += dx*time;
    y += dy*time;
    sprite.setPosition(x,y);
}

void Plant::interactionWithMap()//ф-ция взаимодействия с картой
{
    //std::cout <<
    int chanceToAvoid = rand()%20;
    if ((TileMap[int(y / 32)][int(x / 32)] == '0') && chanceToAvoid != 0)//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
    {
        if (dy>0) { dir=1; }
        if (dy<0) { dir=0; }
        if (dx>0) { dir=2; }
        if (dx < 0) { dir=3; }
    }

}