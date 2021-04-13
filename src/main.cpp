#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Menu.hpp"

#include "../resources/icon.png.hpp"

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), L"Ogóras");
    window.setFramerateLimit(60);

    sf::Image icon;
    if(!icon.loadFromMemory(icon_png, icon_png_len))
        exit(-1);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Menu menu(window);
    while(window.isOpen()) {
        menu.start(window);
        if(menu.shouldPlay) {
            Game game(window);
            menu.shouldPlay = false;
        }
    }
    return 0;
}