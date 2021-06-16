#include "Map.hpp"

Map::Map() {
    blockPositionInFile.reserve(255);

    loadTexture(texture, "data/blocks.png");
    sprite.setTexture(texture);
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(uint y = 0; y < map.size(); y++) {
        for(uint x = 0; x < map[0].size(); x++) {
            if(map[y][x] != 0 && map[y][x] != 1) {
                sprite.setTextureRect(sf::IntRect(sf::Vector2i(blockPositionInFile[map[y][x]]), sf::Vector2i(128, 128)));
                sprite.setPosition(x * PIXELS_PER_UNIT, y * PIXELS_PER_UNIT);
                target.draw(sprite, states);
            }
        }
    }

    for(uint i = 0; i < npc.size(); i++) {
        target.draw(npc[i], states);
    }
}

void Map::load(std::string path) {
    //textures of blocks
    config.setPath(path + "blocks.ini");
    uint quantity = config.getNumberOfSections();
    if(quantity > 253) {
        Console::pushMessage("Too many blocks! Maximum is 253.");
        quantity = 253;
    }
    blockPositionInFile.clear();

    for(uint i = 2; i < quantity + 2; i++) {
        blockPositionInFile[i].x = config.readInt("Block" + std::to_string(i), "x", 0);
        blockPositionInFile[i].y = config.readInt("Block" + std::to_string(i), "y", 0);
    }

    //blocks
    std::ifstream file(path + "map.lvl");
    std::string line;

    std::vector<Blocks>tmp;
    map.clear();

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
    quantity = config.getNumberOfSections();
    npc.reserve(quantity);

    for(uint i = 0; i < quantity; i++) {
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