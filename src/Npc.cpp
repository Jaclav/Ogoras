#include "Npc.hpp"

Npc::Npc(const Npc &other) : name(other.name), command(other.command), position(other.position),
    texture(other.texture), sprite(other.sprite), side(other.side), description(other.description), message(other.message) {
    sprite.setTexture(texture);
}

Npc::Npc(int number, std::string path) : description("", font, 16) {
    name = readIniString(path, "Npc" + std::to_string(number), "name", "NULL");
    std::string sectionName = "Npc" + std::to_string(number);

    //load command
    command = readIniString(path, "Npc" + std::to_string(number), "command", "NULL");

    //load position
    position.x = readIniInt(path, sectionName, "x", 0);
    position.y = readIniInt(path, sectionName, "y", 0);

    //load side
    side = (Npc::Side)readIniString(path, sectionName, "s", "D")[0];
    this->side = side;

    //load texture and sprite
    loadTexture(texture, readIniString(path, sectionName, "src", sectionName));
    sprite.setTexture(texture);
    sprite.setTextureRect(setIntRect(side));
    sprite.setPosition(position.x * PIXELS_PER_UNIT, position.y * PIXELS_PER_UNIT);

    //set description
    description.setOutlineThickness(2);
    description.setString(name);
}

void Npc::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
    description.setPosition(sprite.getPosition().x + (sprite.getLocalBounds().width - description.getLocalBounds().width) / 2, sprite.getPosition().y - description.getLocalBounds().height);
    target.draw(description, states);
    target.draw(message, states);
}

void Npc::say(sf::Time time, std::string string) {
    message.setString(string);
    message.setPosition(position);
    message.setTime(time);
    message.trigger();
}

void Npc::touched() {
    if(command != "NULL")
        Console::interpret(command);
}

sf::Vector2<units> Npc::getPosition() {
    return position;
}

void Npc::move(units x, units y) {
    position.x += x;
    position.y += y;

    if(x > 0)
        sprite.setTextureRect(setIntRect(Entity::Right));
    else if(x < 0)
        sprite.setTextureRect(setIntRect(Entity::Left));
    else if(y > 0)
        sprite.setTextureRect(setIntRect(Entity::Down));
    else if(y < 0)
        sprite.setTextureRect(setIntRect(Entity::Up));

    sprite.setPosition(position.x * PIXELS_PER_UNIT, position.y * PIXELS_PER_UNIT);
}