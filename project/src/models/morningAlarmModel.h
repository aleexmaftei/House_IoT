
#ifndef HOUSE_IOT_MORNINGALARMMODEL_H
#define HOUSE_IOT_MORNINGALARMMODEL_H

#include "vector"

class morningAlarmModel
{
private:
    typedef struct
    {
        int hour;
        int minutes;
        int duration;
    } Alarm;

    vector<Alarm> alarmList = vector<Alarm>();
    bool isDismissable = false;
    bool isUserInBed = false;
    Alarm mostRecentAlarm;

    static bool compareAlarmsIncreasing(Alarm a, Alarm b)
    {
        return (a.hour == b.hour)
            ? a.minutes < b.minutes
            : a.hour < b.hour;
    }

public:
    morningAlarmModel()
    {
        this->alarmList = vector<Alarm>();
    }

    void AddAlarm(int h, int m, int d)
    {
        if(alarmList.size() >= 11)
        {
            alarmList.erase(alarmList.begin(), alarmList.end());
        }

        if(alarmList.size() >= 10)
            throw (-201);

        for(auto x : alarmList)
        {
            if(x.hour == h && x.minutes == m)
                throw (-200);
        }

        if(h >= 0 && h <= 23 && m >= 0 && m <= 59 && d >= 1 && d <= 60)
        {
            Alarm newAlarm;
            newAlarm.hour = h;
            newAlarm.minutes = m;
            newAlarm.duration = d;
            alarmList.push_back(newAlarm);

            sort(alarmList.begin(), alarmList.end(), compareAlarmsIncreasing);

            mostRecentAlarm = newAlarm;
        }
        else throw (-100);
    }

    void SetAlarmList(vector<Alarm> newAlarmList)
    {
        alarmList = newAlarmList;
    }

    vector<Alarm> GetAlarmList()
    {
        return alarmList;
    }

    void SetIsDismissable(bool dismissable)
    {
        isDismissable = dismissable;
    }

    bool GetIsDismissable() const
    {
        return isDismissable;
    }

    void SetIsUserInBed(bool userInBed)
    {
        isUserInBed = userInBed;
    }

    bool GetIsUserInBed()
    {
        return isUserInBed;
    }

    string GetFormattedAlarm(int hour, int minutes)
    {
        auto alarm = FindAlarm(hour, minutes);

        string alarmString;
        alarmString += (alarm.hour < 10) ? "0" + to_string(alarm.hour) : to_string(alarm.hour);
        alarmString += ":";
        alarmString += (alarm.minutes < 10) ? "0" + to_string(alarm.minutes) : to_string(alarm.minutes);

        return alarmString;
    }

    string GetLastSetAlarm()
    {
        string alarmString;
        alarmString += (mostRecentAlarm.hour < 10) ? "0" + to_string(mostRecentAlarm.hour) : to_string(mostRecentAlarm.hour);
        alarmString += ":";
        alarmString += (mostRecentAlarm.minutes < 10) ? "0" + to_string(mostRecentAlarm.minutes) : to_string(mostRecentAlarm.minutes);
        alarmString += ", " + to_string(mostRecentAlarm.duration) + " seconds duration";

        return alarmString;
    }

    Alarm FindAlarm(int hour, int minutes)
    {
        Alarm alarm;
        for(auto x : alarmList)
        {
            if(x.hour == hour && x.minutes == minutes)
            {
                alarm = x;
                break;
            }
        }

        return alarm;
    }
};

#endif //HOUSE_IOT_MORNINGALARMMODEL_H
