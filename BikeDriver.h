#ifndef BIKEDRIVER_H
#define BIKEDRIVER_H

#include "Driver.h"
using namespace std;

class BikeDriver : public Driver {
    string bikeModel;
    double maxLoadKg;

public:
    BikeDriver();

    //driver functions
    double calcDeliveryFee(string custAdd, string restAdd) override;

    double calcEstTime(string custAdd, string restAdd) override;

    void showDetails() override;

    //setters
    void setBikeModel();

    void setMaxLoad();

    //getters
    string getBikeModel();

    double getMaxLoad();
};

#endif //BIKEDRIVER_H
