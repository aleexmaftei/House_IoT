
#ifndef HOUSE_IOT_SERVERUTILS_H
#define HOUSE_IOT_SERVERUTILS_H

#include <fstream>
#include "../data/dataPaths.h"
#include <iostream>

class serverUtils {
public:
    // must be used in a try-catch block
    template<typename T>
    static T convertStringToNumber(const std::string &str) {
        return stoul(str);
    }

    static json readJson(string fileName) {
        ifstream fin(fileName);
        string x;
        if (fin.is_open()) {
            while (!fin.eof()) {
                string temp;
                fin >> temp;
                x += temp;
            }
        }
        json j = nlohmann::json::parse(x);
        return j;
    }

    static void writeJson(string fileName, json jsonToWrite) {
        ofstream out(fileName);
        out << setw(4) << jsonToWrite << '\n';
    }
};

#endif
