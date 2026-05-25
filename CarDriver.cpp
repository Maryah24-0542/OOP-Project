#include "Driver.h"
#include "CarDriver.h"
#include <iostream>
using namespace std;

CarDriver::CarDriver() {
    setCarModel();
    cout << "Driver: " << driverName << " has been added, your ID: " << driverID << endl;
}

void CarDriver::setCarModel() {
    cout << "Enter Car Model: ";
    cin >> carModel;
}

string CarDriver::getCarModel() {
    return carModel;
}


double CarDriver::calcDeliveryFee(string custAdd, string restAdd) {
    if (custAdd == restAdd) {
        return baseFare;
    }
    return baseFare + 0.8;
}

double CarDriver::calcEstTime(string custAdd, string restAdd) {
    if (custAdd == restAdd) {
        return 10;
    }
    return 20;
}
void CarDriver::showDetails() {
    Driver::showDetails();
    cout << "Car Model: " << getCarModel() << "\n";
    cout << "=========================\n";
}
