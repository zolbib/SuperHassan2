#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Texture playerTexture;
    Player* player = nullptr; // Use pointer

    sf::RectangleShape ground;
    sf::Clock clock;

    void processEvents();
    void update(float dt);
    void handleCollisions();
    void render();
};
