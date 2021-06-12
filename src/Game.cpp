#include "Game.hpp"

Game::Game(sf::RenderWindow &window) : console(window.getSize()) {
    std::vector<sf::Drawable*>toDraw = {&background, &map, &player, &console};
    load(0, window);
    Console::pushMessage("Game loaded");

    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            defaultEvents(window, event);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                player.move(Player::Up);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                player.move(Player::Down);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player.move(Player::Right);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                player.move(Player::Left);
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

void Game::load(uint number, const sf::RenderWindow &window) {
    std::string path = "data/lvl" + std::to_string(number) + "/";
    config.setPath(path + "config.ini");

    //background
    if(!backgroundT.loadFromFile(path + "map.png"))
        exit(0);
    background.setTexture(backgroundT);
    background.setScale(window.getSize().x / background.getLocalBounds().width,
                        window.getSize().y / background.getLocalBounds().height);

    //player
    player.setPositionAndSide(config.readInt("Player", "x", 0),
                              config.readInt("Player", "y", 0),
                              (Npc::Side)config.readString("Player", "s", "D")[0]);

    //npc
    config.setPath(path + "npc.ini");
    npc.clear();
    std::string name = "";
    uint quiantity = config.readInt("Npc", "quantity", 0);
    if(quiantity == 0)
        return;
    npc.reserve(quiantity);

    for(uint i = 0; i < quiantity; i++) {
        npc.push_back(Npc(i, path + "npc.ini"));//Allocate number to Npc and give path with cnfig file
    }
}