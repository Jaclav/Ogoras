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
    sf::Vector2<units> getPosition();
    void touched();
private:
    std::string name;
    sf::Vector2<units> position;

    sf::Texture texture;
    sf::Sprite sprite;
    Side side;
    mutable sf::Text description;
    Message message;
};

#endif //NPC_HPP