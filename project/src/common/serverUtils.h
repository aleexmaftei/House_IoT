
#ifndef HOUSE_IOT_SERVERUTILS_H
#define HOUSE_IOT_SERVERUTILS_H

#include <fstream>
#include <iomanip>
#include "../data/dataPaths.h"
#include "../../lib/nlohmann/json.hpp"

class serverUtils {
public:
    // must be used in a try-catch block
    template<typename T>
    static T convertStringToNumber(const std::string &str) {
        return stoul(str);
    }

    static nlohmann::json readJson(const std::string fileName) {
        std::ifstream fin(fileName);
        std::string x;
        if (fin.is_open()) {
            while (!fin.eof()) {
                std::string temp;
                fin >> temp;
                x += temp;
            }
        }
        nlohmann::json j = nlohmann::json::parse(x);
        return j;
    }

    static void writeJson(const std::string fileName, const nlohmann::json jsonToWrite) {
        std::ofstream out(fileName);
        out << std::setw(4) << jsonToWrite << '\n';
    }
};

#endif
