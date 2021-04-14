#ifndef NPC_HPP
#define NPC_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class NPC : public Entity {
private:
    std::string name = "NULL";

    sf::Texture texture;
    sf::Sprite sprite;
public:
    void draw(sf::RenderTarget &target, sf::RenderStates states);
    void loadTexture(std::string path);
    void touch();

    void setPosition(uint x, uint y);
    void setName(std::string name);

    //here add getters
};

#endif //NPC_HPP