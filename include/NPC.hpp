#ifndef NPC_HPP
#define NPC_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "tools.hpp"

#include "../resources/notFound.png.hpp"

extern sf::Font font;

class NPC : public Entity {
public:
    enum Side {Up = 'U', Down = 'D', Right = 'R', Left = 'L'};
    NPC(const NPC &other);
    NPC(std::string name, uint posX, uint posY);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void loadTexture(Side side);
    void touch();
private:
    std::string name = "NULL";

    sf::Texture texture;
    sf::Sprite sprite;
    Side side = Down;

    mutable sf::Text description;
};

#endif //NPC_HPP