#ifndef NPC_HPP
#define NPC_HPP

#include <fstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Entity.hpp"
#include "Message.hpp"
#include "tools.hpp"

#include "../resources/notFound.png.hpp"

extern sf::Font font;

class Npc : public Entity {
public:
    Npc(const Npc &other);
    Npc(int number, std::string path);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void say(sf::Time time, std::string string);
    void touched();

    sf::Vector2<units> getPosition();
    void move(units x, units y);

private:
    std::string name, command;
    sf::Vector2<units> position;

    sf::Texture texture;
    sf::Sprite sprite;
    Side side;
    mutable sf::Text description;
    Message message;
};

#endif //NPC_HPP