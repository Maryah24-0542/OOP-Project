#ifndef CARDRIVER_H
#define CARDRIVER_H
#include "Driver.h"
using namespace std;

class CarDriver : public Driver {
    string carModel;

public:
    CarDriver();

    //driver functions
    double calcDeliveryFee(string custAdd, string restAdd) override;

    double calcEstTime(string custAdd, string restAdd) override;

    void showDetails() override;

    //setters
    void setCarModel();

    //getters
    string getCarModel();
};
#endif //CARDRIVER_H
