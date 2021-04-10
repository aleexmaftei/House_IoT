#include "headers/curtainsHandler.h"


curtainsHandler::curtainsHandler(Router &router) {
    this->setupHandlerRoutes(router);
}

void curtainsHandler::setupHandlerRoutes(Router &router) {
    Routes::Post(router, "/curtains/open", Routes::bind(&curtainsHandler::openCurtains, this));
    Routes::Post(router, "/curtains/close", Routes::bind(&curtainsHandler::closeCurtains, this));
}

/// endpoints --- do NOT make them static
void curtainsHandler::openCurtains(const Rest::Request &request, Http::ResponseWriter response) {
    if (curtains.getAreCurtainsClosed()) {
        Guard guard(curtainsLock);

        curtains.setAreCurtainsClosed(false);
        response.send(Http::Code::Ok, "Curtains are now fully opened.\n");
    }
    response.send(Http::Code::Ok, "Curtains are already fully opened.\n");
}

void curtainsHandler::closeCurtains(const Rest::Request &request, Http::ResponseWriter response) {
    if (!curtains.getAreCurtainsClosed()) {
        Guard guard(curtainsLock);

        curtains.setAreCurtainsClosed(true);
        response.send(Http::Code::Ok, "Curtains are now fully closed.\n");
    }
    response.send(Http::Code::Ok, "Curtains are already fully closed.\n");
}
