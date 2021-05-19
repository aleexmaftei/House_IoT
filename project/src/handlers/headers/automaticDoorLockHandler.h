
#ifndef HOUSE_IOT_AUTOMATICDOORLOCKHANDLER_H
#define HOUSE_IOT_AUTOMATICDOORLOCKHANDLER_H

#include "../../common/baseRoute.h"
#include "../../models/automaticDoorLockModel.h"

class automaticDoorLockModel final : public baseRoute {
    automaticDoorLockModel doorLock;

    void setupHandlerRoutes(Router &) override;

    void unlockDoor(const Rest::Request &, Http::ResponseWriter);

    void lockDoor(const Rest::Request &, Http::ResponseWriter);

public:
    explicit automaticDoorLockHandler(Router &);
};

#endif
