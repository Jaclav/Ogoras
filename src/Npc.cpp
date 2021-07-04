#include "Npc.hpp"

Npc::Npc(const Npc &other) : name(other.name), position(other.position),
    texture(other.texture), sprite(other.sprite), side(other.side), description(other.description), message(other.message) {
    sprite.setTexture(texture);
}

Npc::Npc(int number, std::string path) : description("", font, 16) {
    config.setPath(path);
    name = config.readString("Npc" + std::to_string(number), "name", "NULL");
    if(name == "NULL")
        std::cerr << "NPC" << number << " name is NULL!\n";
    std::string sectionName = "Npc" + std::to_string(number);

    //load position
    position.x = config.readInt(sectionName, "x", 0);
    position.y = config.readInt(sectionName, "y", 0);

    //load side
    side = (Npc::Side)config.readString(sectionName, "s", "D")[0];
    this->side = side;

    //load texture and sprite
    loadTexture(texture, config.readString(sectionName, "src", sectionName));
    sprite.setTexture(texture);
    sprite.setTextureRect(setIntRect(side));
    sprite.setPosition(position.x * PIXELS_PER_UNIT, position.y * PIXELS_PER_UNIT);

    //set description
    description.setOutlineThickness(2);
	description.setString(name);

    //set message
    message.setString(config.readString(sectionName, "message", "Hey!"));
    message.setTime(sf::milliseconds((sf::Int32)config.readInt(sectionName, "messageTime", 2000)));
}

void Npc::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
    description.setPosition(sprite.getPosition().x + (sprite.getLocalBounds().width - description.getLocalBounds().width) / 2, sprite.getPosition().y - description.getLocalBounds().height);
    target.draw(description, states);
    target.draw(message, states);
}

sf::Vector2<units> Npc::getPosition() {
    return position;
}

void Npc::touched() {
    message.setPosition(position);
    message.trigger();
}
