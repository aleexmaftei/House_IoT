
#ifndef HOUSE_IOT_AUTOMATICLIGHTS_H
#define HOUSE_IOT_AUTOMATICLIGHTS_H

#include "../../common/baseRoute.h"
#include "../../models/automaticLightsModel.h"

class automaticLights final : public baseRoute {
    automaticLightsModel lights;

    void setupHandlerRoutes(Router &) override;

    //endpoints
    void turnOnLights(const Rest::Request &, Http::ResponseWriter);

    void turnOffLights(const Rest::Request &, Http::ResponseWriter);

    void changeColor(const Rest::Request &, Http::ResponseWriter);

public:
    explicit automaticLightsHandler(Router &);
};


#endif //HOUSE_IOT_AUTOMATICLIGHTS_H
