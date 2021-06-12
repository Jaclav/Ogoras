#include "Map.hpp"

Map::Map() {
    loadTexture(texture, "data/blocks.png");
    sprite.setTexture(texture);
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(uint y = 0; y < map.size(); y++) {
        for(uint x = 0; x < map[0].size(); x++) {

        }
    }
}

void Map::load(std::string path) {
    std::ifstream file(path + "map.lvl");
    std::string line;

    while(std::getline(file, line)) {

    }
}

bool Map::shouldMove(sf::Vector2<units> position) {

}