#include "serverConfiguration.h"
#include "../handlers/headers/curtainsHandler.h"
#include "../handlers/headers/testConnectionHandler.h"
#include "../handlers/headers/secretDoorHandler.h"
#include "../handlers/headers/automaticDoorLockHandler.h"
#include "../handlers/headers/windowsHandler.h"
#include "../handlers/headers/automaticLightsHandler.h"
#include "../handlers/headers/morningAlarmHandler.h"

serverConfiguration::serverConfiguration(Address addr, size_t thr = 2) {
    httpEndpoint = std::make_shared<Http::Endpoint>(addr);

    auto opts = Http::Endpoint::options().threads(static_cast<int>(thr));
    httpEndpoint->init(opts);
}


void serverConfiguration::startHttp() {
    // Initialise handlers based on router settings
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serveThreaded();
}

void serverConfiguration::stop() {
    httpEndpoint->shutdown();
}

// What the server can do
void serverConfiguration::initialiseHandlers() {
    testConnectionHandler testConnectionHandler(router);
    curtainsHandler curtainsHandler(router);
    secretDoorHandler secretDoorHandler(router);
    automaticDoorLockHandler automaticDoorLockHandler(router);
    morningAlarmHandler morningAlarmHandler(router);
    windowsHandler windowsHandler(router);
    automaticLightsHandler automaticLightsHandler(router);
}
