#include "Npc.hpp"

Npc::Npc(const Npc &other) : name(other.name), texture(other.texture), sprite(other.sprite), side(other.side), description(other.description) {
    sprite.setTexture(texture);
}

Npc::Npc(int number, std::string path) {
    config.setPath(path);
    name = config.readString("Npc" + std::to_string(number), "name", "NULL");
    if(name == "NULL")
        std::cerr << "NPC" << number << " name is NULL!\n";

    //load position
    position.x = config.readInt("Npc" + std::to_string(number), "x", 0);
    position.y = config.readInt("Npc" + std::to_string(number), "y", 0);

    //load side
    side = (Npc::Side)config.readString("Npc" + std::to_string(number), "s", "D")[0];
    this->side = side;

    //load and set texture
    std::fstream file("data/characters/" + name + ".png", std::ios::in);
    if(file.good())
        texture.loadFromFile("data/characters/" + name + ".png", setIntRect(side));
    else
        texture.loadFromMemory(notFound_png, notFound_png_len);
    file.close();
    sprite.setTexture(texture);
    sprite.setPosition(position.x, position.y);

    //set description
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

void Npc::touch() {
    //what have to do when touched?
}