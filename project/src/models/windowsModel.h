
#ifndef HOUSE_IOT_WINDOWSMODEL_H
#define HOUSE_IOT_WINDOWSMODEL_H

#include "string.h"


class windowsModel {
private:
    bool areAllWindowsClosed;
    unsigned numberOfWindows;
    unsigned insidePrefTemperature;


public:
    bool getAreAllWindowsClosed() const { return areAllWindowsClosed; }

    void setAreAllWindowsClosed(bool _areAllWindowsClosed) { areAllWindowsClosed = _areAllWindowsClosed; }

    void setNumberOfWindows(int _numberOfWindows) { numberOfWindows = _numberOfWindows; }

    void setInsidePrefTemperature(double _insidePrefTemperature) { insidePrefTemperature = _insidePrefTemperature; }


    windowsModel *readJsonData() {
        json data = serverUtils::readJson(windowsDataPath);
        areAllWindowsClosed = data["areAllWindowsClosed"];
        numberOfWindows = data["numberOfWindows"];
        insidePrefTemperature = data["insidePrefTemperature"];

        return this;
    }

    void writeJsonData() {
        json data = {
                {"areAllWindowsClosed",   areAllWindowsClosed},
                {"numberOfWindows",       numberOfWindows},
                {"insidePrefTemperature", insidePrefTemperature}
        };
        serverUtils::writeJson(windowsDataPath, data);
    }
};

#endif
