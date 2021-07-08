#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Entity.hpp"
#include "Message.hpp"
#include "tools.hpp"

class Player : public Entity {
public:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void load(std::string path);
    void move(Side side);

    sf::Vector2<units> getPosition();
    void setPosition(units x, units y);
    void setSide(Side side);

    void say(sf::Time time, std::string string);

private:
    Side side = Side::Down;
    u_char velocity = 1;
    sf::Vector2<units> position;

    sf::Texture texture;
    sf::Sprite sprite;

    Message message;
};

#endif //PLAYER_HPP