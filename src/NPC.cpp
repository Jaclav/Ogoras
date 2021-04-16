#include "NPC.hpp"
#include <iostream>

NPC::NPC(const NPC &other) : name(other.name), sprite(other.sprite), side(other.side), description(other.description) {
    loadTexture(side);
    std::cout << name << '\n';
}

NPC::NPC(std::string name, uint posX, uint posY, Side side) {
    this->name = name;
    sprite.setPosition(posX, posY);
    this->side = side;

    description.setFont(font);
    description.setString(name);
    description.setCharacterSize(16);
    description.setOutlineThickness(2);
}

void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
    description.setPosition(sprite.getPosition().x + (sprite.getLocalBounds().width - description.getLocalBounds().width) / 2, sprite.getPosition().y - description.getLocalBounds().height);
    target.draw(description, states);
}

void NPC::loadTexture(Side side = Side::Down) {
    sf::IntRect ir(0, 0, 128, 128);
    this->side = side;
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
    std::fstream file("data/characters/" + name + ".png", std::ios::in);
    if(file.good())
        texture.loadFromFile("data/characters/" + name + ".png", ir);
    else
        texture.loadFromMemory(notFound_png, notFound_png_len);
    file.close();
    sprite.setTexture(texture);
}

void NPC::touch() {
    //what have to do when touched?
}