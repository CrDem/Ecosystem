//#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <iostream>

using namespace sf;
class Predator {
private:
    static std::set<Predator*> PredatorsList;
public:
    Predator(float X, float Y, float W, float H){
        PredatorsList.insert(this);
        w = W; h = H;//высота и ширина
        image.loadFromFile("C:/Users/Anton/CLionProjects/erg/Ecosystem/textures/predator texture.png");
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        //sprite.setColor(Color(100,100,255));//заливаем спрайт цветом

        x = X; y = Y;//координата появления спрайта
        sprite.setTextureRect(IntRect(0, 0, w, h));
        sprite.setOrigin(16,16);
        sprite.setPosition(x,y);
        //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу.
        //IntRect - приведение типов
    }

    ~Predator() {
        PredatorsList.erase(this);
    }
    void update(float time);
    void interactionWithMap();

    static void drawPredators (sf::RenderWindow* window) {
        for (Predator* curr:PredatorsList) {
            window->draw(curr->sprite);
        }
    }
    static void updateDirPredators() {
        for (Predator* curr:PredatorsList) {
            int chance = rand()%5;
            if (chance==0) curr->updateDirTo(rand()%4);
        }
    }
    static void PredatorsUpdate(const float currentFrame, const float time) {
        //std::cout << PredatorsList.size() << '\n';
        for (Predator* curr:PredatorsList) {
            curr->nextTexture(currentFrame);
            curr->update(time);
        }
    }
    void updateDirTo (int DIR) {
        if (DIR<0 || DIR>3) throw std::invalid_argument("net takogo direction alo");
        dir = DIR;
    }
    void nextTexture(float currentFrame) {
        std::cout << (int(currentFrame)%3) << '\n';
        sprite.setTextureRect(IntRect(32 * (int(currentFrame)%3), 0, 32, 32));
    }
    static unsigned long long int getAmountOfPredators() {
        return PredatorsList.size();
    };

private:
    float x, y, w, h, dx = 0, dy = 0, speed = 0.1; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
    int dir = 0;
    Image image;
    Texture texture;
    Sprite sprite;
};