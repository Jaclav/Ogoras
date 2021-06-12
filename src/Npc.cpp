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

    loadTexture(texture, "data/characters/" + name + ".png");
    sprite.setTexture(texture);
    sprite.setTextureRect(setIntRect(side));
    sprite.setPosition(position.x * PIXELS_PER_UNIT, position.y * PIXELS_PER_UNIT);

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
    //TODO add in touch dialogs
}