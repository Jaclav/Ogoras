#ifndef MENU_HPP
#define MENU_HPP

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Button.hpp"
#include "tools.hpp"
#include "version.hpp"

#include "../resources/DejaVuSans.ttf.hpp"

extern sf::Font font;

class Menu {
public:
    Menu(sf::RenderWindow &window);
    void setDefault();
    void start();

private:
    sf::RenderWindow *window;

    sf::Event event;

    sf::Texture backgroundT;
    sf::Sprite background;

    sf::Text mainText;
    sf::Text subText;
    const std::wstring mainTextStr = L"Ogóras";
};

#endif //MENU_HPP