#include <SFML/Graphics.hpp>

sf::View view;
float cameraSpeed = 0.2f;
float currentCameraSize = 1;
float zoomSpeed = 0.01f;

void changeView(float time, int mapWidth, int mapHeight) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        view.move(cameraSpeed*time*currentCameraSize, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        view.move(0, cameraSpeed*time*currentCameraSize);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        view.move(-cameraSpeed*time*currentCameraSize, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        view.move(0, -cameraSpeed*time*currentCameraSize);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        view.setCenter(mapWidth/2,
                       mapHeight/2);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && currentCameraSize < 1) {
        view.zoom(1 + zoomSpeed);
        currentCameraSize *= (1 + zoomSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && currentCameraSize > 0.1) {
        view.zoom(1 - zoomSpeed);
        currentCameraSize *= (1 - zoomSpeed);
    }
}