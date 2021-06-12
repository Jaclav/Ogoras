#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>
#include <utility>
#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Clipboard.hpp>
#include <SFML/Window/Event.hpp>

#include "tools.hpp"

extern sf::Font font;

class Console : public sf::Drawable {
public:
    Console(sf::Vector2u windowSize);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void handleEvent(sf::Event &event);
    void static pushMessage(std::string message);

private:
    bool activated = false;

    static sf::RectangleShape background;

    static std::string previousString;
    static sf::Text previousText;
    static std::string typedString;
    static sf::Text typedText;
};

#endif //CONSOLE_HPP