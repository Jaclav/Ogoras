#include "Map.hpp"

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {

}

Map::Blocks& Map::operator () (uint r, uint c) {
    return map[r][c];
}