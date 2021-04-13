#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "tools.hpp"

class Game {
    sf::Event event;
    Map map;
public:
    Game(sf::RenderWindow &window);
    ~Game();
};

#endif //GAME_HPP