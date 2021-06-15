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

    for(uint i = 0; i < npc.size(); i++) {
        target.draw(npc[i], states);
    }
}

void Map::load(std::string path) {
    std::ifstream file(path + "map.lvl");
    std::string line;

    std::vector<Blocks>tmp;

    while(std::getline(file, line)) {
        for(uint x = 0; x < line.size(); x++) {
            tmp.push_back((Map::Blocks)line[x]);
        }
        map.push_back(tmp);
        tmp.clear();
    }

    //npc
    config.setPath(path + "npc.ini");
    npc.clear();
    std::string name = "";
    uint quiantity = config.readInt("Npc", "quantity", 0);
    if(quiantity == 0)
        return;
    npc.reserve(quiantity);

    for(uint i = 0; i < quiantity; i++) {
        npc.push_back(Npc(i, path + "npc.ini"));//Allocate number to Npc and give path with config file
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