
#ifndef HOUSE_IOT_SECRETDOORMODEL_H
#define HOUSE_IOT_SECRETDOORMODEL_H


class secretDoorModel {
private:
    bool isSecretDoorOpen = false;
    inline static unsigned secretDoorPin = 1234;
    inline static unsigned changeSecretDoorPin = 1234;

public:
    bool isSecretDoorPinCorrect(unsigned pinCode) const { return secretDoorPin == pinCode; }

    bool isChangeSecretDoorPinCorrect(unsigned changePinCode) const { return changeSecretDoorPin == changePinCode; }

    void setChangeSecretDoorPin(unsigned changePinCode) { changeSecretDoorPin = changePinCode; }

    bool getIsSecretDoorOpen() const { return isSecretDoorOpen; }

    void setIsSecretDoorOpen(bool _isDoorOpen) { isSecretDoorOpen = _isDoorOpen; }
};

#endif
