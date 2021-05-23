#include "headers/morningAlarmHandler.h"

morningAlarmHandler::morningAlarmHandler(Router &router) {
    this->setupHandlerRoutes(router);
}

void morningAlarmHandler::setupHandlerRoutes(Router &router) {
    Routes::Get(router, "/morningAlarm/info",
                Routes::bind(&morningAlarmHandler::info, this));
    Routes::Post(router, "/morningAlarm/setDismissable/:dismissable",
                 Routes::bind(&morningAlarmHandler::setDismissable, this));
    Routes::Post(router, "/morningAlarm/addAlarm/:hour/:minutes/:duration",
                 Routes::bind(&morningAlarmHandler::addAlarm, this));
    Routes::Post(router, "/morningAlarm/addAlarm/:hour/:minutes",
                 Routes::bind(&morningAlarmHandler::addAlarm, this));
    Routes::Post(router, "/morningAlarm/removeAlarm/:hour/:minutes",
                 Routes::bind(&morningAlarmHandler::removeAlarm, this));
}

void morningAlarmHandler::setDismissable(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    morningAlarm = *morningAlarm.readJsonData();

    auto x = request.param(":dismissable");

    string message;
    try {
        auto dismissable = x.as<string>();

        if(dismissable == "true") {
            if (morningAlarm.GetIsDismissable()) {
                message = "Alarm can be dismissed already.";
            } else {
                morningAlarm.SetIsDismissable(true);
                message = "Alarm can now be dismissed.";
            }
        }
        else {
            if (!morningAlarm.GetIsDismissable()) {
                message = "Alarm can not be dismissed already.";
            } else {
                morningAlarm.SetIsDismissable(false);
                message = "Alarm now can not be dismissed.";
            }
        }
    }
    catch(...){
        jsonResponse = {
                {"actionId",      computeNewGuid()},
                {"httpCode",      Http::Code::Bad_Request},
                {"message",       "Something went wrong when trying to set dismissable alarm."}
        };
        response.send(Http::Code::Bad_Request, jsonResponse.dump(2));
    }

    jsonResponse = {
            {"actionId",      computeNewGuid()},
            {"httpCode",      Http::Code::Ok},
            {"isDismissable", morningAlarm.GetIsDismissable()},
            {"message",       message}
    };

    morningAlarm.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}

void morningAlarmHandler::addAlarm(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    morningAlarm = *morningAlarm.readJsonData();

    auto hour = request.param(":hour");
    auto minutes = request.param(":minutes");
    auto duration = (request.hasParam(":duration"))
                    ? request.param(":duration")
                    : TypedParam(":duration", "60");

    try {
        int h = hour.as<int>();
        int m = minutes.as<int>();
        int d = duration.as<int>();

        morningAlarm.AddAlarm(h, m, d);
    }
    catch (int x) {
        string message;

        switch (x) {
            case -201: {
                message = "Cannot have more than 10 registered alarms.";
                break;
            }
            case -200: {
                message = "Already have an alarm set for that time.";
                break;
            }
            case -100: {
                message = "Invalid value for hour, minutes, or duration";
                break;
            }
            default: {
                message = "Something went wrong with your request.";
                break;
            }
        }

        jsonResponse = {
                {"actionId", computeNewGuid()},
                {"httpCode", Http::Code::Bad_Request},
                {"message",  message}
        };
        response.send(Http::Code::Bad_Request, jsonResponse.dump(2));
    }

    jsonResponse = {
            {"actionId",  computeNewGuid()},
            {"httpCode",  Http::Code::Ok},
            {"alarmTime", morningAlarm.GetLastSetAlarm()},
            {"message",   "Your alarm is set for " + morningAlarm.GetLastSetAlarm()}
    };

    morningAlarm.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}

void morningAlarmHandler::removeAlarm(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    morningAlarm = *morningAlarm.readJsonData();

    auto hour = request.param(":hour");
    auto minutes = request.param(":minutes");

    string message = "Something went wrong while removing the alarm";
    try {
        int h = hour.as<int>();
        int m = minutes.as<int>();

        message = morningAlarm.DeleteAlarm(h, m);
    }
    catch (...) {
        jsonResponse = {
                {"actionId", computeNewGuid()},
                {"httpCode", Http::Code::Bad_Request},
                {"message",  message}
        };
        response.send(Http::Code::Bad_Request, jsonResponse.dump(2));
    }

    jsonResponse = {
            {"actionId", computeNewGuid()},
            {"httpCode", Http::Code::Ok},
            {"message",  message}
    };

    morningAlarm.writeJsonData();
    response.send(Http::Code::Ok, jsonResponse.dump(2));
}


void morningAlarmHandler::info(const Rest::Request &request, Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    jsonResponse = {
            {"actionId",      computeNewGuid()},
            {"isDismissable", "To set the alarm either dismissable or undismissable use /morningAlarm/setDismissable/true_or_false"},
            {"alarmList",     "To add an alarm use either /morningAlarm/addAlarm/hour/minutes/duration or /morningAlarm/addAlarm/hour/minutes"},
            {"removeAlarm",   "To remove an alarm use /morningAlarm/removeAlarm/hour/minutes"}
    };

    response.send(Http::Code::Ok, jsonResponse.dump(2));
}