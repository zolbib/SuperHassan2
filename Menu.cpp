
#include "Menu.h"
#include <iostream>
#include "Game.h"

Menu::Menu() {
    set_values();
}

void Menu::set_values() {
    window.create(sf::VideoMode(1280, 720), "SUPER HASSAN II", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(0, 0));

    pos = 1;
    theselect = false;

    if (!font.loadFromFile("RetroMario-Regular.otf")) {
        std::cerr << "Error loading font\n";
    }

    if (!image.loadFromFile("Menu_bg.png")) {
        std::cerr << "Error loading image\n";
    }

    bg.setTexture(image);

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = image.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    bg.setScale(scaleX, scaleY);

    options = { "Super Hassan II", "Play", "Options", "About", "Quit" };
    texts.resize(options.size());
    coords = { {540,40},{560,191},{550,282},{560,370},{570,457} };
    sizes = { 40,36,32,32,32 };

    for (size_t i = 0; i < texts.size(); ++i) {
        texts[i].setFont(font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setOutlineThickness(2);
        texts[i].setPosition(coords[i]);
        texts[i].setFillColor(sf::Color::White);
    }

    texts[pos].setOutlineThickness(4);

    winclose.setSize(sf::Vector2f(23, 26));
    winclose.setPosition(1178, 39);
    winclose.setFillColor(sf::Color::Transparent);
}

void Menu::loop_events() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Down && pos < 4) {
                texts[pos].setOutlineThickness(2);
                ++pos;
                texts[pos].setOutlineThickness(4);
                theselect = false;
            }
            else if (event.key.code == sf::Keyboard::Up && pos > 1) {
                texts[pos].setOutlineThickness(2);
                --pos;
                texts[pos].setOutlineThickness(4);
                theselect = false;
            }
            else if (event.key.code == sf::Keyboard::Enter && !theselect) {
                theselect = true;
                std::cout << "Selected: " << options[pos] << '\n';
                if (pos == 4) {
                    window.close();
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            pos_mouse = sf::Mouse::getPosition(window);
            mouse_coord = window.mapPixelToCoords(pos_mouse);
            if (winclose.getGlobalBounds().contains(mouse_coord)) {
                window.close();
            }
        }
    }
}

void Menu::draw_all() {
    window.clear();
    window.draw(bg);
    for (auto& t : texts)
        window.draw(t);
    window.display();
}

bool Menu::run_menu() {
    while (window.isOpen()) {
        loop_events();
        draw_all();

        if (theselect && pos == 1) { // "Play" selected
            window.close();
            return true;
        }
    }
    return false;
}
