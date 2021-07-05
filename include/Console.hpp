#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <fstream>
#include <string>
#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Clipboard.hpp>
#include <SFML/Window/Event.hpp>

extern sf::Font font;
class Game;
class Player;

class Console : public sf::Drawable {
public:
    Console(sf::Vector2u windowSize);
    ~Console();

    struct Settings {
        bool noclip = false;
    };
    static Settings settings;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    static void handleEvent(sf::Event &event);
    static void pushMessage(std::string message);

    static Settings getSettings();
    static void setHandles(Game *game, Player *player);
    static void interpret(std::string command);

private:
    static bool activated;
    static Game *game;
    static Player *player;

    static sf::RectangleShape background;

    static sf::Text previousText;
    static std::wstring typedString;
    static sf::Text typedText;

    static std::ofstream file;
};

#endif //CONSOLE_HPP