#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <fstream>
#include <mutex>
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

class Console {
public:
    Console(sf::Vector2u windowSize, Game &game);
    ~Console();

    struct Variables {
        bool noclip = false;
        bool playing = false;
    };
    static Variables variables;

    static void drawOn(sf::RenderWindow &window);
    static void handleEvent(sf::Event &event);
    static void pushMessage(std::string message);

    static Variables getVariable();

    static void interpret(std::string command);
    static void script(std::string name);

private:
    static bool activated, interpretScript;
    static int numberOfThreads;

    static Game *game;

    static sf::RectangleShape background;

    static sf::Text previousText;
    static std::wstring typedString;
    static sf::Text typedText;

    static std::ofstream file;

    static std::mutex fontMutex;
};

#endif //CONSOLE_HPP