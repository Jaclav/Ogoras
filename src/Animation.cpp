#include "Animation.hpp"

Animation::Animation() {

}

Animation::Animation(const Animation &other) : texture(other.texture), sprite(other.sprite), frameY(other.frameY), frameSize(other.frameSize), period(other.period) {

}

void Animation::draw(sf::RenderTarget &target, sf::RenderStates states)const {
    if(clock.getElapsedTime() >= period) {
        sprite.setTextureRect(sf::IntRect((sprite.getTextureRect().left + frameSize.x) % texture.getSize().x,
                                          frameY,
                                          frameSize.x, frameSize.y));
        clock.restart();
    }
    target.draw(sprite, states);
}

void Animation::loadFromFile(std::string path, sf::Vector2i frameSize) {
    this->frameSize = frameSize;
    loadTexture(texture, path);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), frameSize));
}

void Animation::move(int x, int y) {
    sprite.move(x, y);
}

void Animation::setFrameY(int frameY) {
    this->frameY = frameY;
    sprite.setTextureRect(sf::IntRect(sprite.getTextureRect().left,
                                      frameY,
                                      frameSize.x, frameSize.y));
}

void Animation::setPeriod(sf::Time period) {
    this->period = period;
}

void Animation::setPosition(int x, int y) {
    sprite.setPosition(x, y);
}