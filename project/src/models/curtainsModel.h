
#ifndef HOUSE_IOT_CURTAINSMODEL_H
#define HOUSE_IOT_CURTAINSMODEL_H

class curtainsModel {
private:
    bool areCurtainsClosed = false;

public:
    void setAreCurtainsClosed(bool value) { areCurtainsClosed = value; }

    bool getAreCurtainsClosed() const { return areCurtainsClosed; }
};

#endif
