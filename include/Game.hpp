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

private:
    sf::Event event;

    Map map;
    Player player;
    const sf::RenderWindow *window;

    sf::Texture backgroundT;
    sf::Sprite background;
};

#endif //GAME_HPP