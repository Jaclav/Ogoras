#include "Menu.hpp"

Menu::Menu(sf::RenderWindow &window) {
    if(!font.loadFromMemory(DejaVuSans_ttf, DejaVuSans_ttf_len))
        exit(0);
    mainText.setFont(font);
    mainText.setOutlineThickness(3);
    mainText.setCharacterSize(window.getSize().x / 24);

    subText.setFont(font);
    subText.setOutlineThickness(2);
    subText.setCharacterSize(window.getSize().x / 35);
    setDefault(window);

    if(!backgroundT.loadFromMemory(startBackground_png, startBackground_png_len))
        exit(-1);
    background.setTexture(backgroundT);
    background.setScale(window.getSize().x / background.getLocalBounds().width,
                             window.getSize().y / background.getLocalBounds().height);
}

Menu::~Menu() {

}

void Menu::start(sf::RenderWindow &window) {
    Button backButton((window.getSize().x - 500) / 2, window.getSize().y / 1.2, 500, 100, "Back", [&]() {
        setDefault(window);//doesn't work!!!
    });
    Button playButton(window.getSize().x / 8, window.getSize().y / 3, 500, 100, "Play", [&]() {
        shouldPlay = true;
    });
    Button settingsButton(window.getSize().x / 8, window.getSize().y / 3 + 125, 500, 100, "Settings", [&]() {
        setAndAlignText(mainText, L"Settings", window.getSize().x, 100);

        subText.setString(L"Usage:");
        subText.setPosition(window.getSize().x / 10, 300);

        sf::Drawable *toDraw[] = {&background, &backButton, &mainText, &subText};

        while(window.isOpen()) {
            while(window.pollEvent(event)) {
                defaultEvents(window, event);
                if(backButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    setDefault(window);
                    return;
                }
            }
            draw(window, toDraw, sizeof(toDraw) / sizeof(toDraw[0]));
        }
    });
    Button creditsButton(window.getSize().x / 8, window.getSize().y / 3 + 250, 237.5, 100, "Credits", [&]() {
        setAndAlignText(mainText, L"Credits", window.getSize().x, 100);

        subText.setString(L"Game created by: Jacław\nTextures created by: Skryty\nGraphic library: SFML created by Laurent Gomila\nFont used: DejaVuSans");
        subText.setPosition(window.getSize().x / 10, 300);

        sf::Drawable *toDraw[] = {&background, &backButton, &mainText, &subText};

        while(window.isOpen()) {
            while(window.pollEvent(event)) {
                defaultEvents(window, event);
                if(backButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    setDefault(window);
                    return;
                }
            }
            draw(window, toDraw, sizeof(toDraw) / sizeof(toDraw[0]));
        }
    });
    Button quitButton(window.getSize().x / 8 + 262.5, window.getSize().y / 3 + 250, 237.5, 100, "Quit", [&]() {
        window.close();
    });

    sf::Drawable *toDraw[] = {&background, &playButton, &settingsButton, &creditsButton, &quitButton, &mainText, &subText};

    while(window.isOpen() && !shouldPlay) {
        while(window.pollEvent(event)) {
            defaultEvents(window, event);
        }

        draw(window, toDraw, sizeof(toDraw) / sizeof(toDraw[0]));
    }
}

void Menu::setDefault(sf::RenderWindow &window) {
    setAndAlignText(mainText, mainTextStr, window.getSize().x, 100);
    subText.setString(version);
    subText.setPosition(0, 0);
}

void Menu::stop(sf::RenderWindow &window) {
    //TODO; stop screen when pressed ESC
    window.setPosition(window.getPosition());
}