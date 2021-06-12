#include "Map.hpp"

Map::Map() {
    loadTexture(texture, "data/blocks.png");
    sprite.setTexture(texture);
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {

}

void Map::load(std::string path) {

}