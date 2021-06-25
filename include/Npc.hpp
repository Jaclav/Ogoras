#ifndef NPC_HPP
#define NPC_HPP

#include <fstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Entity.hpp"
#include "Message.hpp"
#include "inicpp/Ini.hpp"
#include "tools.hpp"

#include "../resources/notFound.png.hpp"

extern sf::Font font;

class Npc : public Entity {
public:
    Npc(const Npc &other);
    Npc(int number, std::string path);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Vector2<units> getPosition();
    void touched();
private:
    std::string name;
    std::string path;
    sf::Vector2<units> position;

    Ini config;

    sf::Texture texture;
    sf::Sprite sprite;
    mutable sf::Text description;
    Message message;
    Side side;
};

#endif //NPC_HPP