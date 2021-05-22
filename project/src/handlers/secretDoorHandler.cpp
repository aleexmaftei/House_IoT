
#include "headers/secretDoorHandler.h"

secretDoorHandler::secretDoorHandler(Router &router) {
    this->setupHandlerRoutes(router);
}

void secretDoorHandler::setupHandlerRoutes(Router &router) {
    Routes::Post(router, "/secretDoor/open", Routes::bind(&secretDoorHandler::openSecretDoor, this));
    Routes::Post(router, "/secretDoor/close", Routes::bind(&secretDoorHandler::closeSecretDoor, this));
    Routes::Post(router, "/secretDoor/changePin", Routes::bind(&secretDoorHandler::changeSecretDoorPin, this));
}

void secretDoorHandler::openSecretDoor(const Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    secretDoor = *secretDoor.readJsonData();

    try {
        auto requestBody = json::parse(request.body());
        if (requestBody.contains(std::string("pinCode"))) {
            string pinCodeString = requestBody["pinCode"];
            unsigned pinCode = stoul(pinCodeString);

            if (!secretDoor.isSecretDoorPinCorrect(pinCode)) {
                throw string("Wrong Pin!");
            }

            string message = "Secret door is already open.";
            if (!secretDoor.getIsSecretDoorOpen()) {
                secretDoor.setIsSecretDoorOpen(true);
                message = "Secret door was opened.";
            }

            jsonResponse = {
                    {"actionId",         computeNewGuid()},
                    {"httpCode",         Http::Code::Ok},
                    {"isSecretDoorOpen", secretDoor.getIsSecretDoorOpen()},
                    {"message",          message}
            };

            secretDoor.writeJsonData();

            response.send(Http::Code::Ok, jsonResponse.dump(2));
        } else {
            throw string("Pin code is not inserted!");
        }
    }
    catch (string &errorMessage) {
        jsonResponse = {
                {"errorId",  computeNewGuid()},
                {"httpCode", Http::Code::Bad_Request},
                {"message",  errorMessage}
        };
        response.send(Http::Code::Bad_Request, jsonResponse.dump(2));
    }
    catch (...) {
        jsonResponse = {
                {"errorId",          computeNewGuid()},
                {"httpCode",         Http::Code::Internal_Server_Error},
                {"exceptionMessage", "Something went wrong when processing the request!"}
        };
        response.send(Http::Code::Internal_Server_Error, jsonResponse.dump(2));
    }
}

void secretDoorHandler::closeSecretDoor(const Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    secretDoor = *secretDoor.readJsonData();

    string message = "Secret door is already closed.";
    if (secretDoor.getIsSecretDoorOpen()) {
        secretDoor.setIsSecretDoorOpen(false);
        message = "Secret door was closed.";
    }

    jsonResponse = {
            {"actionId",         computeNewGuid()},
            {"httpCode",         Http::Code::Ok},
            {"isSecretDoorOpen", secretDoor.getIsSecretDoorOpen()},
            {"message",          message}
    };

    secretDoor.writeJsonData();

    response.send(Http::Code::Ok, jsonResponse.dump(2));
}

void secretDoorHandler::changeSecretDoorPin(const Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    try {
        auto requestBody = json::parse(request.body());
        if (requestBody.contains(std::string("pinCode")) && requestBody.contains(std::string("changePinCode")) &&
            requestBody.contains(std::string("newPinCode"))) {

            auto pinCode = serverUtils::convertStringToNumber<unsigned>(requestBody["pinCode"]);
            auto changePinCode = serverUtils::convertStringToNumber<unsigned>(requestBody["changePinCode"]);
            auto newPinCode = serverUtils::convertStringToNumber<unsigned>(requestBody["newPinCode"]);

            secretDoor = *secretDoor.readJsonData();

            if (!secretDoor.isSecretDoorPinCorrect(pinCode) ||
                !secretDoor.isChangeSecretDoorPinCorrect(changePinCode)) {
                throw string("Wrong Door Pin or Wrong Change Pin Code!");
            }

            secretDoor.setSecretDoorPin(newPinCode);
            jsonResponse = {
                    {"actionId", computeNewGuid()},
                    {"httpCode", Http::Code::Ok},
                    {"message",  "Secret door pin code was modified."}
            };

            secretDoor.writeJsonData();

            response.send(Http::Code::Ok, jsonResponse.dump(2));
        } else {
            throw string("Pin code or changePinCode or newPinCode not inserted!");
        }
    }
    catch (string &errorMessage) {
        jsonResponse = {
                {"errorId",  computeNewGuid()},
                {"httpCode", Http::Code::Bad_Request},
                {"message",  errorMessage}
        };
        response.send(Http::Code::Bad_Request, jsonResponse.dump(2));
    }
    catch (...) {
        jsonResponse = {
                {"errorId",          computeNewGuid()},
                {"httpCode",         Http::Code::Internal_Server_Error},
                {"exceptionMessage", "Something went wrong when processing the request!"}
        };
        response.send(Http::Code::Internal_Server_Error, jsonResponse.dump(2));
    }
}