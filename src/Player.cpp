#include "Player.hpp"

Player::Player() {
    texture.loadFromMemory(player_png, player_png_len);
    sprite.setTexture(texture);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Player::setPosition(uint x, uint y) {
    sprite.setPosition(x, y);
}

void Player::touch() {

}