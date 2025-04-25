#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Player {
public:
    Player(const std::string& nom, sf::Texture& texture);
    void Move(float deltaTime);
    void Jump();
    void Animation(float deltaTime);
    void update(float deltaTime);
    void Hit(int damage);
    void Revive();
    bool IsAlive() const;
    void gainXp(int amount);
    int getDamage() const;
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void setIsOnGround(bool value);

private:
    std::string Nom;
    sf::Texture& textureRef;
    sf::Sprite SpriteSheet;
    sf::IntRect IntRect;
    sf::Vector2f velocity;
    int xp, NbVie, Degats;
    bool isOnGround;
    int currentFrameX;
    int currentFrameY;
};

