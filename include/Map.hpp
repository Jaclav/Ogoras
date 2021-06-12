#ifndef MAP_HPP
#define MAP_HPP

#include <fstream>
#include <string>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "tools.hpp"

class Map : public sf::Drawable {
public:
    enum Blocks {Air = 0, Border = 1};

    Map();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void load(std::string path);
    bool shouldMove(sf::Vector2<units> position);
private:
    std::vector<std::vector<Blocks>>map ;//what draw

    sf::Sprite sprite;
    sf::Texture texture;
};

#endif //MAP_HPP