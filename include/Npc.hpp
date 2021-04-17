#ifndef NPC_HPP
#define NPC_HPP

#include <fstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Entity.hpp"
#include "tools.hpp"

#include "../resources/notFound.png.hpp"

extern sf::Font font;

class Npc : public Entity {
public:
    Npc(const Npc &other);
    Npc(std::string name, uint posX, uint posY, Side side);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
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