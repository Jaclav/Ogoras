#include "Npc.hpp"

Npc::Npc(const Npc &other) : name(other.name), sprite(other.sprite), side(other.side), description(other.description) {
    loadTexture(side);
}

Npc::Npc(std::string name, uint posX, uint posY, Side side) {
    this->name = name;
    sprite.setPosition(posX, posY);
    this->side = side;

    description.setFont(font);
    description.setString(name);
    description.setCharacterSize(16);
    description.setOutlineThickness(2);
}

void Npc::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
    description.setPosition(sprite.getPosition().x + (sprite.getLocalBounds().width - description.getLocalBounds().width) / 2, sprite.getPosition().y - description.getLocalBounds().height);
    target.draw(description, states);
}

void Npc::loadTexture(Side side = Side::Down) {
    this->side = side;
    std::fstream file("data/characters/" + name + ".png", std::ios::in);
    if(file.good())
        texture.loadFromFile("data/characters/" + name + ".png", setIntRect(side));
    else
        texture.loadFromMemory(notFound_png, notFound_png_len);
    file.close();
    sprite.setTexture(texture);
}

void Npc::touch() {
    //what have to do when touched?
}