#include "Game.hpp"

Game::Game(sf::RenderWindow &window) {
    std::vector<sf::Drawable*>toDraw = {&background};
    load(0, window);

    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            defaultEvents(window, event);
        }
        window.clear();
        for(auto i : toDraw) {
            window.draw(*i);
        }
        for(auto i : npc) {
            window.draw(i);
        }
        window.display();
    }
}

Game::~Game() {

}

void Game::load(uint number, const sf::RenderWindow &window) {
    std::string path = "data/lvl" + std::to_string(number) + "/";
    //background
    if(!backgroundT.loadFromFile(path + "map.png"))
        exit(0);
    background.setTexture(backgroundT);
    background.setScale(window.getSize().x / background.getLocalBounds().width,
                        window.getSize().y / background.getLocalBounds().height);

    //npc
    npc.clear();
    config.setName(path + "map.ini");
    std::string name = "";
    for(uint i = 0; ; i++) {
        name = config.readString("NPC" + std::to_string(i), "name", "NULL");
        if(name == "NULL")
            break;
        npc.push_back(NPC(name,
                          config.readInt("NPC" + std::to_string(i), "x", 0),
                          config.readInt("NPC" + std::to_string(i), "y", 0)));
    }
}