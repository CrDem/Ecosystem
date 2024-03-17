#include <SFML/Graphics.hpp>
#include <set>
#include <iostream>

using namespace sf;
class Plant {
private:
    static std::set<Plant*> PlantsList;
public:
    Plant(float X, float Y, float W, float H){
        PlantsList.insert(this);
        w = W; h = H;//высота и ширина
        shining = false;
        image.loadFromFile("C:/Users/Anton/CLionProjects/erg/Ecosystem/textures/flower texture.png");
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        //sprite.setColor(Color(100,100,255));//заливаем спрайт цветом

        x = X; y = Y;//координата появления спрайта
        sprite.setTextureRect(IntRect(0, 0, w, h));
        sprite.setOrigin(16,32);
        sprite.setPosition(x,y);
        //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу.
        //IntRect - приведение типов
    }

    ~Plant() {
        PlantsList.erase(this);
    }
    //void update(float time);
    //void interactionWithMap();

    static void drawPlants (sf::RenderWindow* window) {
        for (Plant* curr:PlantsList) {
            window->draw(curr->sprite);
        }
    }
    static void PlantsUpdate(const float currentFrame, const float time) {
        //std::cout << PlantsList.size() << '\n';
        for (Plant* curr:PlantsList) {
            curr->nextTexture(currentFrame);
            //curr->update(time);
        }
    }
    void nextTexture(float currentFrame) {
        if (shining)
            sprite.setTextureRect(IntRect(32 * int(currentFrame/8), 0, 32, 32));
        if (int(currentFrame/8)==0) chanceToShine = rand()%10;
        if (chanceToShine==0) shining = true;
        else shining = false;
    }
    static unsigned long long int getAmountOfPlants() {
        return PlantsList.size();
    };

private:
    float x, y, w, h; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
    bool shining;
    int chanceToShine = -1;
    Image image;
    Texture texture;
    Sprite sprite;
};