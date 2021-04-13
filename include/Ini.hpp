#ifndef GETINI_HPP
#define GETINI_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Ini {
public:
    Ini();
    Ini(const std::string name);

    ~Ini();

    void setName(const std::string name);

    std::string readString(const std::string section, const std::string key, const std::string def);
    int readInt(const std::string section, const std::string key, const int def);

    void writeString(const std::string section, const std::string key, const std::string value);
	void writeInt(const std::string section, const std::string key, const int value);

private:
    std::string name;
    std::fstream file;
    std::vector<std::string> loaded;
};

#endif // GETINI_HPP
