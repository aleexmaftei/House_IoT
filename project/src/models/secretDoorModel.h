
#ifndef HOUSE_IOT_SECRETDOORMODEL_H
#define HOUSE_IOT_SECRETDOORMODEL_H


class secretDoorModel {
private:
    bool isSecretDoorOpen;
    unsigned secretDoorPin;
    unsigned changeSecretDoorPin;

public:
    bool isSecretDoorPinCorrect(unsigned pinCode) const { return secretDoorPin == pinCode; }

    bool isChangeSecretDoorPinCorrect(unsigned changePinCode) const { return changeSecretDoorPin == changePinCode; }

    void setSecretDoorPin(unsigned _secretDoorPin) { secretDoorPin = _secretDoorPin; }

    bool getIsSecretDoorOpen() const { return isSecretDoorOpen; }

    void setIsSecretDoorOpen(bool _isDoorOpen) { isSecretDoorOpen = _isDoorOpen; }

    secretDoorModel *readJsonData() {
        json data = serverUtils::readJson(secretDoorDataPath);
        isSecretDoorOpen = data["isSecretDoorOpen"];
        secretDoorPin = data["secretDoorPin"];
        changeSecretDoorPin = data["changeSecretDoorPin"];

        return this;
    }

    void writeJsonData() {
        json data = {
                {"isSecretDoorOpen",    isSecretDoorOpen},
                {"secretDoorPin",       secretDoorPin},
                {"changeSecretDoorPin", changeSecretDoorPin},
        };
        serverUtils::writeJson(secretDoorDataPath, data);
    }
};

#endif
