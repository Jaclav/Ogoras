#include "Console.hpp"

sf::RectangleShape Console::background;

std::string Console::typedString = "";
sf::Text Console::typedText(">", font);

std::string Console::previousString = "";
sf::Text Console::previousText("", font);

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
        typedText.setString(">" + typedString);
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
            typedText.setString(">" + typedString);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::V) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            typedString = sf::Clipboard::getString();

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            interpret(typedString);
            typedString = "";
        }
        typedText.setString(">" + typedString);
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

    previousString += message += "\n";
    previousText.setString(previousString);
    if(previousText.getLocalBounds().height > background.getSize().y - typedText.getLocalBounds().height) {
        previousString = previousString.substr(previousString.find("\n") + 1, previousString.size() - previousString.find("\n"));
    }
    previousText.setString(previousString);
}

Console::Settings Console::getSettings() {
    return settings;
}

void Console::interpret(std::string command) {
    std::string cmd = command.substr(0, command.find(" "));
    int p1 = 0;
    try {
        p1 = std::stoi(command.substr(command.find(" "), command.find_last_of(" ")));
    }
    catch(...) {}
    if(cmd == "noclip") {
        settings.noclip = p1;
        pushMessage("Noclip setted");
    }
    else {
        pushMessage("Command not found!");
    }
}