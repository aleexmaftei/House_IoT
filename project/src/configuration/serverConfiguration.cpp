#include "serverConfiguration.h"
#include "../handlers/headers/curtainsHandler.h"
#include "../handlers/headers/testConnectionHandler.h"
#include "../handlers/headers/secretDoorHandler.h"

serverConfiguration::serverConfiguration(Address addr, size_t thr = 2) {
    httpEndpoint = std::make_shared<Http::Endpoint>(addr);

    auto opts = Http::Endpoint::options().threads(static_cast<int>(thr));
    httpEndpoint->init(opts);
}


void serverConfiguration::start() {
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
}
