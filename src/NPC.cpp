#include "NPC.hpp"

NPC::NPC() {

}

NPC::NPC(std::string name, uint posX, uint posY) {
    this->name = name;
    sprite.setPosition(posX, posY);
}

void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void NPC::loadTexture(Side side) {
    sf::IntRect ir(0, 0, 128, 128);
    switch(side) {
    case Up: {
        ir.left = 0;
        break;
    }
    case Down: {
        ir.left = 128;
        break;
    }
    case Right: {
        ir.left = 256;
        break;
    }
    case Left: {
        ir.left = 384;
        break;
    }
    }
    if(!texture.loadFromFile("data/characters/" + name + ".png", ir))
        exit(0);
    sprite.setTexture(texture);
}

void NPC::touch() {
    //what have to do when touched?
}