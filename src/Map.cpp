#include "Map.hpp"

Map::Map() {
    blocksProperties.reserve(255);

    loadTexture(texture, "data/blocks.png");
    sprite.setTexture(texture);
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(uint y = 0; y < map.size(); y++) {
        for(uint x = 0; x < map[0].size(); x++) {
            if(map[y][x] != 0) {
                sprite.setTextureRect(sf::IntRect(blocksProperties[map[y][x]].imageX, blocksProperties[map[y][x]].imageY, 128, 128));
                sprite.setPosition(x * PIXELS_PER_UNIT, y * PIXELS_PER_UNIT);

                if(blocksProperties[map[y][x]].rotation != 0) {
                    sprite.setOrigin(64, 64);
                    sprite.move(64, 64);
                    sprite.setRotation(blocksProperties[map[y][x]].rotation);

                    target.draw(sprite, states);
                    sprite.setRotation(0);
                    sprite.setOrigin(0, 0);
                    continue;
                }
                target.draw(sprite, states);
            }
        }
    }
}

void Map::drawNpcs(sf::RenderTarget &target, sf::RenderStates states) const {
    for(uint i = 0; i < npc.size(); i++) {
        target.draw(npc[i], states);
    }
}

void Map::load(std::string path) {
    //blocks properties
    config.setPath(path + "blocks.ini");
    uint quantity = config.getNumberOfSections();
    if(quantity > 254) {
        Console::pushMessage("Too many blocks! Maximum is 254.");
        quantity = 254;
    }
    blocksProperties.clear();

    for(uint i = 0; i <= quantity; i++) {
        BlockProperties blockProperties{(units)config.readInt("Block" + std::to_string(i), "x", 0),
                                        (units)config.readInt("Block" + std::to_string(i), "y", 0),
                                        (bool)config.readInt("Block" + std::to_string(i), "solid", true),
                                        config.readInt("Block" + std::to_string(i), "rotation", 0),
                                        config.readString("Block" + std::to_string(i), "command", "NULL")};
        blocksProperties.push_back(blockProperties);
    }

    //blocks
    std::ifstream file(path + "map.lvl");
    std::string line;

    std::vector<Block>tmp;
    map.clear();

    while(std::getline(file, line, (char)0xff)) {
        for(uint x = 0; x < line.size(); x++) {
            tmp.push_back((Block)line[x]);
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
        Console::interpret("say I shouldn't go there!");
        return false;
    }

    if(blocksProperties[map[position.y][position.x]].command != "NULL")
        Console::interpret(blocksProperties[map[position.y][position.x]].command);

    for(uint i = 0; i < npc.size(); i++) {
        if(npc[i].getPosition() == position) {
            npc[i].touched();
            return false;
        }
    }

    if(Console::getSettings().noclip) {
        return true;
    }

    if(blocksProperties[map[position.y][position.x]].solid == false) {
        return true;
    }

    if(map[position.y][position.x] == Air) {
        return true;
    }

    return false;
}