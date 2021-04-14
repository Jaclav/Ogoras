#include "NPC.hpp"

void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void NPC::loadTexture(std::string path) {
    path += ".png";
    if(!texture.loadFromFile(path))
        exit(0);
    sprite.setTexture(texture);
}

void NPC::touch() {
    //what have to do when touched?
}

void NPC::setPosition(uint x, uint y) {
    sprite.setPosition(x, y);
}
void NPC::setName(std::string name) {
    this->name = name;
}