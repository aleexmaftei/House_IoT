
#ifndef HOUSE_IOT_SECRETDOORHANDLER_H
#define HOUSE_IOT_SECRETDOORHANDLER_H


#include "../../common/baseRoute.h"
#include "../../models/secretDoorModel.h"

class secretDoorHandler : public baseRoute {
    secretDoorModel secretDoor;

    void setupHandlerRoutes(Router &) override;

    /// endpoints
    void openSecretDoor(const Rest::Request &, Http::ResponseWriter);

    void closeSecretDoor(const Rest::Request &, Http::ResponseWriter);

    void changeSecretDoorPin(const Rest::Request &, Http::ResponseWriter);

public:
    explicit secretDoorHandler(Router &);
};


#endif
