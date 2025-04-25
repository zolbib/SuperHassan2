#include "Menu.h"
#include "Game.h"

int main() {
    Menu menu;

    // Show the menu first
    if (menu.run_menu()) {
        Game game;
        game.run();
    }

    return 0;
}
