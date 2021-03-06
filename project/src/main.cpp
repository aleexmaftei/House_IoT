
#include <csignal>
#include "handlers/headers/curtainsHandler.h"
#include "handlers/headers/automaticDoorLockHandler.h"
#include "configuration/mqttServerConfiguration.h"
#include "handlers/headers/morningAlarmHandler.h"

using namespace std;

int main() {
    // This code is needed for graceful shutdown of the server when no longer needed.
    sigset_t signals;
    if (sigemptyset(&signals) != 0
        || sigaddset(&signals, SIGTERM) != 0
        || sigaddset(&signals, SIGINT) != 0
        || sigaddset(&signals, SIGHUP) != 0
        || pthread_sigmask(SIG_BLOCK, &signals, nullptr) != 0) {
        perror("Install signal handler failed!");
        return 1;
    }

    // Set a port on which your server to communicate
    Port port(9080);

    // Number of threads used by the server
    int thr = 2;

    Address addr(Ipv4::any(), port);

    // Initialize the server
    serverConfiguration serverConfig(addr, thr);

    // Initialise http handlers that define what the server can do
    serverConfig.initialiseHandlers();

    // Start http server
    serverConfig.startHttp();

    // Start mqtt
    json j = {};
    mqttServerConfiguration::messageMqttWithNewProcess(true, nullptr, j);

    // Code that waits for the shutdown signal for the server
    int signal = 0;
    int status = sigwait(&signals, &signal);
    if (status == 0) {
        std::cout << "received signal " << signal << std::endl;
    } else {
        std::cerr << "sigwait returns " << status << std::endl;
    }

    serverConfig.stop();
}
