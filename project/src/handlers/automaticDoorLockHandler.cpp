#include "headers/automaticDoorLockHandler.h"

automaticDoorLockHandler::automaticDoorLockHandler(Router &router) {
    this->setupHandlerRoutes(router);
}


void automaticDoorLockHandler::setupHandlerRoutes(Router &router) {
    Routes::Get(router, "/doorLock/info",
                Routes::bind(&automaticDoorLockHandler::info, this));
    Routes::Post(router, "/doorLock/unlock",
                 Routes::bind(&automaticDoorLockHandler::unlockDoor, this));
    Routes::Post(router, "/doorLock/lock",
                 Routes::bind(&automaticDoorLockHandler::lockDoor, this));
    Routes::Post(router, "/doorLock/setLockTime/:hour/:minutes",
                 Routes::bind(&automaticDoorLockHandler::setLockTime, this));
    Routes::Post(router, "/doorLock/reset",
                 Routes::bind(&automaticDoorLockHandler::resetLockTime, this));
}

void automaticDoorLockHandler::unlockDoor(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    doorLock = *doorLock.readJsonData();

    string message;
    if (doorLock.GetIsLocked()) {
        doorLock.SetIsLocked(false);
        message = "Unlocked entrance door.";
    } else {
        message = "Entrance door is already unlocked.";
    }

    jsonResponse = {
            {"actionId",     computeNewGuid()},
            {"httpCode",     Http::Code::Ok},
            {"isDoorLocked", doorLock.GetIsLocked()},
            {"message",      message}
    };

    doorLock.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}

void automaticDoorLockHandler::lockDoor(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    doorLock = *doorLock.readJsonData();

    string message;
    if (doorLock.GetIsLocked()) {
        message = "Door is already locked.";
    } else {
        doorLock.SetIsLocked(true);
        message = "Entrance door has been locked.";
    }

    jsonResponse = {
            {"actionId",     computeNewGuid()},
            {"httpCode",     Http::Code::Ok},
            {"isDoorLocked", doorLock.GetIsLocked()},
            {"message",      message}
    };

    doorLock.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}

void automaticDoorLockHandler::setLockTime(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    doorLock = *doorLock.readJsonData();

    auto hour = request.param(":hour");
    auto minutes = request.param(":minutes");

    try {
        int h = hour.as<int>();
        int m = minutes.as<int>();

        doorLock.SetLockingTime(h, m);
    }
    catch (...) {
        jsonResponse = {
                {"actionId", computeNewGuid()},
                {"httpCode", Http::Code::Bad_Request},
                {"message",  "Incorrect value for hour or minutes."}
        };
        response.send(Http::Code::Bad_Request, jsonResponse.dump(2));
    }

    jsonResponse = {
            {"actionId", computeNewGuid()},
            {"httpCode", Http::Code::Ok},
            {"lockTime", doorLock.GetLockingTime()},
            {"message",  "Door will automatically lock at " + doorLock.GetLockingTime()}
    };

    doorLock.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}

void automaticDoorLockHandler::resetLockTime(const Rest::Request &, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    doorLock = *doorLock.readJsonData();

    doorLock.SetLockingTime(23, 0);

    jsonResponse = {
            {"actionId", computeNewGuid()},
            {"httpCode", Http::Code::Ok},
            {"lockTime", doorLock.GetLockingTime()},
            {"message",  "Locking time has been reset. Door will automatically lock at " + doorLock.GetLockingTime()}
    };

    doorLock.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}

void automaticDoorLockHandler::info(const Rest::Request &, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    jsonResponse = {
            {"actionId", computeNewGuid()},
            {"isLocked", "To lock or unlock the door use /doorLock/lock or /doorLock/unlock respectively"},
            {"lockTime", "To set the locking time use /doorLock/setLockTime/hour/minutes"},
            {"reset",    "To reset the lockTime to the default value use /doorLock/reset"}
    };

    response.send(Http::Code::Ok, jsonResponse.dump(2));
}
