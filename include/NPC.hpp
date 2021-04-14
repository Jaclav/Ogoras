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
    enum Side {Up = 'U', Down = 'D', Right = 'R', Left = 'L'};
    NPC();
    NPC(std::string name, uint posX, uint posY);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void loadTexture(Side side);
    void touch();
};

#endif //NPC_HPP