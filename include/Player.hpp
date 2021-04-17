#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Entity.hpp"

class Player : public Entity {
public:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void touch();
private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif //PLAYER_HPP