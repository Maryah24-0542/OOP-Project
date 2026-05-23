#include <iostream>
#include "BikeDriver.h"

using namespace std;

BikeDriver::BikeDriver() {
    setBaseFarePerKm();
    setMaxLoad();
    cout << "Driver: " << driverName << " has been added, your ID: " << driverID << endl;
}

double BikeDriver::calcDeliveryFee(string custAdd, string restAdd) {
    if (custAdd == restAdd) {
        return baseFarePerKm;
    }
    return baseFarePerKm + 0.700;
}

double BikeDriver::calcEstTime(string custAdd, string restAdd) {
    if (custAdd == restAdd) {
        return 25;
    }
    return 40;
}

void BikeDriver::setMaxLoad() {
    cout << "Enter Max load for your bike in kg : ";
    cin >> maxLoadKg;
}

double BikeDriver::getMaxLoad() {
    return maxLoadKg;
}

void BikeDriver::setBaseFarePerKm() {
    cout << "Enter base fare for your bike: ";
    cin >> baseFarePerKm;
}

double BikeDriver::getBaseFarePerKm() {
    return baseFarePerKm;
}

void BikeDriver::setBikeModel() {
    cout << "Enter your bike model : ";
    cin >> bikeModel;
}

string BikeDriver::getBikeModel() {
    return bikeModel;
}

void BikeDriver::showDetails() {
    Driver::showDetails();
    cout << "Base fare per kilometer -> " << getBaseFarePerKm() << "\n";
    cout << "Maximum load of of bike -> " << getMaxLoad() << "\n";
    cout << "Bike model -> " << getBikeModel() << "\n";
}
