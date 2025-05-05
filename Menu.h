
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(sf::RenderWindow& win);
    bool run_menu();  

private:
    void set_values();
    void loop_events();
    void draw_all();

    sf::RenderWindow& window; // shared reference
    sf::Font font;
    sf::Texture image;
    sf::Sprite bg;

    std::vector<std::string> options;
    std::vector<sf::Text> texts;
    std::vector<sf::Vector2f> coords;
    std::vector<unsigned int> sizes;

    sf::RectangleShape winclose;
    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;

    int pos;
    bool theselect;
};
