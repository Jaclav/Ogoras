#include "Console.hpp"
#include "Game.hpp"

Console::Settings Console::settings = {};

bool Console::activated = false;
Game *Console::game = nullptr;
Player *Console::player = nullptr;

sf::RectangleShape Console::background;

std::wstring Console::typedString = L"";
sf::Text Console::typedText("> ", font);

sf::Text Console::previousText("", font, 20);

std::ofstream Console::file("console.log", std::ios::out);

Console::Console(sf::Vector2u windowSize) {
    background.setSize(sf::Vector2f(windowSize.x / 2.5, windowSize.y / 4));
    background.setPosition(0, windowSize.y - background.getLocalBounds().height);
    background.setFillColor(sf::Color(128, 128, 128, 150));//button's color

    previousText.setPosition(10, background.getPosition().y);
    previousText.setFillColor(sf::Color::Black);

    typedText.setPosition(10, windowSize.y - typedText.getLocalBounds().height * 2.1);
    typedText.setFillColor(sf::Color::Black);
}

Console::~Console() {
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

void Console::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if(!activated)
        return;

    target.draw(background, states);
    target.draw(previousText, states);
    target.draw(typedText, states);
}

void Console::pushMessage(std::string message) {
    file << message << std::endl;

    previousText.setString(previousText.getString() + message + "\n");
    if(previousText.getLocalBounds().height > background.getSize().y - typedText.getLocalBounds().height) {
        previousText.setString(previousText.getString().substring(previousText.getString().find("\n") + 1,
                               previousText.getString().getSize() - previousText.getString().find("\n")));
    }
}

Console::Settings Console::getSettings() {
    return settings;
}

void Console::setHandles(Game *game, Player *player) {
    Console::game = game;
    Console::player = player;
}

void Console::interpret(std::string command) {
    pushMessage("> " + command);

    std::string cmd = command.substr(0, command.find(" "));
    std::vector<int> parameterInt;
    parameterInt.reserve(3);
    std::vector<std::string> parameterStr;
    parameterStr.reserve(3);

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

    if(cmd == "clear") {
        previousText.setString("");
    }
    else if(player == nullptr || game == nullptr) {
        pushMessage("Game or player undefined!");
        return;
    }
    else if(cmd == "noclip") {
        settings.noclip = parameterInt[0];
        pushMessage("Noclip setted as " + std::to_string(parameterInt[1]));
    }
    else if(cmd == "load") {
        game->load(parameterStr[0]);
        pushMessage("Level loaded");
    }
    else if(cmd == "tp") {
        if(parameterInt.size() < 2) {
            pushMessage("2 parameters required!");
            return;
        }
        player->setPosition(parameterInt[0], parameterInt[1]);
        pushMessage("Player teleported at " + std::to_string(player->getPosition().x) + " " + std::to_string(player->getPosition().y));
    }
    else if(cmd == "position") {
        pushMessage("Player position is " + std::to_string(player->getPosition().x) + " " + std::to_string(player->getPosition().y));
    }
    else if(cmd == "say") {
        player->say(command.substr(command.find(" ") + 1));
    }
    else {
        pushMessage("Command not found!");
    }
}