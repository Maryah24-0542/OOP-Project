#include "Driver.h"
#include "CarDriver.h"
#include <iostream>
using namespace std;

CarDriver::CarDriver() {
    setBaseFarePerKm();
    setCarModel();
    setSeatingCapacity();
    cout << "Driver: " << driverName << " has been added, your ID: " << driverID << endl;
}

void CarDriver::setSeatingCapacity() {
    cout << "Enter seating capacity of car: ";
    cin >> seatingCapacity;
}

int CarDriver::getSeatingCapacity() {
    return seatingCapacity;
}

void CarDriver::setBaseFarePerKm() {
    cout << "Enter base fare per km:";
    cin >> baseFarePerKm;
}

double CarDriver::getBaseFarePerKm() {
    return baseFarePerKm;
}

void CarDriver::setCarModel() {
    cout << "Enter Car Model:";
    cin >> carModel;
}

string CarDriver::getCarModel() {
    return carModel;
}


double CarDriver::calcDeliveryFee(string custAdd, string restAdd) {
    if (custAdd == restAdd) {
        return 1.5;
    }
    return 2.3;
}

double CarDriver::calcEstTime(string custAdd, string restAdd) {
    if (custAdd == restAdd) {
        return 20;
    }
    return 30;
}
void CarDriver::showDetails() {
    Driver::showDetails();
    cout << "Car Model -> " << getCarModel() << "\n";
    cout << "Seating capacity of the car -> " << getSeatingCapacity() << "\n";
    cout << "Base fare per kilometer -> " << getBaseFarePerKm() << "\n";
}
