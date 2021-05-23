
#include "headers/automaticLightsHandler.h"

automaticLightsHandler::automaticLightsHandler(Router &router) {
    this->setupHandlerRoutes(router);
}

void automaticLightsHandler::setupHandlerRoutes(Router &router) {
    Routes::Post(router, "/lights/turnOn", Routes::bind(&automaticLightsHandler::turnOnLights, this));
    Routes::Post(router, "/lights/turnOff", Routes::bind(&automaticLightsHandler::turnOffLights, this));
    Routes::Post(router, "/lights/turnOn/:color", Routes::bind(&automaticLightsHandler::changeColor, this));
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

void automaticLightsHandler::changeColor(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    lights = *lights.readJsonData();

    string color;
    auto value = request.param(":color");

    try {
        color = value.as<string>();

        string possibleColors[4] = {"blue", "red", "white", "green"};

        int ok = 0;
        for (auto & possibleColor : possibleColors) {
            if (color == possibleColor) { ok = 1; }
        }

        if (!ok) { throw string("Colors must be blue, red, white or green!"); }

        lights.setColor(color);

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


    string message;
    if (lights.getAreLightsOn()) {
        message = string("Color is now ") + lights.getColor();
    } else {
        message = string("The lights are now on and the color was set to ") + lights.getColor();
    }
    lights.setAreLightsOn(true);

    jsonResponse = {
            {"actionId", computeNewGuid()},
            {"httpCode", Http::Code::Ok},
            {"lights", {
                                 {"areLightsOn", lights.getAreLightsOn()},
                                 {"color", lights.getColor()}
                         }},
            {"message",  message}
    };

    lights.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}



