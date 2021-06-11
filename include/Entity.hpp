#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

//for example NPC, player, chest

class Entity : public sf::Drawable {
public:
    enum Side {Up = 'U', Down = 'D', Right = 'R', Left = 'L'};
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};

#endif //ENTITY_HPP