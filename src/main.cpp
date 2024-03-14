#include <SFML/Graphics.hpp>
#include <iostream>
#include "plant.h"
#include "map.h"
#include "settings.h"
#include <set>

void createPlants(int amount);

int main() {
    Image map_image;//объект изображения для карты
    map_image.loadFromFile("C:/Users/Anton/CLionProjects/erg/Ecosystem/textures/map2.png");//загружаем файл для карты
    Texture map;//текстура карты
    map.loadFromImage(map_image);//заряжаем текстуру картинкой
    Sprite s_map;//создаём спрайт для карты
    s_map.setTexture(map);//заливаем текстуру спрайтом

    sf::RenderWindow window(
    sf::VideoMode(startSettings::windowWidth, startSettings::windowHeight),
    "biocenosis");
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::Red);

    float updateDirTimer = 0;
    float CurrentFrame = 0; //хранит текущий кадр
    Clock clock;
    createPlants(startSettings::plantsAmount);

    while (window.isOpen()) {

        float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        clock.restart(); //перезагружает время
        time = time/800; //скорость игры
        updateDirTimer+=time;

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (updateDirTimer>200){
            Plant::updateDirPlants();
            updateDirTimer=0;
        }
        CurrentFrame += 0.012*time;
        if (CurrentFrame > 3) CurrentFrame -= 3;
        Plant::plantsUpdate(CurrentFrame,time);

        window.clear(Color(200,255,200));
        /////////////////////////////Рисуем карту/////////////////////
        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
                if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
                if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик


                s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

                window.draw(s_map);//рисуем квадратики на экран
            }
        /////////////////////////////////////////////////////////////////
        Plant::drawPlants(&window);
        window.display();
        //std::cout << Plant::getAmountOfPlants() << std::endl;
    }

    return 0;
}

void createPlants(int amount) {
    for (int i = 0; i < amount; ++i) {
        new Plant (rand()%(startSettings::windowWidth-64)+32,
                   rand()%(startSettings::windowHeight-64)+32,32,32);
    }
}