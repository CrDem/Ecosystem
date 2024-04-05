#pragma once
#include <SFML/Graphics.hpp>

class Creature{
public:
    Creature(sf::Image& image,float X, float Y, float W, float H){
        w = W; h = H;
        x = X; y = Y;
        alive = true; reproductable = true; ableToMove = true;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }
    sf::IntRect getRect() {
        return sf::IntRect(x,y,w,h);
    }
    bool isAlive() {return alive;}
    void kill() {alive = false;}
    float getX() const {return x;}
    float getY() const {return y;}
protected:
    bool alive, reproductable, ableToMove;
    float x, y, w, h, lifeTimer{0}, deathTimer{0}, digestionTimer{0};
    sf::Texture texture;
    sf::Sprite sprite;
};
