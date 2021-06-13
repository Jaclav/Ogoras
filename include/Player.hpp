#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Entity.hpp"
#include "tools.hpp"

#include "../resources/player.png.hpp"

class Player : public Entity {
public:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void move(Side side);

    sf::Vector2<units> getPosition();
    void setPosition(units x, units y);
    void setSide(Side side);

private:
    Side side = Side::Down;
    u_char velocity = 1;
    sf::Vector2<units> position;

    sf::Texture texture;
    sf::Sprite sprite;
};

#endif //PLAYER_HPP