#include "tools.hpp"

void defaultEvents(sf::RenderWindow &window, sf::Event event) {
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

void draw(sf::RenderWindow &window, sf::Drawable *toDraw[], const int quantity) {
    window.clear();
    for(int i = 0; i < quantity; i++)
        window.draw(*toDraw[i]);
    window.display();
    return;
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