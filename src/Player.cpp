#include "Player.hpp"

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
    target.draw(message, states);
}

void Player::load(std::string path) {
    setPosition(readIniInt(path + "config.ini", "Player", "x", 0),
                readIniInt(path + "config.ini", "Player", "y", 0));
    setSide((Side)readIniString(path + "config.ini", "Player", "s", "D")[0]);

    sprite.loadFromFile(readIniString(path + "config.ini", "Player", "src", "data/characters/player.png"), sf::Vector2i(PIXELS_PER_UNIT, PIXELS_PER_UNIT));
    setSide(side);
    sprite.setPeriod(sf::milliseconds(readIniInt(readIniString(path + "config.ini", "Player", "src", "data/characters/player.png") + ".ini", "", "period", 0)));
}

void Player::move(Side side) {
    setSide(side);
    switch(side) {
    case Up:
        sprite.move(0, -velocity * PIXELS_PER_UNIT);
        position.y -= 1;
        break;
    case Down:
        sprite.move(0, velocity * PIXELS_PER_UNIT);
        position.y += 1;
        break;
    case Right:
        sprite.move(velocity * PIXELS_PER_UNIT, 0);
        position.x += 1;
        break;
    case Left:
        sprite.move(-velocity * PIXELS_PER_UNIT, 0);
        position.x -= 1;
        break;
    }
    message.setPosition(position);
}

sf::Vector2<units> Player::getPosition() {
    return position;
}

void Player::setPosition(units x, units y) {
    position.x = x;
    position.y = y;

    sprite.setPosition(x * PIXELS_PER_UNIT, y * PIXELS_PER_UNIT);
}

void Player::setSide(Side side) {
    this->side = side;

    switch(side) {
    case Up:
        sprite.setFrameY(0);
        break;
    case Down:
        sprite.setFrameY(PIXELS_PER_UNIT);
        break;
    case Right:
        sprite.setFrameY(PIXELS_PER_UNIT * 2);
        break;
    case Left:
        sprite.setFrameY(PIXELS_PER_UNIT * 3);
        break;
    }

}

void Player::say(sf::Time time, std::string string) {
    message.setString(string);
    message.setPosition(position);
    message.setTime(time);
    message.trigger();
}