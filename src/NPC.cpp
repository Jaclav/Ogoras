#include "NPC.hpp"

NPC::NPC(std::string name, uint posX, uint posY) {
    this->name = name;
    sprite.setPosition(posX, posY);

    description.setFont(font);
    description.setString(name);
    description.setCharacterSize(16);
    description.setOutlineThickness(2);
}

void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
    description.setPosition(sprite.getPosition().x + description.getLocalBounds().width, sprite.getPosition().y - description.getLocalBounds().height);
    target.draw(description, states);
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