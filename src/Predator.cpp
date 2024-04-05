#include "Predator.h"
#include <cmath>
#include <iostream>
#include "Herbivore.h"

std::list<Predator*> Predator::PredatorsList;
int Predator::BRCR;

void Predator::update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
{
    lifeTimer+=time;
    if (lifeTimer>10000) {
        if (rand()%(int(100000000/lifeTimer)) == 0
        && PredatorsList.size()>4) alive = false;
        if (rand()%(int(10000000000/lifeTimer)) == 0
        && PredatorsList.size()<=4) alive = false;
    }

    if ((PredatorsList.size()>13 && rand()%(13000/PredatorsList.size()) == 0) ||
        (PredatorsList.size()>8 &&
        (Herbivore::HerbivoresList.size() / PredatorsList.size()) <= 1
        && rand()%(100) == 0)) alive = false;

    if (!ableToMove) {
        digestionTimer+=time;
        if (digestionTimer > 1000) ableToMove = true;
        return;
    }

    dx = speed * cos(dir*3.14159265358979323846/180);
    dy = -speed * sin(dir*3.14159265358979323846/180);
    sprite.setRotation(90-dir);
    x += dx*time;
    y += dy*time;
    sprite.setPosition(x,y);
    if (int(y / 32)<0 || int(x / 32)<0 || int(y / 32)>=HEIGHT_MAP || int(x / 32)>=WIDTH_MAP) {
        alive = false;
        return;
    }
    interactionWithHerbivores();
    if (hunger>1 && BRCR<10 && PredatorsList.size()<40) {
        hunger = 0;
        BRCR++;
        replication();
    }
    interactionWithMap();
}

void Predator::interactionWithMap()
{
    if (!alive) return;
    if (TileMap[int(y / 32)][int(x / 32)] == '3' ||
        TileMap[int(y / 32)][int(x / 32)] == '1') {
        dir = 360-dir;
    }

    if (TileMap[int(y / 32)][int(x / 32)] == '0' ||
        TileMap[int(y / 32)][int(x / 32)] == '2') {
        if (dir>180)
            dir = 180 - dir + 360;
        else
            dir = 180 - dir;
    }
}

void Predator::interactionWithHerbivores() {
    for (Herbivore* herbivore: Herbivore::HerbivoresList) {
        if (herbivore->getRect().intersects(this->getRect()) && herbivore->isAlive()) {
            herbivore->kill();
            lifeTimer+=5500;
            hunger++;
            digestionTimer = 0;
            x = herbivore->getX(); y = herbivore->getY();
            sprite.setPosition(x,y);
            ableToMove = false;
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
    //std::list<Predator *>::iterator curr;
    bool needNew = false;
    for (Predator* curr:PredatorsList) {
        curr->nextTexture(currentFrame);
        curr->update(time);
        if (!curr->alive) {
            //PredatorsList.erase(curr);
            delete curr;
            needNew = true;
            break;
        }
    }
    if (needNew) { PredatorsUpdate(currentFrame,time); return; }
    BRCR = 0;
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
