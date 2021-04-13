#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <cmath>

#include <SFML/Graphics.hpp>

void defaultEvents(sf::RenderWindow &window, sf::Event event);
void draw(sf::RenderWindow &window, sf::Drawable *toDraw[], const int quantity);
bool isMouseCovering(sf::Vector2f position, sf::Vector2f size);
void setAndAlignText(sf::Text &text, std::wstring str, u_int windowWidth, u_int posY);

#endif //TOOLS_HPP