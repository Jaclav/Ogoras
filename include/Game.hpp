#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Console.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "tools.hpp"

class Game {
public:
    Game(sf::RenderWindow &window);
    void load(std::string levelName);
    void play();

    std::string getLevelName();
    Map* getMap();
    Player* getPlayer();

private:
    sf::RenderWindow *window;
    sf::Event event;
    std::string levelName;

    Map map;
    Player player;

    sf::Texture backgroundT;
    sf::Sprite background;
};

#endif //GAME_HPP