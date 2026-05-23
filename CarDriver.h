#ifndef CARDRIVER_H
#define CARDRIVER_H
#include "Driver.h"
using namespace std;

class CarDriver : public Driver {
    int seatingCapacity;
    string carModel;
    double baseFarePerKm;

public:
    CarDriver();

    //driver functions
    double calcDeliveryFee(string custAdd, string restAdd) override;

    double calcEstTime(string custAdd, string restAdd) override;

    void showDetails() override;

    //setters
    void setSeatingCapacity();

    void setBaseFarePerKm();

    void setCarModel();

    //getters
    int getSeatingCapacity();

    double getBaseFarePerKm();

    string getCarModel();
};
#endif //CARDRIVER_H
