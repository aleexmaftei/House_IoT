
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
    Routes::Post(router, "/windowsLock/:temp/:tempMax/:F",
                 Routes::bind(&windowsHandler::closeWindowsWithTemp, this));
    Routes::Get(router, "/windowsLock/userSettings", Routes::bind(&windowsHandler::getWindowsLockUserSettings, this));
}

void windowsHandler::getWindowsLockUserSettings(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    windowsLock = *windowsLock.readJsonData();
    jsonResponse = {
            {"actionId",     computeNewGuid()},
            {"userSettings", {
                                     {"areAllWindowsClosed", windowsLock.getAreAllWindowsClosed()},
                                     {"insidePrefTemperature", windowsLock.getInsidePrefTemperature()},
                                     {"isRaining", windowsLock.getIsRaining()}
                             }}
    };

    response.send(Http::Code::Ok, jsonResponse.dump(2));
}

void windowsHandler::closeWindowsWithTemp(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    windowsLock = *windowsLock.readJsonData();

    auto tempRequestString = request.param(":temp");
    auto maxTempRequestString = request.param(":tempMax");
    auto tempScaleRequestString = request.param(":F");

    try {
        auto temp = tempRequestString.as<unsigned>();
        auto maxTemp = maxTempRequestString.as<unsigned>();
        auto tempScale = tempScaleRequestString.as<string>();

        if (tempScale == "F") {
            double maxTempInCelsius = (maxTemp - 32) / 1.8;
            double tempInCelsius = (temp - 32) / 1.8;
            if (tempInCelsius >= 40 || maxTempInCelsius >= 40) {
                throw string("In loc sa deschidem geamurile, nu doriti sa sunam la 112?");
            }
            if (tempInCelsius >= maxTempInCelsius) {
                windowsLock.setAreAllWindowsClosed(false);
            }
        } else if (tempScale == "C") {
            if (temp >= 40 || maxTemp >= 40) {
                throw string("In loc sa deschidem geamurile, nu doriti sa sunam la 112?");
            }
            if (temp >= maxTemp) {
                windowsLock.setAreAllWindowsClosed(false);
            }
        } else {
            throw string("Wrong temperature scale input! Try F or C!");
        }
    }
    catch (string &errorMessage) {
        jsonResponse = {
                {"errorId",  computeNewGuid()},
                {"httpCode", Http::Code::Bad_Request},
                {"message",  errorMessage}
        };
        response.send(Http::Code::Bad_Request, jsonResponse.dump(2));
    }
    catch (...) {
        jsonResponse = {
                {"errorId",          computeNewGuid()},
                {"httpCode",         Http::Code::Internal_Server_Error},
                {"exceptionMessage", "Something went wrong when processing the request!"}
        };
        response.send(Http::Code::Internal_Server_Error, jsonResponse.dump(2));
    }

    string msg;
    if (windowsLock.getAreAllWindowsClosed()) {
        msg = "The temperature is perfect! here is no need to open the windows!";
    }
    else {
        msg = "The temperature inside the house was getting a bit uncomfortable. The windows were opened!";
    }
    jsonResponse = {
            {"actionId", computeNewGuid()},
            {"httpCode", Http::Code::Ok},
            {"windows",  {
                                 {"areAllWindowsClosed", windowsLock.getAreAllWindowsClosed()}
                         }},
            {"message",  msg}
    };

    windowsLock.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}

void windowsHandler::windowsWithRain(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    windowsLock = *windowsLock.readJsonData();

    auto isRainingRequestString = request.param(":rain");

    try {
        auto isRainingString = isRainingRequestString.as<string>();
        bool isRaining = (isRainingString == "true" || isRainingString == "rain" || isRainingString == "isRaining");

        if (isRaining) {
            windowsLock.setAreAllWindowsClosed(true);
            windowsLock.setIsRaining(true);
        } else {
            windowsLock.setAreAllWindowsClosed(false);
            windowsLock.setIsRaining(false);
        }

    } catch (...) {
        jsonResponse = {
                {"errorId",  computeNewGuid()},
                {"httpCode", Http::Code::Bad_Request},
                {"message",  "Parameter is not a string!"}
        };
        response.send(Http::Code::Bad_Request, jsonResponse.dump(2));
    }
    string msg;
    if (windowsLock.getAreAllWindowsClosed()) {
        msg = "It is raining! All windows are now closed!";
    } else {
        msg = "The rain stopped! All windows are now opened!";
    }
    jsonResponse = {
            {"actionId", computeNewGuid()},
            {"httpCode", Http::Code::Ok},
            {"windows",  {
                                 {"areAllWindowsClosed", windowsLock.getAreAllWindowsClosed()},
                                 {"isRaining", windowsLock.getIsRaining()}
                         }},
            {"message",  msg}
    };

    windowsLock.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}

void windowsHandler::openWindows(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    windowsLock = *windowsLock.readJsonData();

    string msg;
    if (!windowsLock.getIsRaining()) {
        if (windowsLock.getAreAllWindowsClosed()) {
            windowsLock.setAreAllWindowsClosed(false);
            msg = "All the windows are opened now.";
        } else {
            msg = "All the windows are already opened.";
        }
    } else {
        msg = "It is pouring outside! You can't open the windows right now!";
    }
    jsonResponse = {
            {"actionId",         computeNewGuid()},
            {"httpCode",         Http::Code::Ok},
            {"areWindowsClosed", windowsLock.getAreAllWindowsClosed()},
            {"message",          msg}
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
            {"actionId",         computeNewGuid()},
            {"httpCode",         Http::Code::Ok},
            {"areWindowsClosed", windowsLock.getAreAllWindowsClosed()},
            {"message",          msg}
    };

    windowsLock.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}



