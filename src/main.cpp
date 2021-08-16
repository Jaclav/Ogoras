#include <SFML/Graphics/RenderWindow.hpp>

#include "Game.hpp"
#include "Menu.hpp"

#include "../resources/icon.png.hpp"
#include "../resources/DejaVuSans.ttf.hpp"

sf::Font font;

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), L"Ogóras");
#ifdef _WIN32
    ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
#endif //_WIN32
    window.setFramerateLimit(60);

    sf::Image icon;
    if(!icon.loadFromMemory(icon_png, icon_png_len))
        exit(-1);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    if(!font.loadFromMemory(DejaVuSans_ttf, DejaVuSans_ttf_len))
        exit(0);

    Menu menu(window);
    Game game(window);
    static Console console(window.getSize(), game);
    while(window.isOpen()) {
        menu.start();
        if(window.isOpen())
            game.play();
    }
    return 0;
}