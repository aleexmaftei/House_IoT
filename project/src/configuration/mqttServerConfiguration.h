
#ifndef HOUSE_IOT_MQTTSERVERCONFIGURATION_H
#define HOUSE_IOT_MQTTSERVERCONFIGURATION_H

#include <iostream>
#include <mosquitto.h>
#include <unistd.h>
#include <csignal>
#include <sys/wait.h>
#include "../../lib/nlohmann/json.hpp"
#include "../../lib/crossguid/include/crossguid/guid.hpp"
#include "../common/serverUtils.h"
#include "../data/dataPaths.h"

using namespace std;

using json = nlohmann::json;

class mqttServerConfiguration {
public:
    static void messageMqttWithNewProcess(bool useDefaultMqttMessages, const char *topic, const json &jsonToPublish);

    static void startMqttPublisher(bool useDefaultMqttMessages, const char *topic, const json &jsonToPublish);

    static void startMqttSubscriber(struct mosquitto *mosq);

    static void on_message(struct mosquitto *, void *, const struct mosquitto_message *);
};


#endif
