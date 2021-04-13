#include "Game.hpp"

Game::Game(sf::RenderWindow &window) {
    sf::Drawable *toDraw[] = {&map};
    map.load(1, window);

    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            defaultEvents(window, event);
        }
        draw(window, toDraw, sizeof(toDraw) / sizeof(toDraw[0]));
    }
}

Game::~Game() {

}