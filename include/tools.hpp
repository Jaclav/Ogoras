#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <cmath>
#ifdef _WIN32
#include <windows.h>
typedef uint unsigned int;
#endif //_WIN32

#include <SFML/Graphics.hpp>

void defaultEvents(sf::RenderWindow &window, sf::Event event);
void draw(sf::RenderWindow &window, sf::Drawable *toDraw[], const int quantity);
bool isMouseCovering(sf::Vector2f position, sf::Vector2f size);
void setAndAlignText(sf::Text &text, std::wstring str, uint windowWidth, uint posY);

#endif //TOOLS_HPP