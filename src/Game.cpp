#include "Game.hpp"

Game::Game(sf::RenderWindow &window) {
    this->window = &window;
}

void Game::load(std::string levelName) {
    this->levelName = levelName;
    std::string path = "data/levels/" + levelName + "/";
    map.load(path);
    player.load(path);

    //background
    loadTexture(backgroundT, path + "background.png");
    background.setTexture(backgroundT);
    background.setScale(window->getSize().x / background.getLocalBounds().width,
                        window->getSize().y / background.getLocalBounds().height);
}

void Game::play() {
    Console::pushMessage("Game loaded");
    std::vector<sf::Drawable*>toDraw = {&background, &map, &player};

    while(window->isOpen()) {
        while(window->pollEvent(event)) {
            defaultEvents(*window, event);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                Console::interpret("stop");
                return;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if(map.shouldMove(sf::Vector2i(player.getPosition().x, player.getPosition().y - 1))) {
                    player.move(Player::Up);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if(map.shouldMove(sf::Vector2i(player.getPosition().x, player.getPosition().y + 1))) {
                    player.move(Player::Down);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if(map.shouldMove(sf::Vector2i(player.getPosition().x + 1, player.getPosition().y))) {
                    player.move(Player::Right);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if(map.shouldMove(sf::Vector2i(player.getPosition().x - 1, player.getPosition().y))) {
                    player.move(Player::Left);
                }
            }
        }
        window->clear();
        draw(*window, toDraw);
        map.drawNpcs(*window, sf::RenderStates());

        window->display();
    }
}

std::string Game::getLevelName() {
    return levelName;
}

Map* Game::getMap() {
    return &map;
}

Player* Game::getPlayer() {
    return &player;
}