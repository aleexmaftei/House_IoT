#include "headers/automaticDoorLockHandler.h"

automaticDoorLockHandler::automaticDoorLockHandler(Router &router)
{
    this->setupHandlerRoutes(router);
}


void automaticDoorLockHandler::setupHandlerRoutes(Router &router)
{
    Routes::Post(router, "doorLock/unlock", Routes::bind(&automaticDoorLockHandler::unlockDoor, this));
    Routes::Post(router, "doorLock/lock", Routes::bind(&automaticDoorLockHandler::lockDoor, this));
}

void automaticDoorLockHandler::unlockDoor(const Rest::Request &request, Http::ResponseWriter response)
{
    if(doorLock.GetIsLocked())
    {
        Guard guard(doorLockMutex);

        doorLock.SetIsLocked(false);
        response.send(Http::Code::Ok, "Unlocked entrance door.");
    }
    else
    {
        response.send(Http::Code::Ok, "Entrance door is already unlocked.");
    }
}

void automaticDoorLockHandler::lockDoor(const Rest::Request &request, Http::ResponseWriter response)
{
    if(doorLock.GetIsLocked())
    {
        response.send(Http::Code::Ok, "Door is already locked.")
    }
    else
    {
        Guard guard(doorLockMutex);

        doorLock.SetIsLocked(true);
        response.send(Http::Code::Ok, "Entrance door has been locked.");
    }
}
