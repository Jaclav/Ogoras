#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

#include "Button.hpp"
#include "tools.hpp"
#include "version.hpp"

#include "../resources/backgrounds/startBackground.png.hpp"
#include "../resources/DejaVuSans.ttf.hpp"

extern sf::Font font;

class Menu {
    enum Returned {Back, Play};
    Returned play(sf::RenderWindow &window);

    sf::Event event;

    sf::Texture backgroundT;
    sf::Sprite background;

    sf::Text mainText;
    sf::Text subText;
    const std::wstring mainTextStr = L"Ogóras";
public:
    Menu(sf::RenderWindow &window);
    ~Menu();
    void setDefault(sf::RenderWindow &window);
    void start(sf::RenderWindow &window);
    void stop(sf::RenderWindow &window);

    bool shouldPlay = false;
};

#endif //MENU_HPP