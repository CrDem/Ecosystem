#include "Predator.h"
#include <cmath>
#include <iostream>
#include "Herbivore.h"

std::list<Predator*> Predator::PredatorsList;

void Predator::update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
{
    lifeTimer+=time;
    //if (lifeTimer>20000) alive = false;

    dx = speed * cos(dir*3.14159265358979323846/180);
    dy = -speed * sin(dir*3.14159265358979323846/180);
    //if (dir>=0 && dir<=180)
    sprite.setRotation(90-dir);
    //if (dir>180 && dir<360) sprite.setRotation()
    x += dx*time;
    y += dy*time;
    sprite.setPosition(x,y);
    interactionWithHerbivores();
    if (hunger>1) {
        hunger = 0;
        replication();
    }
    interactionWithMap();
}

void Predator::interactionWithMap()
{
    //std::cout << "m\n";
    if (TileMap[int(y / 32)][int(x / 32)] == '3' ||
        TileMap[int(y / 32)][int(x / 32)] == '1') {
        dir = 360-dir;
        std::cout << "ya daun\n";
    }

    if (TileMap[int(y / 32)][int(x / 32)] == '0' ||
        TileMap[int(y / 32)][int(x / 32)] == '2') {
        std::cout << "neeee\n";
        if (dir>180)
            dir = 180 - dir + 360;
        else
            dir = 180 - dir;
    }
}

void Predator::interactionWithHerbivores() {
    for (Herbivore* herbivore: Herbivore::HerbivoresList) {
        if (herbivore->getRect().intersects(this->getRect())) {
            herbivore->kill();
            lifeTimer-=20000;
            hunger++;
            break;
        }
    }
}

void Predator::replication() {
    int dist = 30;
    int deg = rand()%360;
    Image image;
    image.loadFromFile("C:/Users/Anton/CLionProjects/erg/Ecosystem/textures/predator texture.png");
    int childX = dist*cos(deg), childY = dist*sin(deg);
    if (isOnMap(x+childX, y+childY)) new Predator(image,x+childX, y+childY, 32, 32);
}

void Predator::PredatorsUpdate(const float currentFrame, const float time) {
    std::list<Predator *>::iterator curr;
    for (curr = PredatorsList.begin(); curr != PredatorsList.end(); curr++) {
        (*curr)->nextTexture(currentFrame);
        (*curr)->update(time);
        if (!(*curr)->alive) {
            PredatorsList.erase(curr);
            delete (*curr);
        }
    }
}

int Predator::nearestHerbivore(float x, float y, int dir) {
    //std::cout << "initial data: " << x << ' ' << y << ' ' << dir << '\n';
    int stepVal = 8;
    for (int step = stepVal; step < 20*stepVal; step+=stepVal) {
        for (int i = dir-64; i <= dir+64; ++i) {
            int pointX = x + (step * cos(i*3.14159265358979323846/180));
            int pointY = y + (-step * sin(i*3.14159265358979323846/180));
            //std::cout << "Point " << step << " : " << pointX << ' ' << pointY << '\n';
            for (Herbivore* herbivore: Herbivore::HerbivoresList) {
                if (herbivore->getRect().contains(pointX,pointY)) {
                    return i;
                }
            }
        }
    }
    return dir;
}
