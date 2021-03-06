#include "Menu.hpp"

Menu::Menu(sf::RenderWindow &window) {
    this->window = &window;

    mainText.setFont(font);
    mainText.setOutlineThickness(3);
    mainText.setCharacterSize(window.getSize().x / 24);

    subText.setFont(font);
    subText.setOutlineThickness(2);
    subText.setCharacterSize(window.getSize().x / 35);
    setDefault();

    //for initializing Console
    std::vector<sf::Drawable*> tmp;
    draw(window, tmp);

    loadTexture(backgroundT, "data/menuBackground.png");
    background.setTexture(backgroundT);
    background.setScale(window.getSize().x / background.getLocalBounds().width,
                        window.getSize().y / background.getLocalBounds().height);
}

void Menu::setDefault() {
    setAndAlignText(mainText, mainTextStr, window->getSize().x, 100);
    subText.setString(version);
    subText.setPosition(0, 0);
}

void Menu::start() {
    Button backButton((window->getSize().x - 500) / 2, window->getSize().y / 1.2, 500, 100, "Back", [&]() {});
    Button playButton(window->getSize().x / 8, window->getSize().y / 3, 500, 100, "Play", [&]() {});
    Button settingsButton(window->getSize().x / 8, window->getSize().y / 3 + 125, 500, 100, "Settings", [&]() {
        setAndAlignText(mainText, L"Settings", window->getSize().x, 100);

        subText.setString(L"Usage:\n\t` - open console\n\tArrows - move player\nFor more information read README.md");
        subText.setPosition(window->getSize().x / 10, 300);

        std::vector<sf::Drawable*> toDraw{&background, &backButton, &mainText, &subText};

        while(window->isOpen()) {
            if(Console::getVariable().playing) {
                setDefault();
                return;
            }

            while(window->pollEvent(event)) {
                defaultEvents(*window, event);
                if((backButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Left))  || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    setDefault();
                    return;
                }
            }
            window->clear();
            draw(*window, toDraw);
            window->display();
        }
    });
    Button creditsButton(window->getSize().x / 8, window->getSize().y / 3 + 250, 237.5, 100, "Credits", [&]() {
        setAndAlignText(mainText, L"Credits", window->getSize().x, 100);

        subText.setString(L"Game created by: Jac??aw\nTextures created by: Skryty\nGraphic library: SFML created by Laurent Gomila\nFont used: DejaVuSans");
        subText.setPosition(window->getSize().x / 10, 300);

        std::vector<sf::Drawable*> toDraw{&background, &backButton, &mainText, &subText};

        while(window->isOpen()) {
            if(Console::getVariable().playing) {
                setDefault();
                return;
            }

            while(window->pollEvent(event)) {
                defaultEvents(*window, event);
                if((backButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Left)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    setDefault();
                    return;
                }
            }
            window->clear();
            draw(*window, toDraw);
            window->display();
        }
    });
    Button quitButton(window->getSize().x / 8 + 262.5, window->getSize().y / 3 + 250, 237.5, 100, "Quit", [&]() {
        window->close();
    });

    std::vector<sf::Drawable*> toDraw{&background, &playButton, &settingsButton, &creditsButton, &quitButton, &mainText, &subText};

    while(window->isOpen()) {
        if(Console::getVariable().playing)
            return;

        while(window->pollEvent(event)) {
            defaultEvents(*window, event);
            if(playButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                Console::interpret("load lvl0");
                return;
            }
        }
        window->clear();
        draw(*window, toDraw);
        window->display();
    }
}