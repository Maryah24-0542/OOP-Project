#include "Driver.h"
#include <bits/stdc++.h>
using namespace std;

int Driver::count = 1;

Driver::Driver() {
    setDriverName();
    setDriverPhone();
    setPlateNumber();
    setAvailability(true);
    earnings = 0;
    setDriverID();
}

Driver::~Driver() {
}

void Driver::setDriverID() {
    // create string stream to format the ID
    stringstream ss;
    // format ID as D-0001, D-0002, etc.
    ss << "D-" << setfill('0') << setw(4) << count++;
    // return the formatted string
    driverID = ss.str();
}

string Driver::getDriverID() {
    return driverID;
}

void Driver::setDriverName() {
    cout << "Enter your name:";
    cin >> driverName;
}

string Driver::getDriverName() {
    return driverName;
}

void Driver::setDriverPhone() {
    cout << "Enter your phone number: ";
    cin >> driverPhone;
}

int Driver::getDriverPhone() {
    return driverPhone;
}

void Driver::setPlateNumber() {
    cout << "Enter plate number: ";
    cin >> plateNumber;
}

string Driver::getPlateNumber() {
    return plateNumber;
}

void Driver::addEarnings(double amount) {
    earnings += amount;
}

double Driver::getEarnings() {
    return earnings;
}

void Driver::setAvailability(bool a) {
    isAvailable = a;
}

bool Driver::getAvailability() {
    return isAvailable;
}
void Driver::updateOrderStatus(Order *order) {
    order->updateStatus();
}

void Driver::showDetails() {
    cout << "Driver's ID: " << getDriverID() << "\n";
    cout << "Driver's name: " << getDriverName() << "\n";
    cout << "Driver's phone number: " << getDriverPhone() << "\n";
    cout << "Driver's earnings: " << getEarnings() << "\n";
    cout << "Drive's availability:" << getAvailability() << "\n";
    cout << "Plate number: " << getPlateNumber() << "\n";
}
