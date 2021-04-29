#include "Game.hpp"

Game::Game(sf::RenderWindow &window) {
    std::vector<sf::Drawable*>toDraw = {&background, &player};
    load(0, window);

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
        }
        window.clear();
        for(uint i = 0; i < toDraw.size(); i++) {
            window.draw(*toDraw[i]);
        }
        for(uint i = 0; i < npc.size(); i++) {
            window.draw(npc[i]);
        }
        window.display();
    }
}

void Game::load(uint number, const sf::RenderWindow &window) {
    std::string path = "data/lvl" + std::to_string(number) + "/";
    config.setName(path + "map.ini");
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
    npc.clear();
    std::string name = "";
    for(uint i = 0; ; i++) {
        name = config.readString("Npc" + std::to_string(i), "name", "NULL");
        if(name == "NULL")
            break;
        npc.push_back(Npc(name,
                          config.readInt("Npc" + std::to_string(i), "x", 0),
                          config.readInt("Npc" + std::to_string(i), "y", 0),
                          (Npc::Side)config.readString("Npc" + std::to_string(i), "s", "D")[0]));
    }
}