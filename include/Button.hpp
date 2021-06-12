#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <iostream>
#include <functional>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

#include "tools.hpp"

#include "../resources/DejaVuSans.ttf.hpp"

extern sf::Font font;

class Button : public sf::Drawable {
public:
    Button(int x, int y, int width, int height, std::string str, std::function<void(void)> function);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool isCovering() const;

private:
    mutable sf::RectangleShape rect;

    std::function<void( void )> function;

    sf::Text text;
    const sf::Color defaultColor{128, 128, 128, 220};
    const sf::Color activateColor{0, 0, 255, 122};
};

#endif //BUTTON_HPP