#include "Driver.h"
#include "Order.h"
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

string Driver::getDriverID() const {
    return driverID;
}

void Driver::setDriverName() {
    cout << "Enter your name:";
    cin >> driverName;
}

string Driver::getDriverName() const {
    return driverName;
}

void Driver::setDriverPhone() {
    cout << "Enter your phone number: ";
    cin >> driverPhone;
}

int Driver::getDriverPhone() const {
    return driverPhone;
}

void Driver::setPlateNumber() {
    cout << "Enter plate number: ";
    cin >> plateNumber;
}

string Driver::getPlateNumber() const {
    return plateNumber;
}

void Driver::addEarnings(double amount) {
    earnings += amount;
}

double Driver::getEarnings() const {
    return earnings;
}

void Driver::setAvailability(bool a) {
    isAvailable = a;
}

bool Driver::getAvailability() const {
    return isAvailable;
}

void Driver::setAssignedOrder(Order *order) {
    assignedOrder = order;
    setAvailability(false);
}

Order *Driver::getAssignedOrder() const {
    return assignedOrder;
}

void Driver::updateOrderStatus(Order *order) {
    order->updateStatus();
}

void Driver::clearAssignedOrder() {
    assignedOrder = nullptr;
    setAvailability(true);
}

void Driver::showDetails() {
    cout << "Driver's ID: " << getDriverID() << "\n";
    cout << "Driver's name: " << getDriverName() << "\n";
    cout << "Driver's phone number: " << getDriverPhone() << "\n";
    cout << "Driver's earnings: " << getEarnings() << "\n";
    cout << "Drive's availability:" << getAvailability() << "\n";
    cout << "Plate number: " << getPlateNumber() << "\n";
}
