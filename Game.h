#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game {
public:
    Game(sf::RenderWindow& window);
    bool run();

private:

    sf::Texture playerTexture;
    sf::RenderWindow& window;


    Player* player = nullptr; // Use pointer

    sf::RectangleShape ground;
    sf::Clock clock;

    void processEvents();
    void update(float dt);
    void handleCollisions();
    void render();
};
