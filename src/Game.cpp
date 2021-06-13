#include "Game.hpp"

Game::Game(sf::RenderWindow &window) : console(window.getSize()) {
    std::vector<sf::Drawable*>toDraw = {&background, &map, &player, &console};
    load(0, window.getSize());
    Console::pushMessage("Game loaded");

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
            console.handleEvent(event);
        }
        window.clear();
        draw(window, toDraw);
        for(uint i = 0; i < npc.size(); i++) {
            window.draw(npc[i]);
        }
        window.display();
    }
}

void Game::load(uint number, sf::Vector2u windowSize) {
    std::string path = "data/lvl" + std::to_string(number) + "/";
    config.setPath(path + "config.ini");

    //map
    map.load(path + "map.lvl");

    //player
    player.setPosition(config.readInt("Player", "x", 0),
                       config.readInt("Player", "y", 0));
    player.setSide((Npc::Side)config.readString("Player", "s", "D")[0]);

    //npc
    config.setPath(path + "npc.ini");
    npc.clear();
    std::string name = "";
    uint quiantity = config.readInt("Npc", "quantity", 0);
    if(quiantity == 0)
        return;
    npc.reserve(quiantity);

    for(uint i = 0; i < quiantity; i++) {
        npc.push_back(Npc(i, path + "npc.ini"));//Allocate number to Npc and give path with config file
    }

    //background
    if(!backgroundT.loadFromFile(path + "map.png"))
        exit(0);
    background.setTexture(backgroundT);
    background.setScale(windowSize.x / background.getLocalBounds().width,
                        windowSize.y / background.getLocalBounds().height);
}