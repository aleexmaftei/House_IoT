//
// Created by Iliescu Andrei on 5/23/21.
//

#ifndef HOUSE_IOT_AUTOMATICLIGHTSMODEL_H
#define HOUSE_IOT_AUTOMATICLIGHTSMODEL_H

class automaticLightsModel {
private:
    bool areLightsOn;
public:
    void setAreLightsOn(bool value) {areLightsOn = value;}
    void getAreLightsOn() const {return areLightsOn;}

    automaticLightsModel *readJsonData() {
        json data = serverUtils::readJson(lightsDataPath);
        areLightsOn = data["areLightsOn"];

        return this;
    }

    void writeJsonData() {
        json data = {
                {"areLightsOn", areLightsOn}
        };
        serverUtils::writeJson(lightsDataPath, data);
    }
};

#endif //HOUSE_IOT_AUTOMATICLIGHTSMODEL_H
