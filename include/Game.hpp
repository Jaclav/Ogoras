#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Npc.hpp"
#include "Ini.hpp"
#include "tools.hpp"

class Game {
public:
    Game(sf::RenderWindow &window);

private:
    sf::Event event;

    sf::Texture backgroundT;
    sf::Sprite background;

    std::vector<Npc>npc;

    Ini config;
    void load(uint number, const sf::RenderWindow &window);
};

#endif //GAME_HPP