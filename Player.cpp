#include "Player.h"

Player::Player(const std::string& nom, sf::Texture& texture)
    : Nom(nom), xp(0), NbVie(3), Degats(10), isOnGround(false), textureRef(texture),
    currentFrameX(0), currentFrameY(0)
{
    SpriteSheet.setTexture(textureRef);
    IntRect = sf::IntRect(0, 0, 256, 256);
    SpriteSheet.setTextureRect(IntRect);
    

    SpriteSheet.setOrigin(128.f, 128.f); // Fix flipping issue d zb
    SpriteSheet.setPosition(100.f, 100.f);

    velocity = sf::Vector2f(0.f, 0.f);
}

void Player::Move(float deltaTime) {
    float speed = 150.f;
    velocity.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x -= speed;
        currentFrameY = 0; // walking left row
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        velocity.x += speed;
        currentFrameY = 0; // walking right row
    }

    if (velocity.x < 0)
        SpriteSheet.setScale(-1.f, 1.f);  // Flip sprite horizontally
    else if (velocity.x > 0)
        SpriteSheet.setScale(1.f, 1.f);   // Normal

    SpriteSheet.move(velocity.x * deltaTime, 0.f);
}

void Player::Jump() {
    if (isOnGround) {
        velocity.y = -425.f;
        isOnGround = false;
        currentFrameY = 0; // jumping row
    }
}

void Player::update(float deltaTime) {
    float gravity = 500.f;

    if (!isOnGround) {
        velocity.y += gravity * deltaTime;
        SpriteSheet.move(0.f, velocity.y * deltaTime);
    }
    else {
        velocity.y = 0.f;
    }

    Move(deltaTime);
    Animation(deltaTime);
}

void Player::Animation(float deltaTime) {
    static float timer = 0.f;
    timer += deltaTime;

    int maxFrames = 6;  // Default = idle

    if (velocity.x == 0 && isOnGround) {
        currentFrameY = 0; // Idle row
        maxFrames = 6;
    }
    else if (velocity.x != 0 && isOnGround) {
        currentFrameY = 1; // Walking row
        maxFrames = 8;
    }
    else if (!isOnGround) {
        currentFrameY = 2; // Jump/fall (optional: reuse run)
        maxFrames = 8;
    }

    if (timer >= 0.1f) {
        currentFrameX = (currentFrameX + 1) % maxFrames;

        IntRect.left = currentFrameX * 256;
        IntRect.top = currentFrameY * 256;

        SpriteSheet.setTextureRect(IntRect);
        timer = 0.f;
    }
}


void Player::Hit(int damage) {
    NbVie -= damage;
    if (NbVie < 0) NbVie = 0;
}

void Player::Revive() {
    NbVie = 3;
    xp = 0;
    SpriteSheet.setPosition(100.f, 100.f);
}

bool Player::IsAlive() const {
    return NbVie > 0;
}

void Player::gainXp(int amount) {
    xp += amount;
}

int Player::getDamage() const {
    return Degats + (xp / 10);
}

void Player::setIsOnGround(bool value) {
    isOnGround = value;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(SpriteSheet);
}

sf::FloatRect Player::getBounds() const {
    return SpriteSheet.getGlobalBounds();
}