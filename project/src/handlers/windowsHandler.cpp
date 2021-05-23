
#include "headers/windowsHandler.h"

windowsHandler::windowsHandler(Router &router) {
    this->setupHandlerRoutes(router);
}


void windowsHandler::setupHandlerRoutes(Router &router) {
    Routes::Post(router, "/windowsLock/openWindows",
                 Routes::bind(&windowsHandler::openWindows, this));
    Routes::Post(router, "/windowsLock/closeWindows",
                 Routes::bind(&windowsHandler::closeWindows, this));
    Routes::Post(router, "/windowsLock/:rain",
                 Routes::bind(&windowsHandler::windowsWithRain, this));
    //Routes::Post(router, "/windowsLock/:tempMax/:F",
    //           Routes::bind(&windowsHandler::closeWindowsWithTemp, this));
}


void windowsHandler::windowsWithRain(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    windowsLock = *windowsLock.readJsonData();


}

void windowsHandler::openWindows(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    windowsLock = *windowsLock.readJsonData();

    string msg;
    if (windowsLock.getAreAllWindowsClosed()) {
        windowsLock.setAreAllWindowsClosed(false);
        msg = "All the windows are opened now.";
    } else
        msg = "All the windows are already opened.";
    jsonResponse = {
            {"actionId",          computeNewGuid()},
            {"httpCode",          Http::Code::Ok},
            {"areWindowsClosed?", windowsLock.getAreAllWindowsClosed()},
            {"message",           msg}
    };
    windowsLock.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}

void windowsHandler::closeWindows(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    windowsLock = *windowsLock.readJsonData();


    string msg;
    if (windowsLock.getAreAllWindowsClosed()) {
        msg = "All the windows already closed.";
    } else {
        windowsLock.setAreAllWindowsClosed(true);
        msg = "All the windows have been closed.";
    }
    jsonResponse = {
            {"actionId",          computeNewGuid()},
            {"httpCode",          Http::Code::Ok},
            {"areWindowsClosed?", windowsLock.getAreAllWindowsClosed()},
            {"message",           msg}
    };

    windowsLock.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}



