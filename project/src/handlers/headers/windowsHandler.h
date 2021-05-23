
#ifndef HOUSE_IOT_WINDOWSHANDLER_H
#define HOUSE_IOT_WINDOWSHANDLER_H


#include "../../common/baseRoute.h"
#include "../../models/windowsModel.h"

class windowsHandler : public baseRoute {
    windowsModel windowsLock;

    void setupHandlerRoutes(Router &) override;

    void closeWindows(const Rest::Request &, Http::ResponseWriter);

    void openWindows(const Rest::Request &, Http::ResponseWriter);

    void closeWindowsWithTemp(const Rest::Request &, Http::ResponseWriter);

    void windowsWithRain(const Rest::Request &, Http::ResponseWriter);

public:
    explicit windowsHandler(Router &);
};


#endif
