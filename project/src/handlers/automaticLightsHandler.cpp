//
// Created by Iliescu Andrei on 5/23/21.
//

#include "headers/automaticLightsHandler.h"

automaticLightsHandler::automaticLightsHandler(Router &router) {
    this->setupHandlerRoutes(router);
}

void automaticLightsHandler::setupHandlerRoutes(Router &router) {
    Routes::Post(router, "/lights/turnOn", Routes::bind(&automaticLightsHandler::turnOnLights, this));
    Routes::Post(router, "/lights/turnOff", Routes::bind(&automaticLightsHandler::turnOffLights, this));
}

//endpoints
void automaticLightsHandler::turnOnLights(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    lights = *lights.readJsonData();

    string message = "Lights are already on!";
    if (!lights.getAreLightsOn()) {
        lights.setAreLightsOn(true);
        message = "Lights are now on!";
    }

    jsonResponse = {
            {"actionId",          computeNewGuid()},
            {"httpCode",          Http::Code::Ok},
            {"areLightsOn",       lights.getAreLightsOn()},
            {"message",           message}
    };

    lights.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}

void automaticLightsHandler::turnOffLights(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    lights = *lights.readJsonData();

    string message = "Lights are already off!";
    if (lights.getAreLightsOn()) {
        lights.setAreLightsOn(false);
        message = "Lights are now off!";
    }

    jsonResponse = {
            {"actionId",          computeNewGuid()},
            {"httpCode",          Http::Code::Ok},
            {"areLightsOn",       lights.getAreLightsOn()},
            {"message",           message}
    };

    lights.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}
