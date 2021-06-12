#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>

#include "tools.hpp"

class Map : sf::Drawable {
public:
    enum Blocks {Air = 0, Border = 1};
    void draw(sf::RenderTarget &target, sf::RenderStates states);
    void load(std::string path);
    Blocks& operator () (uint r, uint c);
private:
    std::vector<std::vector<Blocks>>map ;//what draw
};

#endif //MAP_HPP