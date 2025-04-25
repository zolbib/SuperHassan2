#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(1280, 720), "Super Hassan II") {
    window.setFramerateLimit(60);

    if (!playerTexture.loadFromFile("player_spritesheet.png")) {
        std::cerr << "Failed to load player sprite!" << std::endl;
    }

    player = new Player("Arab Hero", playerTexture); // dynamically allocate

    ground.setSize(sf::Vector2f(800, 50));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(0.f, 550.f);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        float dt = clock.restart().asSeconds();
        update(dt);
        render();
    }

    delete player; // cleanup
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player->Jump();
    }
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
