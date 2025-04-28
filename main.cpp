#include "Menu.h"
#include "Game.h"

int main() {
    Menu menu;

    if (menu.run_menu()) {
        Game game;
        game.run();
    }

    return 0;
}
