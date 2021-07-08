#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "tools.hpp"

class Message : public sf::Drawable {
public:
    Message();
    Message(const Message &other);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setPosition(sf::Vector2<units> position);// must be call after setString
    void setString(std::string string);
    void setTime(sf::Time time);
    void trigger();

private:
    mutable bool activated = false;
    sf::Time time;
    sf::Clock clock;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::Text text;
};
#endif //MESSAGE_HPP