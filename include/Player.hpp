#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Entity.hpp"

#include "../resources/player.png.hpp"

class Player : public Entity {
public:
    Player();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void setPosition(uint x, uint y);
    void touch();
private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif //PLAYER_HPP