#include "Player.hpp"

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Player::move(Side side) {
    this->side = side;
    texture.loadFromMemory(player_png, player_png_len, setIntRect(side));
    switch(side) {
    case Up:
        sprite.move(0, -velocity);
        break;
    case Down:
        sprite.move(0, velocity);
        break;
    case Right:
        sprite.move(velocity, 0);
        break;
    case Left:
        sprite.move(-velocity, 0);
        break;
    }
}

void Player::setPositionAndSide(uint x, uint y, Side side) {
    texture.loadFromMemory(player_png, player_png_len, setIntRect(side));
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}