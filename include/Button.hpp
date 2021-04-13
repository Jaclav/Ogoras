#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <iostream>
#include <functional>

#include <SFML/Graphics.hpp>

#include "tools.hpp"

#include "../resources/DejaVuSans.ttf.hpp"

class Button : public sf::Drawable {
    mutable sf::RectangleShape rect;

    std::function<void( void )> function;

    sf::Font font;
    sf::Text text;
    const sf::Color defaultColor{128, 128, 129, 220};
    const sf::Color activateColor{0, 0, 255, 122};
public:
    Button(int x, int y, int width, int height, std::string str, std::function<void(void)> function);
    ~Button();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool isCovering() const;
};

#endif //BUTTON_HPP