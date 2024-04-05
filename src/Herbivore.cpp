#include "Herbivore.h"
#include <iostream>
#include "plant.h"

std::list<Herbivore*> Herbivore::HerbivoresList;
int Herbivore::BRCH;

void Herbivore::update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
{
    lifeTimer+=time;
    if (lifeTimer>5000) {
        int chanceToDie = rand()%(int(70000000/lifeTimer));
        if (chanceToDie == 0) alive = false;
    }

    if (HerbivoresList.size()>35 && rand()%(70000/HerbivoresList.size()) == 0) alive = false;

    if (!ableToMove) {
        digestionTimer+=time;
        if (digestionTimer > 1000) { ableToMove = true; }
        return;
    }

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

    if (int(y / 32)<0 || int(x / 32)<0 || int(y / 32)>=HEIGHT_MAP || int(x / 32)>=WIDTH_MAP) {
        alive = false;
        return;
    }

    interactionWithFlowers();
    if (hunger>2 and BRCH < 20 and HerbivoresList.size() < 70) {
        hunger = 0;
        BRCH++;
        replication(false);
    }
    interactionWithMap();
}

void Herbivore::interactionWithMap() //ф-ция взаимодействия с картой
{
    if (TileMap[int(y / 32)][int(x / 32)] == '0' ||
            TileMap[int(y / 32)][int(x / 32)] == '1' ||
            TileMap[int(y / 32)][int(x / 32)] == '2' ||
            TileMap[int(y / 32)][int(x / 32)] == '3')
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
            lifeTimer+=4000;
            shining = true;
            digestionTimer = 0;
            ableToMove = false;
            break;
        }
    }
}

void Herbivore::replication(bool distanceReplication) {
    int dist = 30;
    int deg = rand()%360;
    if (rand()%7 == 0) distanceReplication = true;
    Image image;
    image.loadFromFile("C:/Users/Anton/CLionProjects/erg/Ecosystem/textures/herbivore texture.png");
    if (distanceReplication) dist = rand()%1000;
    int childX = dist*cos(deg), childY = dist*sin(deg);
    if (isOnMap(x+childX, y+childY)) new Herbivore(image,x+childX, y+childY, 19, 19);
    else replication(distanceReplication);
}

void Herbivore::HerbivoresUpdate(const float currentFrame, const float time) {
    bool needNew = false;
    for (Herbivore* curr:HerbivoresList) {
        if (curr->alive) {
            curr->nextTexture(currentFrame);
            curr->update(time);
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
    if (needNew) { HerbivoresUpdate(currentFrame,time); return; }
    BRCH = 0;
}

int Herbivore::nearestPlant(float x, float y, int dir) {
    //std::cout << "initial data: " << x << ' ' << y << ' ' << dir << '\n';
    int stepVal = 16;
    for (int step = stepVal; step < 30*stepVal; step+=stepVal) {

        int pointX = x + step; int pointY = y;
        for (Plant* Plant: Plant::PlantsList) {
            if (Plant->getRect().contains(pointX,pointY)) { return 0; }
        }

        pointX = x; pointY = y + step;
        for (Plant* Plant: Plant::PlantsList) {
            if (Plant->getRect().contains(pointX,pointY)) { return 2; }
        }

        pointX = x - step; pointY = y;
        for (Plant* Plant: Plant::PlantsList) {
            if (Plant->getRect().contains(pointX,pointY)) { return 1; }
        }

        pointX = x; pointY = y - step;
        for (Plant* Plant: Plant::PlantsList) {
            if (Plant->getRect().contains(pointX,pointY)) { return 3; }
        }
    }
    if(rand()%5 == 0) return rand()%4;
    return dir;
}

void Herbivore::nextTexture(float currentFrame) {
    if (shining) sprite.setTextureRect(IntRect(32 * (int(currentFrame)/6), 0, 32, 32));
    if (int(currentFrame / 6) > 0 && shining) stopShining = true;
    if (int(currentFrame / 6) == 0 && stopShining) { shining = false; stopShining = false; }
}
