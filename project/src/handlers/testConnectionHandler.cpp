
#include "headers/testConnectionHandler.h"

testConnectionHandler::testConnectionHandler(Router &router) {
    this->setupHandlerRoutes(router);
}

void testConnectionHandler::setupHandlerRoutes(Router &router) {
    Routes::Get(router, "/test", Routes::bind(&testConnectionHandler::test, this));
}

void testConnectionHandler::test(const Request &request, Http::ResponseWriter response) {
    response.send(Http::Code::Ok, "Server up and running.\n");
}
