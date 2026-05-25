#include <iostream>
#include "BikeDriver.h"

using namespace std;

BikeDriver::BikeDriver() {
    setBikeModel();
    setMaxLoad();
    cout << "Driver: " << driverName << " has been added, your ID: " << driverID << endl;
}

double BikeDriver::calcDeliveryFee(string custAdd, string restAdd) {
    if (custAdd == restAdd) {
        return baseFare;
    }
    return baseFare + 2;
}

double BikeDriver::calcEstTime(string custAdd, string restAdd) {
    if (custAdd == restAdd) {
        return 15;
    }
    return 30;
}

void BikeDriver::setMaxLoad() {
    cout << "Enter Max load for your bike in kg: ";
    cin >> maxLoadKg;
}

double BikeDriver::getMaxLoad() {
    return maxLoadKg;
}

void BikeDriver::setBikeModel() {
    cout << "Enter your bike model: ";
    cin >> bikeModel;
}

string BikeDriver::getBikeModel() {
    return bikeModel;
}

void BikeDriver::showDetails() {
    Driver::showDetails();
    cout << "Bike model: " << getBikeModel() << "\n";
    cout << "Maximum load of of bike: " << getMaxLoad() << "\n";
    cout << "=========================\n";
}
