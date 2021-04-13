#include "Game.hpp"

Game::Game(sf::RenderWindow &window) {
    sf::Drawable *toDraw[] = {&background};
    load(0, window);

    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            defaultEvents(window, event);
        }
        draw(window, toDraw, sizeof(toDraw) / sizeof(toDraw[0]));
    }
}

Game::~Game() {

}

void Game::load(uint number, const sf::RenderWindow &window) {
    std::string path = "data/lvl" + std::to_string(number) + "/";
    if(!backgroundT.loadFromFile(path + "map.png"))
        exit(0);
    background.setTexture(backgroundT);
    background.setScale(window.getSize().x / background.getLocalBounds().width,
                        window.getSize().y / background.getLocalBounds().height);

    config.setName(path + "map.ini");
    std::string name;
    for(uint i = 0; name != "NULL"; i++) {
        name = config.readString("NPC" + std::to_string(i), "name", "NULL");
    }
}