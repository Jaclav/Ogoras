#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <fstream>
#include <string>
#include <thread>
#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Window/Clipboard.hpp>
#include <SFML/Window/Event.hpp>

extern sf::Font font;
class Game;
class Map;
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
    static void setHandles(Game *game, Map *map, Player *player);
    static void interpret(std::string command);
    static void script(std::string path);

private:
    static bool activated;
    static Game *game;
    static Map *map;
    static Player *player;

    static sf::RectangleShape background;

    static sf::Text previousText;
    static std::wstring typedString;
    static sf::Text typedText;

    static std::ofstream file;
};

#endif //CONSOLE_HPP