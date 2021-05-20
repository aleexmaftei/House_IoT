
#ifndef HOUSE_IOT_CURTAINSHANDLER_H
#define HOUSE_IOT_CURTAINSHANDLER_H

#include "../../common/baseRoute.h"
#include "../../models/curtainsModel.h"

class curtainsHandler final : public baseRoute {
    curtainsModel curtains;
    Lock curtainsLock;

    /// must have function
    void setupHandlerRoutes(Router &) override;

    /// endpoints
    void openCurtains(const Rest::Request &, Http::ResponseWriter);

    void closeCurtains(const Rest::Request &, Http::ResponseWriter);

    void openCurtainsByPercentage(const Rest::Request &, Http::ResponseWriter);

public:
    explicit curtainsHandler(Router &);
};

#endif
