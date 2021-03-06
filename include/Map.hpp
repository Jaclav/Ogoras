#ifndef MAP_HPP
#define MAP_HPP

#include <fstream>
#include <string>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Npc.hpp"
#include "tools.hpp"

class Map : public sf::Drawable {
public:
    Map();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void drawNpcs(sf::RenderTarget &target, sf::RenderStates states) const;
    void load(std::string path);
    bool shouldMove(sf::Vector2<units> position);

    void setBlock(units x, units y, Block block);
    Npc* getNpc(size_t number);

private:
    std::vector<std::vector<Block>>map;

    struct BlockProperties {
        units imageX, imageY;
        bool solid;
        int rotation;
        std::string command;
    };
    std::vector<BlockProperties>blocksProperties;

    mutable sf::Sprite sprite;
    sf::Texture texture;

    std::vector<Npc>npc;
};

#endif //MAP_HPP