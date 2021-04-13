#include "Ini.hpp"

Ini::Ini() {

}

Ini::Ini(const std::string name) {
    Ini::name = name;
}

Ini::~Ini() {
    file.close();
}

void Ini::setName(const std::string name) {
    Ini::name = name;
}

std::string Ini::readString(const std::string section, const std::string key, const std::string def) {
    file.open(name, std::ios::in);
    if(!file.good()) {
        return def;
    }

    std::string line;
    std::string value;
    std::string currentKey;

    while(std::getline(file, line)) { //reading line
        value = line.substr(line.find("[") + 1); //value is name of section

        if(value.substr(0, value.find("]")) != section) { //checking section
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

            value = line.substr(line.find("=") + 1, line.size());

            file.close();
            return value;
        }
    }
    file.close();
    return def;
}

int Ini::readInt(const std::string section, const std::string key, const int def) {
    try {
        return std::atoi(readString(section, key, std::to_string(def)).c_str());
    }
    catch(...) {
        std::cerr << "Error atoi threw an exception!\n";
        return def;
    }
}

void Ini::writeString(const std::string section, const std::string key, const std::string value) {
    file.open(name, std::ios::in | std::ios::out);
    if(!file.good()) {
        file << '[' << section << ']' << '\n' << key << '=' << value;
    }

    //loading file into memory
    loaded.clear();
    std::string tmp;
    while(getline(file, tmp)) {
        loaded.push_back(tmp);
    }

    bool sectionFounded = false;
	bool keyFounded = false;

	unsigned int i = 0;

    for(; i < loaded.size(); i++) { //search section
		if(sectionFounded && loaded[i].size() > 3 && loaded[i][0] == '['){
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
    else if(!keyFounded){ // section exists but key doesn't
		loaded.insert(loaded.begin() + i, key + "=" + value);
	}

    file.close();
    remove(name.c_str());

    file.open(name, std::ios::out);

    for(unsigned int i = 0; i < loaded.size(); i++) {
        file << loaded[i] << '\n';
    }

    file.close();
    return;
}

void Ini::writeInt(const std::string section, const std::string key, const int value){
	writeString(section, key, std::to_string(value));
	return;
}
