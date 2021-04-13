#include "Map.hpp"

Map::Map() {

}

Map::~Map() {

}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
}

void Map::load(uint number, const sf::RenderWindow &window) {
    if(!backgroundT.loadFromFile("data/lvl" + std::to_string(number) + "/map.png"))
        exit(0);
    background.setTexture(backgroundT);
    background.setScale(window.getSize().x / background.getLocalBounds().width,
                        window.getSize().y / background.getLocalBounds().height);
}