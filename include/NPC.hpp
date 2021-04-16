#ifndef NPC_HPP
#define NPC_HPP

#include <fstream>

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "tools.hpp"

#include "../resources/notFound.png.hpp"

extern sf::Font font;

class NPC : public Entity {
public:
    NPC(const NPC &other);
    NPC(std::string name, uint posX, uint posY, Side side);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void loadTexture(Side side);
    void touch();
private:
    std::string name;

    sf::Texture texture;
    sf::Sprite sprite;
    Side side;

    mutable sf::Text description;
};

#endif //NPC_HPP