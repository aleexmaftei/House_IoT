
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
        if(hour >= 0 && hour <= 23)
        {
            automaticLockingTime.hour = hour;
        }
        else throw (hour);

        if(minutes >= 0 && minutes <= 59)
        {
            automaticLockingTime.minutes = minutes;
        }
        else throw (minutes);
    }

    string GetLockingTime() const
    {
        string timeString = "";

        if(automaticLockingTime.hour < 10)
        {
            timeString = timeString + "0" + to_string(automaticLockingTime.hour);
        }
        else
        {
            timeString = timeString + to_string(automaticLockingTime.hour);
        }

        timeString = timeString + ":";

        if(automaticLockingTime.minutes < 10)
        {
            timeString = timeString + "0" + to_string(automaticLockingTime.minutes);
        }
        else
        {
            timeString = timeString + to_string(automaticLockingTime.minutes);
        }

        return timeString;
    }
};

#endif
