
#ifndef HOUSE_IOT_AUTOMATICDOORLOCKMODEL_H
#define HOUSE_IOT_AUTOMATICDOORLOCKMODEL_H

#include "string.h"

class automaticDoorLockModel
{
private:
    typedef struct
    {
        int hour;
        int minutes;
    } Time;

    bool isLocked = false;
    Time automaticLockingTime;

public:
    void SetIsLocked(bool value)
    {
        isLocked = value;
    }

    bool GetIsLocked() const
    {
        return isLocked;
    }

    void SetLockingTime(int hour, int minutes)
    {
        if(hour >= 0 && hour <= 23 && minutes >= 0 && minutes <= 59)
        {
            automaticLockingTime.hour = hour;
            automaticLockingTime.minutes = minutes;
        }
        else throw(-100);
    }

    string GetLockingTime() const
    {
        string time;
        time += (automaticLockingTime.hour < 10) ? "0" + to_string(automaticLockingTime.hour) : to_string(automaticLockingTime.hour);
        time += ":";
        time += (automaticLockingTime.minutes < 10) ? "0" + to_string(automaticLockingTime.minutes) : to_string(automaticLockingTime.minutes);

        return time;
    }
};

#endif
