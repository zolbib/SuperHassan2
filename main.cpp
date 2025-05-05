#include "Menu.h"
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Super Hassan II");
    Menu menu(window);
    Game game(window);

    // Show the menu first
    if (menu.run_menu()) {
        
        game.run();
    }

    return 0;
}
