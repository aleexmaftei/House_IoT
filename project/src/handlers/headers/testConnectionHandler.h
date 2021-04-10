
#ifndef HOUSE_IOT_TESTCONNECTIONHANDLER_H
#define HOUSE_IOT_TESTCONNECTIONHANDLER_H


#include "../../common/baseRoute.h"

class testConnectionHandler : public baseRoute {

    void setupHandlerRoutes(Router &) override;

    void test(const Rest::Request &, Http::ResponseWriter);

public:
    explicit testConnectionHandler(Router &);
};


#endif
