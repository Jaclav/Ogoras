#include "Game.hpp"

Game::Game(sf::RenderWindow &window) {
    this->window = &window;
    std::vector<sf::Drawable*>toDraw = {&background, &map, &player};
    load("lvl0");
    Console::pushMessage("Game loaded");
    Console::setHandles(this, &player);

    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            defaultEvents(window, event);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                player.move(Player::Up);
                if(!map.shouldMove(player.getPosition())) {
                    player.move(Player::Down);//antagonist move
                    player.setSide(Player::Side::Up);//set side after antagonist move
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                player.move(Player::Down);
                if(!map.shouldMove(player.getPosition())) {
                    player.move(Player::Up);//antagonist move
                    player.setSide(Player::Side::Down);//set side after antagonist move
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player.move(Player::Right);
                if(!map.shouldMove(player.getPosition())) {
                    player.move(Player::Left);//antagonist move
                    player.setSide(Player::Side::Right);//set side after antagonist move
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                player.move(Player::Left);
                if(!map.shouldMove(player.getPosition())) {
                    player.move(Player::Right);//antagonist move
                    player.setSide(Player::Side::Left);//set side after antagonist move
                }
            }
        }
        window.clear();
        draw(window, toDraw);

        window.display();
    }
}

void Game::load(std::string levelName) {
    std::string path = "data/" + levelName + "/";
    config.setPath(path + "config.ini");

    map.load(path);
    player.load(path);

    //background
    loadTexture(backgroundT, path + "map.png");
    background.setTexture(backgroundT);
    background.setScale(window->getSize().x / background.getLocalBounds().width,
                        window->getSize().y / background.getLocalBounds().height);
}