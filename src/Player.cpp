#include "Player.hpp"

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Player::setPositionAndSide(uint x, uint y, Side side) {
    texture.loadFromMemory(player_png, player_png_len, setIntRect(side));
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Player::touch() {

}