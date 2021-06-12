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
    void setPositionAndSide(uint x, uint y, Side side);
private:
    sf::Texture texture;
    sf::Sprite sprite;
    Side side;
    u_char velocity = 1;
};

#endif //PLAYER_HPP