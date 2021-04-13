#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>

#include "Ini.hpp"

class Map : public sf::Drawable {
    sf::Texture backgroundT;
    sf::Sprite background;

    Ini config;
public:
    Map();
    ~Map();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void load(uint number, const sf::RenderWindow &window);
};

#endif //MAP_HPP