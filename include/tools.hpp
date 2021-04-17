#ifndef TOOLS_HPP
#define TOOLS_HPP

#ifdef _WIN32
#include <windows.h>
typedef unsigned int uint;
#endif //_WIN32

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Entity.hpp"

void defaultEvents(sf::RenderWindow &window, sf::Event event);
void draw(sf::RenderWindow &window, sf::Drawable *toDraw[], const int quantity);
bool isMouseCovering(sf::Vector2f position, sf::Vector2f size);
void setAndAlignText(sf::Text &text, std::wstring str, uint windowWidth, uint posY);
sf::IntRect setIntRect(Entity::Side side);

#endif //TOOLS_HPP