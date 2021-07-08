#include "Message.hpp"
#include <iostream>

Message::Message() : text("", font) {
    loadTexture(texture, "data/characters/message.png");
    sprite.setTexture(texture);

    text.setFillColor(sf::Color::Black);
}

Message::Message(const Message &other) : time(other.time), texture(other.texture), sprite(other.sprite), text(other.text) {
    sprite.setTexture(texture);
}

void Message::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(clock.getElapsedTime().asMilliseconds() > time.asMilliseconds()) {
        activated = false;
    }
    if(activated) {
        target.draw(sprite, states);
        target.draw(text, states);
    }
}

void Message::setPosition(sf::Vector2<units> position) {
    sprite.setPosition(position.x * PIXELS_PER_UNIT, position.y * PIXELS_PER_UNIT - 64);
    text.setPosition(sprite.getPosition().x + (sprite.getLocalBounds().width - text.getLocalBounds().width) / 2,
                     sprite.getPosition().y + (sprite.getLocalBounds().height - 32 - text.getLocalBounds().height) / 2);
}

void Message::setString(std::string string) {
    text.setString(string);
    text.setCharacterSize(30);

    if(text.getLocalBounds().width > sprite.getLocalBounds().width) {
        text.setCharacterSize(sprite.getLocalBounds().width / text.getString().getSize() * 1.5);
    }
}

void Message::setTime(sf::Time time) {
    this->time = time;
}

void Message::trigger() {
    activated = true;
    clock.restart();
}