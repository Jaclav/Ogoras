#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <fstream>

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

#include "Console.hpp"
#include "Entity.hpp"

#include "../resources/notFound.png.hpp"

static const u_char PIXELS_PER_UNIT = 128;

typedef unsigned int units;

void defaultEvents(sf::RenderWindow &window, sf::Event event);
void draw(sf::RenderWindow &window, std::vector<sf::Drawable*>&toDraw);
void loadTexture(sf::Texture &texture, std::string path);
bool isMouseCovering(sf::Vector2f position, sf::Vector2f size);
void setAndAlignText(sf::Text &text, std::wstring str, uint windowWidth, uint posY);
sf::IntRect setIntRect(Entity::Side side);

#endif //TOOLS_HPP