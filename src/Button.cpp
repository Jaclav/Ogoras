#include "Button.hpp"

Button::Button(int x, int y, int width, int height, std::string str, std::function<void(void)> function) {
    rect.setPosition(x, y);
    rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(defaultColor);
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(3);

    this->function = function;

    text.setFont(font);
    text.setString(str);

    while(text.getLocalBounds().width > width || text.getLocalBounds().height > height) {
        text.setCharacterSize(text.getCharacterSize() - 1);
    }
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    text.setPosition(x + (width - text.getLocalBounds().width) / 2, y + (height - text.getLocalBounds().height * 1.2) / 2);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rect, states);
    target.draw(text, states);

    if(isCovering()) {
        rect.setFillColor(activateColor);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            function();
    }
    else {
        rect.setFillColor(defaultColor);
    }
}

bool Button::isCovering() const {
    return isMouseCovering(rect.getPosition(), rect.getSize());
}