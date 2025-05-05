#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& win) : window(win) {
    window.setFramerateLimit(60);

    if (!playerTexture.loadFromFile("SpritePlayer.png")) {
        std::cerr << "Failed to load player sprite!" << std::endl;
    }

    player = new Player("Arab Hero", playerTexture);

    ground.setSize(sf::Vector2f(800.f, 50.f));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(0.f, 550.f);
}

bool Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    return false; // Return to menu
                if (event.key.code == sf::Keyboard::Up ||
                    event.key.code == sf::Keyboard::W ||
                    event.key.code == sf::Keyboard::Space)
                    player->Jump();
            }
        }

        float dt = clock.restart().asSeconds();
        update(dt);
        render();
    }

    return false;
}

void Game::update(float dt) {
    player->update(dt);
    handleCollisions();
}

void Game::handleCollisions() {
    if (player->getBounds().intersects(ground.getGlobalBounds())) {
        player->setIsOnGround(true);
    }
    else {
        player->setIsOnGround(false);
    }
}

void Game::render() {
    window.clear();
    window.draw(ground);
    player->draw(window);
    window.display();
}
