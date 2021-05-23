
#ifndef HOUSE_IOT_WINDOWSMODEL_H
#define HOUSE_IOT_WINDOWSMODEL_H

#include "string.h"


class windowsModel {
private:
    bool areAllWindowsClosed;
    bool isRaining;
    unsigned insidePrefTemperature;


public:
    bool getAreAllWindowsClosed() const { return areAllWindowsClosed; }

    bool getIsRaining() const { return isRaining; }

    unsigned getInsidePrefTemperature() const { return insidePrefTemperature; }

    void setAreAllWindowsClosed(bool _areAllWindowsClosed) { areAllWindowsClosed = _areAllWindowsClosed; }

    void setIsRaining(bool _isRaining) { isRaining = _isRaining; }

    void setInsidePrefTemperature(double _insidePrefTemperature) { insidePrefTemperature = _insidePrefTemperature; }


    windowsModel *readJsonData() {
        json data = serverUtils::readJson(windowsDataPath);
        areAllWindowsClosed = data["areAllWindowsClosed"];
        isRaining = data["isRaining"];
        insidePrefTemperature = data["insidePrefTemperature"];

        return this;
    }

    void writeJsonData() {
        json data = {
                {"areAllWindowsClosed",   areAllWindowsClosed},
                {"isRaining",       isRaining},
                {"insidePrefTemperature", insidePrefTemperature}
        };
        serverUtils::writeJson(windowsDataPath, data);
    }
};

#endif
