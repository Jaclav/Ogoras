#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "NPC.hpp"
#include "Ini.hpp"
#include "tools.hpp"

class Game {
    sf::Event event;

    sf::Texture backgroundT;
    sf::Sprite background;

    std::vector<NPC>npc;

    Ini config;
    void load(uint number, const sf::RenderWindow &window);
public:
    Game(sf::RenderWindow &window);
    ~Game();
};

#endif //GAME_HPP