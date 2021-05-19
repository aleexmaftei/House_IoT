#include "headers/curtainsHandler.h"


curtainsHandler::curtainsHandler(Router &router) {
    this->setupHandlerRoutes(router);
}

void curtainsHandler::setupHandlerRoutes(Router &router) {
    Routes::Post(router, "/curtains/open/:curtainsOpenPercentage",
                 Routes::bind(&curtainsHandler::openCurtainsByPercentage, this));
    Routes::Post(router, "/curtains/open", Routes::bind(&curtainsHandler::openCurtains, this));
    Routes::Post(router, "/curtains/close", Routes::bind(&curtainsHandler::closeCurtains, this));
}

/// endpoints --- do NOT make them static
void curtainsHandler::openCurtains(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    string message = "Curtains are already fully opened.";
    if (curtains.getAreCurtainsClosed()) {
        Guard guard(curtainsLock);

        curtains.setAreCurtainsClosed(false);
        message = "Curtains are now fully opened.";
    }

    jsonResponse = {
            {"actionId",          computeNewGuid()},
            {"httpCode",          Http::Code::Ok},
            {"areCurtainsClosed", curtains.getAreCurtainsClosed()},
            {"message",           message}
    };

    response.send(Http::Code::Ok, jsonResponse.dump(2));
}

void curtainsHandler::closeCurtains(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    string message = "Curtains are already fully closed.";
    if (!curtains.getAreCurtainsClosed()) {
        Guard guard(curtainsLock);

        curtains.setAreCurtainsClosed(true);
        message = "Curtains are now fully closed.";
    }

    jsonResponse = {
            {"actionId",          computeNewGuid()},
            {"httpCode",          Http::Code::Ok},
            {"areCurtainsClosed", curtains.getAreCurtainsClosed()},
            {"message",           message}
    };

    response.send(Http::Code::Ok, jsonResponse.dump(2));
}

void curtainsHandler::openCurtainsByPercentage(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    double curtainsOpenPercentage;
    auto value = request.param(":curtainsOpenPercentage");

    try {
        curtainsOpenPercentage = value.as<double>();

        curtains.setAreCurtainsClosed(false);

        if (curtainsOpenPercentage <= 0.0) {
            curtainsOpenPercentage = 0.0;
            curtains.setAreCurtainsClosed(true);
        } else if (curtainsOpenPercentage > 100.0) {
            curtainsOpenPercentage = 100.0;
        }

        curtains.setCurtainsOpenPercentage(curtainsOpenPercentage);
    }
    catch (...) {
        jsonResponse = {
                {"errorId",  computeNewGuid()},
                {"httpCode", Http::Code::Bad_Request},
                {"message",  "Parameter is not a number!"}
        };
        response.send(Http::Code::Bad_Request, jsonResponse.dump(2));
    }

    string message;
    if (curtains.getCurtainsOpenPercentage() == 0.0) {
        message = "Curtains are now fully closed!";
    } else if (curtains.getCurtainsOpenPercentage() != 100.0) {
        message = string("Curtains are now ") + to_string(curtains.getCurtainsOpenPercentage()) + string("% opened.");
    } else {
        message = "Curtains are now fully opened!";
    }

    jsonResponse = {
            {"actionId", computeNewGuid()},
            {"httpCode", Http::Code::Ok},
            {"curtains", {
                                 {"areCurtainClosed", curtains.getAreCurtainsClosed()},
                                 {"curtainsOpenedPercentage", curtains.getCurtainsOpenPercentage()}
                         }},
            {"message",  message}
    };

    response.send(Http::Code::Ok, jsonResponse.dump(2));
}