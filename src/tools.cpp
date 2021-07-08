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
    Console::handleEvent(event);
}

void draw(sf::RenderWindow &window, std::vector<sf::Drawable*>&toDraw) {
    for(long unsigned int i = 0; i < toDraw.size(); i++)
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

    //Console
    static Console console(window.getSize());
    window.draw(console);

    return;
}

size_t findNthElement(std::string string, char toFind, uint n) {
    uint instance = 0;
    for(size_t i = 0; i < string.size(); i++) {
        if(string[i] == toFind) {
            instance++;
            if(instance == n) {
                return i;
            }
        }
    }
    return std::string::npos;
}

void loadTexture(sf::Texture &texture, std::string path) {
    //fstream doesn't work on wine
    if(FILE *file = fopen(path.c_str(), "r")) {
        texture.loadFromFile(path);
        fclose(file);
    }
    else {
        texture.loadFromMemory(notFound_png, notFound_png_len);
        texture.setRepeated(true);
        Console::pushMessage("Cannot load " + path);
    }
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

uint getNumberOfIniSections(std::string path) {
    std::ifstream file(path);
    uint quantity = 0;
    std::string line;
    while(std::getline(file, line)) {
        if(line[0] == '[')
            quantity++;
    }
    file.close();
    return quantity;
}

std::string readIniString(std::string path, std::string section, std::string key, std::string def) {
    std::ifstream file(path);
    if(!file.good()) {
        return def;
    }

    std::string line;
    std::string currentSection;
    std::string currentKey;

    while(std::getline(file, line)) { //reading line
        currentSection = line.substr(line.find("[") + 1); //value is path of section

        if(currentSection.substr(0, currentSection.find("]")) != section) { //checking section
            continue;
        }

        while(std::getline(file, line)) { //reading line in section
            currentKey = line.substr(0, line.find("="));

            if(currentKey.find("[") == 0) { //if start of another section
                break;
            }

            if(currentKey != key) {
                continue;
            }

            file.close();
            return line.substr(line.find("=") + 1, line.size());
        }
    }
    file.close();
    return def;
}

int readIniInt(std::string path, std::string section, std::string key, int def) {
    try {
        return std::atoi(readIniString(path, section, key, std::to_string(def)).c_str());
    }
    catch(...) {
        return def;
    }
}

void writeIniString(std::string path, std::string section, std::string key, std::string value) {
    std::fstream file(path, std::ios::in);
    if(!file.good()) {
        file << '[' << section << ']' << '\n' << key << '=' << value;
    }

    //loading file into memory
    std::vector<std::string> loaded;
    std::string tmp;
    while(std::getline(file, tmp)) {
        loaded.push_back(tmp);
    }

    bool sectionFounded = false;
    bool keyFounded = false;

    uint i = 0;

    for(; i < loaded.size(); i++) { //search section
        if(sectionFounded && loaded[i].size() > 3 && loaded[i][0] == '[') {//section is found and another section begins
            break;
        }
        if(sectionFounded || (loaded[i].size() > 3 && loaded[i][0] == '[' && loaded[i].substr(1, loaded[i].size() - 2) == section)) {//if in good section
            sectionFounded = true;
            if(loaded[i].substr(0, loaded[i].find("=")) == key) { //if good key
                loaded[i] = loaded[i].substr(0, loaded[i].find("=")) + "=" + value;
                keyFounded = true;
                break;
            }
        }
    }

    if(!sectionFounded) { //section doesn't exist
        loaded.push_back("[" + section + "]");
        loaded.push_back(key + "=" + value);
    }
    else if(!keyFounded) { // section exists but key doesn't
        loaded.insert(loaded.begin() + i, key + "=" + value);
    }

    file.close();
    file.open(path, std::ios::out);

    for(uint i = 0; i < loaded.size(); i++) {
        file << loaded[i] << '\n';
    }

    file.close();
    return;
}

void writeIniInt(std::string path, std::string section, std::string key, int value) {
    writeIniString(path, section, key, std::to_string(value));
}