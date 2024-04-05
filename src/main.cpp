#include <SFML/Graphics.hpp>
#include <iostream>
#include "camera.h"
#include "Plant.h"
#include "Herbivore.h"
#include "Predator.h"
#include "settings.h"
#include <set>

void createPredators(int amount);
void createHerbivores(int amount);
void createPlants(int amount);

int main() {
    Image map_image;
    map_image.loadFromFile("C:/Users/Anton/CLionProjects/erg/Ecosystem/textures/map3.png");
    Texture map;
    map.loadFromImage(map_image);
    Sprite s_map;
    s_map.setTexture(map);

    sf::RenderWindow window(
    sf::VideoMode(startSettings::windowWidth, startSettings::windowHeight),
    "biocenosis",sf::Style::Fullscreen);

    float updateDirTimer = 0;
    float CurrentFrame = 0; //хранит текущий кадр
    Clock clock;
    view.reset(sf::FloatRect(0, 0,
                             startSettings::windowWidth, startSettings::windowHeight));
    createPlants(startSettings::PlantsAmount);
    createHerbivores(startSettings::HerbivoresAmount);
    createPredators(startSettings::PredatorsAmount);

    while (window.isOpen()) {

        float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        clock.restart(); //перезагружает время
        time = time/(3200/startSettings::gameSpeedLvl); //скорость игры
        updateDirTimer+=time;

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        if (updateDirTimer>200){
            Predator::updateDirPredators();
            Herbivore::updateDirHerbivores();
            updateDirTimer=0;
        }
        CurrentFrame += 0.012*time;
        if (CurrentFrame > 24) CurrentFrame -= 24;
        Plant::PlantsUpdate(CurrentFrame,time);
        Herbivore::HerbivoresUpdate(CurrentFrame,time);
        Predator::PredatorsUpdate(CurrentFrame,time);

        window.setView(view);
        window.clear(Color(200,255,200));
        //window.clear(Color(0,0,0));
        /////////////////////////////Рисуем карту/////////////////////
        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
                if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
                if (TileMap[i][j] == '0' ||
                    TileMap[i][j] == '1' ||
                    TileMap[i][j] == '2' ||
                    TileMap[i][j] == '3') s_map.setTextureRect(IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик


                s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

                window.draw(s_map);//рисуем квадратики на экран
            }
        /////////////////////////////////////////////////////////////////
        Plant::drawPlants(&window);
        Herbivore::drawHerbivores(&window);
        Predator::drawPredators(&window);
        changeView(time, startSettings::windowWidth, startSettings::windowHeight);
        window.display();
    }

    return 0;
}

void createPredators(int amount) {
    Image image;
    image.loadFromFile("C:/Users/Anton/CLionProjects/erg/Ecosystem/textures/predator texture.png");
    for (int i = 0; i < amount; ++i) {
        new Predator (image,rand()%(startSettings::windowWidth-128)+64, //64 32
                   rand()%(startSettings::windowHeight-128)+64,32,32);
    }
}

void createHerbivores(int amount) {
    Image image;
    image.loadFromFile("C:/Users/Anton/CLionProjects/erg/Ecosystem/textures/herbivore texture.png");
    for (int i = 0; i < amount; ++i) {
        new Herbivore (image,rand()%(startSettings::windowWidth-128)+64, //64 32
                      rand()%(startSettings::windowHeight-128)+64,19,19);
    }
}

void createPlants(int amount) {
    Image image;
    image.loadFromFile("C:/Users/Anton/CLionProjects/erg/Ecosystem/textures/flower texture.png");
    for (int i = 0; i < amount; ++i) {
        new Plant (image,rand()%(startSettings::windowWidth-128)+64, //64 32
                      rand()%(startSettings::windowHeight-128)+64,32,32);
    }
}