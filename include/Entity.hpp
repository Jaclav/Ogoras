#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

//for example NPC, player, chest

class Entity : public sf::Drawable {
public:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    virtual void setPosition(uint x, uint y) = 0;
    virtual void touch() = 0;
};

#endif //ENTITY_HPP