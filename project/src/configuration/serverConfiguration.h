#ifndef HOUSE_IOT_SERVERCONFIGURATION_H
#define HOUSE_IOT_SERVERCONFIGURATION_H


#include <iostream>
#include <mutex>
#include <cstddef>
#include <utility>
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "../../lib/nlohmann/json.hpp"
#include "../../lib/crossguid/include/crossguid/guid.hpp"

using namespace std;
using namespace Pistache;

using json = nlohmann::json;

// Class to startup the server
class serverConfiguration final {

protected:
    shared_ptr<Http::Endpoint> httpEndpoint;
    Rest::Router router;

public:
    explicit serverConfiguration(Address, size_t);

    void start();

    void initialiseHandlers();

    void stop();
};

#endif
