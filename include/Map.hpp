#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>

class Map : sf::Drawable {
public:
    enum Blocks {Air = 0, Border = 1};
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    void load(std::string path);
    Blocks& operator () (uint r, uint c);
private:
    std::vector<std::vector<Blocks>>map;
};

#endif //MAP_HPP