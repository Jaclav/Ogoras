#include "tools.hpp"

bool showFpsCounter = false;

void defaultEvents(sf::RenderWindow &window, sf::Event event) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
        showFpsCounter = !showFpsCounter;
        window.pollEvent(event);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F12)) {
        sf::Texture printScreen;
        printScreen.create(window.getSize().x, window.getSize().y);
        printScreen.update(window);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

#ifdef _WIN32
        static HWND windowHandle = window.getSystemHandle();
        if(!printScreen.copyToImage().saveToFile(std::string(getenv("Temp")) + "\\ogor_screenshot.png")) {
            ShowWindow(windowHandle, SW_MINIMIZE);
            MessageBox(NULL, "Failed to take a screenshot", "Warning", MB_DEFAULT_DESKTOP_ONLY | MB_ICONWARNING | MB_TOPMOST);
            return;
        }
        system("explorer %Temp%\\ogor_screenshot.png") ;
#elif defined __linux__ || defined linux || defined __linux
        if(!printScreen.copyToImage().saveToFile("/tmp/ogor_screenshot.png")) {
            system("zenity --warning --text=\"Failed to take a screenshot.\" --title=\"Warning!\"&");
            return;
        }
        system("xdg-open /tmp/ogor_screenshot.png");
#else
#error Unknown OS
#endif // _WIN32

#pragma GCC diagnostic pop
    }
    else if(event.type == event.Closed) {
        window.close();
    }
}

void draw(sf::RenderWindow &window, std::vector<sf::Drawable*>&toDraw) {
    for(int i = 0; i < toDraw.size(); i++)
        window.draw(*toDraw[i]);

    static sf::Clock fpsClock;
    static int fpsCounter;
    static sf::Text fpsText("", font);

    //fps
    if(fpsClock.getElapsedTime().asMilliseconds() >= 1000) {
        fpsClock.restart();
        fpsText.setString(std::to_string(fpsCounter));
        fpsCounter = 0;
    }
    else {
        fpsCounter++;
    }
    if(showFpsCounter) {
        window.draw(fpsText);
    }
    return;
}

void loadTexture(sf::Texture &texture, std::string pathToFile, Entity::Side side) {
    //load and set texture
    std::ifstream file(pathToFile, std::ios::in);
    if(file.good())
        texture.loadFromFile(pathToFile, setIntRect(side));
    else {
        texture.loadFromMemory(notFound_png, notFound_png_len);
        Console::pushMessage("Cannot load " + pathToFile);
    }
    file.close();
}

bool isMouseCovering(sf::Vector2f position, sf::Vector2f size) {
    if(sf::Mouse::getPosition().x >= position.x &&
            sf::Mouse::getPosition().x <= position.x + size.x &&
            sf::Mouse::getPosition().y >= position.y &&
            sf::Mouse::getPosition().y <= position.y + size.y) {
        return true;
    }
    else
        return false;
}

void setAndAlignText(sf::Text &text, std::wstring str, u_int windowWidth, u_int posY) {
    text.setString(str);
    text.setPosition(windowWidth / 2 - text.getLocalBounds().width / 2, posY);
}

sf::IntRect setIntRect(Entity::Side side) {
    sf::IntRect ir(0, 0, 128, 128);
    switch(side) {
    case Entity::Side::Up: {
        ir.left = 0;
        break;
    }
    case Entity::Side::Down: {
        ir.left = 128;
        break;
    }
    case Entity::Side::Right: {
        ir.left = 256;
        break;
    }
    case Entity::Side::Left: {
        ir.left = 384;
        break;
    }
    }
    return ir;
}