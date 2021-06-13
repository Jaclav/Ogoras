#include "Player.hpp"

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Player::move(Side side) {
    this->side = side;
    sprite.setTextureRect(setIntRect(side));
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

void Player::setPosition(units x, units y) {
    position.x = x;
    position.y = y;

    texture.loadFromMemory(player_png, player_png_len);
    sprite.setTexture(texture);
    sprite.setTextureRect(setIntRect(side));
    sprite.setPosition(x * PIXELS_PER_UNIT, y * PIXELS_PER_UNIT);
}

void Player::setSide(Side side) {
    sprite.setTextureRect(setIntRect(side));
}