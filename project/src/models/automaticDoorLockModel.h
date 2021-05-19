
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

        Time(int h, int m)
        {
            hour = h;
            minutes = m;
        }
    } Time;

    bool isLocked = false;
    Time automaticLockingTime = Time(23, 0);

public:
    void SetIsLocked(bool value)
    {
        isLocked = value;
    }

    bool GetIsLocked() const
    {
        return isLocked;
    }

    bool SetLockingTime(int hour, int minutes)
    {
        if(hour >= 0 && hour <= 23 && minutes >= 0 && minutes <= 59)
        {
            automaticLockingTime = Time(hour, minutes);
            return true;
        }
        else false;
    }

    char* GetLockingTime()
    {
        char hourString[6];
        char minutesString[2];

        if(automaticLockingTime.hour < 10)
        {
            sprintf(hourString, "0%d", automaticLockingTime.hour);
        }
        else
        {
            sprintf(hourString, "%d", automaticLockingTime.hour);
        }

        if(automaticLockingTime.minutes < 10)
        {
            sprintf(minutesString, "0%d", automaticLockingTime.minutes);
        }
        else
        {
            sprintf(minutesString, "%d", automaticLockingTime.minutes);
        }

        strncat(hourString, ":");
        strncat(hourString, minutesString);

        return *hourString;
    }
};

#endif
