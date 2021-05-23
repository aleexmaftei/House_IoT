
#ifndef HOUSE_IOT_BASEROUTE_H
#define HOUSE_IOT_BASEROUTE_H

#include "../configuration/serverConfiguration.h"
#include "serverUtils.h"

using namespace Rest;

class baseRoute {

protected:
    // Json format server response
    json jsonResponse;

    // Compute a new ID
    string computeNewGuid() { return xg::newGuid(); }

    /// must be implemented because it defines the HTTP request routes per handler
    virtual void setupHandlerRoutes(Router &) = 0;
};

#endif
