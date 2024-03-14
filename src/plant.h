//#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <iostream>

using namespace sf;
class Plant {
private:
    static std::set<Plant*> plantsList;
public:
    Plant(float X, float Y, float W, float H){
        plantsList.insert(this);
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

    ~Plant() {
        plantsList.erase(this);
    }
    void update(float time);
    void interactionWithMap();

    static void drawPlants (sf::RenderWindow* window) {
        for (Plant* curr:plantsList) {
            window->draw(curr->sprite);
        }
    }
    static void updateDirPlants() {
        for (Plant* curr:plantsList) {
            int chance = rand()%5;
            if (chance==0) curr->updateDirTo(rand()%4);
        }
    }
    static void plantsUpdate(const float currentFrame, const float time) {
        std::cout << plantsList.size() << '\n';
        for (Plant* curr:plantsList) {
            curr->nextTexture(currentFrame);
            curr->update(time);
        }
    }
    void updateDirTo (int DIR) {
        if (DIR<0 || DIR>3) throw std::invalid_argument("net takogo direction alo");
        dir = DIR;
    }
    void nextTexture(float currentFrame) {
        sprite.setTextureRect(IntRect(32 * int(currentFrame), 0, 32, 32));
    }
    static unsigned long long int getAmountOfPlants() {
        return plantsList.size();
    };

private:
    float x, y, w, h, dx = 0, dy = 0, speed = 0.1; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
    int dir = 0;
    Image image;
    Texture texture;
    Sprite sprite;
};