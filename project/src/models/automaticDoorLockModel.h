
#ifndef HOUSE_IOT_AUTOMATICDOORLOCKMODEL_H
#define HOUSE_IOT_AUTOMATICDOORLOCKMODEL_H

class automaticDoorLockModel {
private:
    bool isLocked = false;
    Datetime lockingHour = new Datetime;

public:
    void setIsLocked(bool value)
    {
        isLocked = value;
    }

    bool GetIsLocked() const
    {
        return isLocked;
    }

    void SetLockingHour(Datetime value)
    {
        lockingHour = value;
    }

    Datetime GetLockingHour()
    {
        return lockingHour;
    }
};

#endif
