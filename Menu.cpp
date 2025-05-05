#include "Menu.h"
#include <iostream>
#include "Game.h"

Menu::Menu(sf::RenderWindow& win) : window(win) {
    set_values();
}

void Menu::set_values() {
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
    sizes = { 40, 36, 32, 32, 32 };

    // Responsive layout
    int spacing = 90; // space between options
    int totalHeight = spacing * (static_cast<int>(options.size()) - 1);
    int centerY = window.getSize().y / 2 - totalHeight / 2;
    int centerX = window.getSize().x / 2;

    for (size_t i = 0; i < texts.size(); ++i) {
        texts[i].setFont(font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setOutlineThickness(2);
        texts[i].setFillColor(sf::Color::White);

        // Center text origin
        sf::FloatRect textRect = texts[i].getLocalBounds();
        texts[i].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

        // Position centered
        texts[i].setPosition(centerX, centerY + static_cast<int>(i) * spacing);
    }

    texts[pos].setOutlineThickness(4);

    winclose.setSize(sf::Vector2f(23, 26));
    winclose.setPosition(window.getSize().x - 100, 39); // dynamic position for close button
    winclose.setFillColor(sf::Color::Transparent);
}

void Menu::loop_events() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            window.close();

        else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Down && pos < static_cast<int>(texts.size()) - 1) {
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
                if (pos == 4) { // "Quit" selected
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
    window.draw(winclose);
    window.display();
}

bool Menu::run_menu() {
    theselect = false; // reset selection state
    pos = 1;           // default to first option

    while (window.isOpen()) {
        loop_events();
        draw_all();

        if (theselect && pos == 1) { // "Play"
            return true; // go to game
        }
        else if (theselect && pos == 4) { // "Quit"
            window.close();
            return false;
        }
    }
    return false;
}
