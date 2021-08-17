#include "Console.hpp"
#include "Game.hpp"
#include "Map.hpp"

Console::Variables Console::variables = {};

bool Console::activated = false;
bool Console::interpretScript = true;
int Console::numberOfThreads = 0;

Game *Console::game = nullptr;

sf::RectangleShape Console::background;

sf::Text Console::previousText("", font, 15);
std::wstring Console::typedString = L"";
sf::Text Console::typedText("> ", font, 20);

std::ofstream Console::file("console.log", std::ios::out);

std::mutex Console::fontMutex = {};

Console::Console(sf::Vector2u windowSize, Game &game) {
    pushMessage("Creating console.");
    this->game = &game;

    background.setSize(sf::Vector2f(windowSize.x / 2.5, windowSize.y / 4));
    background.setPosition(0, windowSize.y - background.getLocalBounds().height);
    background.setFillColor(sf::Color(128, 128, 128, 150));//button's color

    previousText.setPosition(10, background.getPosition().y);
    previousText.setFillColor(sf::Color::Black);

    typedText.setPosition(10, windowSize.y - typedText.getLocalBounds().height * 2.5);
    typedText.setFillColor(sf::Color::Black);
}

Console::~Console() {
    pushMessage("Destructing console.");

    interpret("stop");

    file.close();
}

void Console::handleEvent(sf::Event &event) {
    if(activated && event.type == sf::Event::TextEntered && event.text.unicode > 31 && event.text.unicode != '`') {
        typedString += event.text.unicode;
        typedText.setString(L"> " + typedString);
    }

    //cooldown
    static sf::Clock timer;
    if(timer.getElapsedTime().asMilliseconds() < 50) {
        return;
    }
    else {
        timer.restart();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde)) {
        activated = !activated;
    }
    if(activated) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && typedString.size() > 0) {
            typedString.pop_back();
            typedText.setString(L"> " + typedString);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::V) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            typedString = sf::Clipboard::getString();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            sf::Clipboard::setString(previousText.getString());
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            interpret(std::string(typedString.begin(), typedString.end()));
            typedString = L"";
        }
        typedText.setString(L"> " + typedString);
    }
}

void Console::drawOn(sf::RenderWindow &window) {
    if(!activated)
        return;

    window.draw(background);
    window.draw(previousText);
    window.draw(typedText);
}

void Console::pushMessage(std::string message) {
    file << message << std::endl;

    std::lock_guard<std::mutex> lock(fontMutex);

    previousText.setString(previousText.getString() + message + "\n");
    if(previousText.getLocalBounds().height > background.getLocalBounds().height) {
        previousText.setString(previousText.getString().substring(previousText.getString().find("\n") + 1,
                               previousText.getString().getSize() - previousText.getString().find("\n")));
    }
}

Console::Variables Console::getVariable() {
    return variables;
}

void Console::interpret(std::string command) {
    if(command == "")
        return;

    static const size_t maxParametersAmount = 3;
    pushMessage("> " + command);

    std::string cmd = command.substr(0, command.find(" "));
    std::vector<int> parameterInt;
    parameterInt.reserve(maxParametersAmount);
    std::vector<std::string> parameterStr;
    parameterStr.reserve(maxParametersAmount);

    std::string tmp = command;
    for(int i = 0; tmp.find(" ") != std::string::npos; i++) {
        tmp = tmp.substr(tmp.find(" ") + 1, tmp.size());
        parameterStr.push_back(tmp.substr(0, tmp.find(" ")));
        try {
            parameterInt.push_back(std::stoi(tmp.substr(0, tmp.find(" "))));
        }
        catch(...) {
            parameterInt.push_back(0);
        }
    }
    parameterInt.resize(maxParametersAmount);
    parameterStr.resize(maxParametersAmount);

    if(cmd == "clear") {
        previousText.setString("");
    }
    else if(game == nullptr) {
        pushMessage("Game is undefined!");
        return;
    }
    else if(cmd == "load") {
        interpret("stop");
        variables.playing = true;
        pushMessage("Loading " + parameterStr[0] + " level");
        game->load(parameterStr[0]);
        interpret("script main");
    }
    //threads
    else if(cmd == "script") {
        std::thread(&script, parameterStr[0]).detach();
    }
    else if(cmd == "stop") {
        variables.playing = false;
        interpretScript = false;

        sf::sleep(sf::milliseconds(1));
        for(u_char i = 0; i < 4 && numberOfThreads; i++) {
            pushMessage("Waiting until all threads are terminated.");
            sf::sleep(sf::milliseconds(1));
        }

        interpretScript = true;
        numberOfThreads = 0;
    }
    else if(cmd == "threads") {
        pushMessage("Existing threads: " + std::to_string(numberOfThreads));
    }
    else if(cmd == "wait") {
        sf::Clock clock;
        while(clock.getElapsedTime() < sf::milliseconds(parameterInt[0]) && interpretScript) {} // Cannot be done with sf::sleep because of interpretScript
    }
    //player
    else if(cmd == "noclip") {
        variables.noclip = parameterInt[0];
        pushMessage("Noclip setted as " + std::to_string(parameterInt[0]));
    }
    else if(cmd == "tp") {
        if(game->getMap()->shouldMove(sf::Vector2<units>(parameterInt[0], parameterInt[1]))) {
            game->getPlayer()->setPosition(parameterInt[0], parameterInt[1]);
            pushMessage("Player teleported at " + std::to_string(game->getPlayer()->getPosition().x) + " " + std::to_string(game->getPlayer()->getPosition().y));
        }
        else {
            pushMessage("Cannnot teleport there!");
        }
    }
    else if(cmd == "position") {
        pushMessage("Player position is " + std::to_string(game->getPlayer()->getPosition().x) + " " + std::to_string(game->getPlayer()->getPosition().y));
    }
    else if(cmd == "say") {
        if(findNthElement(command, ' ', 2) != std::string::npos)
            game->getPlayer()->say(sf::milliseconds(parameterInt[0]), command.substr(findNthElement(command, ' ', 2) + 1));
        else
            pushMessage("Wrong say parameters!");
    }
    //map
    else if(cmd == "map_block") {
        if(variables.playing)
            game->getMap()->setBlock(parameterInt[0], parameterInt[1], parameterInt[2]);
        else
            pushMessage("Map can be changed only during game!");
    }
    //npc
    else if(cmd.find("npc_") != std::string::npos) {
        if(game->getMap()->getNpc(parameterInt[0]) != nullptr) {
            if(cmd == "npc_move") {
                game->getMap()->getNpc(parameterInt[0])->move(parameterInt[1], parameterInt[2]);
            }
            else if(cmd == "npc_say") {
                if(findNthElement(command, ' ', 3) != std::string::npos) {
                    game->getMap()->getNpc(parameterInt[0])->say(sf::milliseconds(parameterInt[1]), command.substr(findNthElement(command, ' ', 3) + 1));
                }
                else
                    pushMessage("Wrong npc_say parameters!");
            }
            else if(cmd == "npc_touch") {
                game->getMap()->getNpc(parameterInt[0])->touched();
            }
        }
        else {
            pushMessage("Npc" + parameterStr[0] + " doesn't exist!");
        }
    }
    else {
        pushMessage("Command not found!");
    }
}

void Console::script(std::string name) {
    name = "data/levels/" + game->getLevelName() + "/" + name + ".scr";
    std::ifstream file(name);
    if(!file.good()) {
        pushMessage("Cannot load " + name);
        return;
    }

    numberOfThreads++;
    std::string line;
    while(std::getline(file, line) && interpretScript) {
        interpret(line);
    }
    file.close();

    numberOfThreads--;
}