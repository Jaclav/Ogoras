#ifndef MAP_HPP
#define MAP_HPP

#include <fstream>
#include <string>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "inicpp/Ini.hpp"
#include "Npc.hpp"
#include "tools.hpp"

class Map : public sf::Drawable {
public:
    Map();

    enum Blocks {Air = 0, Border = 1};

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void load(std::string path);
    bool shouldMove(sf::Vector2<units> position);
private:
    Ini config;

    std::vector<std::vector<Blocks>>map;
    std::vector<Npc>npc;

    sf::Sprite sprite;
    sf::Texture texture;
};

#endif //MAP_HPP