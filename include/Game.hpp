#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Console.hpp"
#include "Map.hpp"
#include "Npc.hpp"
#include "inicpp/Ini.hpp"
#include "Player.hpp"
#include "tools.hpp"

class Game {
public:
    Game(sf::RenderWindow &window);

private:
    sf::Event event;

    sf::Texture backgroundT;
    sf::Sprite background;

    std::vector<Npc>npc;
    Player player;

    Ini config;
    Console console;
    Map map;
    void load(uint number, const sf::RenderWindow &window);
};

#endif //GAME_HPP