#ifndef NPC_HPP
#define NPC_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class NPC : public Entity {
private:
    sf::Texture texture;
    sf::Sprite sprite;
public:
    void draw(sf::RenderTarget &target, sf::RenderStates states);
    void loadTexture(std::string path);
    void setPosition(uint x, uint y);
    void touch();
};

#endif //NPC_HPP