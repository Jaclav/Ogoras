#ifndef NPC_HPP
#define NPC_HPP

#include <fstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Entity.hpp"
#include "Ini.hpp"
#include "tools.hpp"

#include "../resources/notFound.png.hpp"

extern sf::Font font;

class Npc : public Entity {
public:
    Npc(const Npc &other);
    Npc(int number, std::string path);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void touch();
private:
    std::string name;
    std::string path;

    Ini config;

    sf::Texture texture;
    sf::Sprite sprite;
    Side side;
    sf::Vector2i position;

    mutable sf::Text description;
};

#endif //NPC_HPP