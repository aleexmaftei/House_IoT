

#ifndef HOUSE_IOT_AUTOMATICLIGHTSMODEL_H
#define HOUSE_IOT_AUTOMATICLIGHTSMODEL_H

class automaticLightsModel {
private:
    bool areLightsOn;
    bool color;
public:
    void setAreLightsOn(bool value) { areLightsOn = value; }
    void getAreLightsOn() const { return areLightsOn; }

    void setColor(string value) { color = value; }
    void getColor() const { return color; }

    automaticLightsModel *readJsonData() {
        json data = serverUtils::readJson(lightsDataPath);
        areLightsOn = data["areLightsOn"];
        color = data["color"];

        return this;
    }

    void writeJsonData() {
        json data = {
                {"areLightsOn", areLightsOn},
                {"color", color}
        };
        serverUtils::writeJson(lightsDataPath, data);
    }
};

#endif
