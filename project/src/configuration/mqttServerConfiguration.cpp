

#include "mqttServerConfiguration.h"

/*
 *
 *  useDefaultMqttMessages (MANDATORY) : false for custom messages
 *  topic : MQTT topic for requests                             - can be empty JUST for default messages
 *  jsonToPublish : message for the MQTT subscribers            - can be empty
 *
 * */
void mqttServerConfiguration::messageMqttWithNewProcess(bool useDefaultMqttMessages, const char *topic,
                                                        const json &jsonToPublish) {
    int pid = fork();

    if (pid == 0) {
        startMqttPublisher(useDefaultMqttMessages, topic, jsonToPublish);
    }
}

// Used when you do not want to make a new process
void
mqttServerConfiguration::startMqttPublisher(bool useDefaultMqttMessages, const char *topic, const json &jsonToPublish) {
    struct mosquitto *mqttConnection;
    mosquitto_lib_init();

    // create a new client as publisher
    mqttConnection = mosquitto_new("publisher", true, nullptr);

    // connect to port 1883
    int rc = mosquitto_connect(mqttConnection, "localhost", 1883, 90);
    if (rc != 0) {
        mosquitto_destroy(mqttConnection);
        perror("Something went wrong with mosquitto connection!");
    }

    string message;
    if (useDefaultMqttMessages) {
        /// default actions at startup for mqtt
        // get current curtains settings
        message = serverUtils::readJson(curtainsDataPath).dump();
        mosquitto_publish(mqttConnection, nullptr, "curtains/currentUserSettings", message.size(), message.c_str(),
                          0, true);

        // check if secret door is locked
        message = serverUtils::readJson(secretDoorDataPath)["isSecretDoorOpen"].dump();
        mosquitto_publish(mqttConnection, nullptr, "secretDoor/isSecretDoorOpen", message.size(), message.c_str(),
                          0, true);

        // check if entrance door is unlocked
        message = serverUtils::readJson(automaticDoorLockDataPath)["isLocked"].dump();
        mosquitto_publish(mqttConnection, nullptr, "automaticDoorLock/isLocked", message.size(), message.c_str(),
                          0, true);
    } else {
        /// custom actions
        if (topic == NULL) {
            perror("Topic can not be null when useDefaultMqttMessages is set to false!");
        } else {
            message = jsonToPublish.dump();
            mosquitto_publish(mqttConnection, nullptr, topic, message.size(), message.c_str(), 0, true);
        }
    }

    mosquitto_disconnect(mqttConnection);
    mosquitto_destroy(mqttConnection);

    mosquitto_lib_cleanup();
}
