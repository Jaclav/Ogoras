#include "Map.hpp"
#include <iostream>
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
    std::ifstream file(path);
    std::string line;

    std::vector<Blocks>tmp;

    while(std::getline(file, line)) {
        for(uint x = 0; x < line.size(); x++) {
            tmp.push_back((Map::Blocks)line[x]);
        }
        map.push_back(tmp);
        tmp.clear();
    }
}

bool Map::shouldMove(sf::Vector2<units> position) {
    if(position.y >= map.size() || position.x >= map[0].size()) {
        Console::pushMessage("Reference to nonexisting map's memory!");
        return false;
    }
    if(Console::getSettings().noclip) {
        return true;
    }

    if(map[position.y][position.x] == Air) {
        return true;
    }
    return false;
}