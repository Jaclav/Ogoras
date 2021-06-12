#include "Player.hpp"

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Player::move(Side side) {
    this->side = side;
    texture.loadFromMemory(player_png, player_png_len, setIntRect(side));
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
}

sf::Vector2<units> Player::getPosition() {
    return position;
}

void Player::setPositionAndSide(units x, units y, Side side) {
    position.x = x;
    position.y = y;

    texture.loadFromMemory(player_png, player_png_len, setIntRect(side));
    sprite.setTexture(texture);
    sprite.setPosition(x * PIXELS_PER_UNIT, y * PIXELS_PER_UNIT);
}