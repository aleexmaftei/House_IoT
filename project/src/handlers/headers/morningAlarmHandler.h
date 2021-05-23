
#ifndef HOUSE_IOT_MORNINGALARMHANDLER_H
#define HOUSE_IOT_MORNINGALARMHANDLER_H

#include "../../common/baseRoute.h"
#include "../../models/morningAlarmModel.h"

class morningAlarmHandler final : public baseRoute {
    morningAlarmModel morningAlarm;

    void setDismissable(const Rest::Request &, Http::ResponseWriter);

    void addAlarm(const Rest::Request &, Http::ResponseWriter);

    void removeAlarm(const Rest::Request &, Http::ResponseWriter);

    void info(const Rest::Request &, Http::ResponseWriter);

    void setupHandlerRoutes(Router &) override;

public:
    explicit morningAlarmHandler(Router &);
};

#endif //HOUSE_IOT_MORNINGALARMHANDLER_H
