#pragma once
#include <SFML/Graphics.hpp>
#include "map.h"

class Creature{
public:
    Creature(sf::Image& image,float X, float Y, float W, float H){
        w = W; h = H; //высота и ширина
        x = X; y = Y; //координата появления спрайта
        alive = true; reproductable = true;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }
    sf::IntRect getRect() {
        return sf::IntRect(x,y,w,h);
    }
    bool isOnMap(int x, int y) {
        return (x>32 && y>32 && x<(WIDTH_MAP-1)*32 && y<(HEIGHT_MAP-1)*32);
    }
    bool isAlive() {return alive;}
    void kill() {alive = false;}
protected:
    bool alive, reproductable;
    float x, y, w, h, lifeTimer{0}, deathTimer{0};
    sf::Texture texture;
    sf::Sprite sprite;
};
