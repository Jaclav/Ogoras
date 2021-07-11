#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

#include "tools.hpp"

class Animation : public sf::Drawable {
public:
    Animation();
    Animation(const Animation &other);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void loadFromFile(std::string path, sf::Vector2i frameSize);
    void move(int x, int y);

    void setFrameY(int frameY);
    void setPeriod(sf::Time period);
    void setPosition(int x, int y);

private:
    sf::Texture texture;
    mutable sf::Sprite sprite;

    int frameY = 0;
    sf::Vector2i frameSize;

    mutable sf::Clock clock;
    mutable sf::Time period = sf::milliseconds(1000);
};

#endif //ANIMATION_HPP