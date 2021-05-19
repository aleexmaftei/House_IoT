
#ifndef HOUSE_IOT_CURTAINSMODEL_H
#define HOUSE_IOT_CURTAINSMODEL_H

class curtainsModel {
private:
    bool areCurtainsClosed = false;
    double curtainsOpenPercentage = 0.0;
public:
    void setAreCurtainsClosed(bool value) { areCurtainsClosed = value; }

    bool getAreCurtainsClosed() const { return areCurtainsClosed; }

    void setCurtainsOpenPercentage(double _curtainsOpenPercentage) { curtainsOpenPercentage = _curtainsOpenPercentage; }

    double getCurtainsOpenPercentage() const { return curtainsOpenPercentage; }
};

#endif
