#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Console.hpp"
#include "Map.hpp"
#include "inicpp/Ini.hpp"
#include "Player.hpp"
#include "tools.hpp"

class Game {
public:
    Game(sf::RenderWindow &window);

private:
    sf::Event event;

    Console console;
    Ini config;
    Map map;
    Player player;
    void load(uint number, sf::Vector2u windowSize);

    sf::Texture backgroundT;
    sf::Sprite background;
};

#endif //GAME_HPP