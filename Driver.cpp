# include"Driver.h"
# include<iostream>
using namespace std;


Driver::Driver(){}
Driver::~Driver(){}


void Driver::setDriverID() {
    cout<<"Enter your Driver ID:";
    cin>>DriverID;
}

int Driver::getDriverID() {
    return DriverID;
}

void Driver::setName() {
    cout<<"Enter Driver's name:";
    cin>>DriverName;
}

string Driver::getName() {
    return DriverName;
}
void Driver::setNumber() {
    cout<<"Enter Driver's phone number: ";
    cin>>DriverPhoneNumber;
}

int Driver::getNumber() {
    return DriverPhoneNumber;
}

void Driver::setVehicleNumber() {
    cout<<"Enter vehicle number: ";
    cin>>vehicleNumber;
}

string Driver::getVehicleNumber() {
    return vehicleNumber;
}

void Driver:: setEarnings() {
    cout<<"Enter Driver's Earnings :";
    cin>>earnings;
}

double Driver::getEarnings() {
    return earnings;
}

int Driver::assignOrder(int orderID) {

}


void Driver::showDetails() {
    cout<<"Driver's ID: "<<getDriverID()<<"\n";
    cout<<"Driver's name: "<<getName()<<"\n";
    cout<<"Driver's phone number: "<<getNumber()<<"\n";
    cout<<"Vehicle number: "<<getVehicleNumber()<<"\n";
    cout<<"Driver's earnings: "<<getEarnings()<<"\n";
    cout<<"Drive's availability :"<<(isAvailable? "Yes":"No")<<"\n";
}
