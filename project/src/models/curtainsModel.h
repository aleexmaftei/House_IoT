
#ifndef HOUSE_IOT_CURTAINSMODEL_H
#define HOUSE_IOT_CURTAINSMODEL_H

class curtainsModel {
private:
    bool areCurtainsClosed;
    double curtainsOpenPercentage;
public:
    void setAreCurtainsClosed(bool value) { areCurtainsClosed = value; }

    bool getAreCurtainsClosed() const { return areCurtainsClosed; }

    void setCurtainsOpenPercentage(double _curtainsOpenPercentage) { curtainsOpenPercentage = _curtainsOpenPercentage; }

    double getCurtainsOpenPercentage() const { return curtainsOpenPercentage; }

    curtainsModel *readJsonData() {
        json data = serverUtils::readJson(curtainsDataPath);
        areCurtainsClosed = data["areCurtainsClosed"];
        curtainsOpenPercentage = data["curtainsOpenPercentage"];

        return this;
    }

    void writeJsonData() {
        json data = {
                {"areCurtainsClosed",      areCurtainsClosed},
                {"curtainsOpenPercentage", curtainsOpenPercentage}
        };
        serverUtils::writeJson(curtainsDataPath, data);
    }
};

#endif
