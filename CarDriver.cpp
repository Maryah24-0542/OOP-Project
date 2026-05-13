#include "Driver.h"
#include "CarDriver.h"
#include<iostream>
using namespace std;



CarDriver::CarDriver() {

}

void CarDriver::setSeatingCapacity() {
    cout<<"Enter seating capacity of car: ";
    cin>>seatingCapacity;
}

int CarDriver::getSeatingCapacity() {
    return seatingCapacity;
}

void CarDriver::setBaseFarePerKm() {
    cout<<"Enter base fare per km :";
    cin>>baseFarePerKm;
}

double CarDriver::getBaseFarePerKm() {
    return baseFarePerKm;
}

void CarDriver::setCarModel() {
    cout<<"Enter Car Model :";
    cin>>carModel;
}
string CarDriver::getCarModel() {
    return carModel;
}

void CarDriver::setPlateNumber() {
    cout<<"Enter plate number : ";
    cin>>plateNumber;
}

string CarDriver::getPlateNumber() {
    return plateNumber;
}

void CarDriver::showDetails() {
    cout<<"Car Model :"<<getCarModel()<<"\n";
    cout<<"Seating capacity of the car : "<<getSeatingCapacity()<<"\n";
    cout<<"Base fare per kilometer :"<<getBaseFarePerKm()<<"\n";
    cout<<"Delivery fee is : "<<calcDeliveryFee()<<"\n";
    cout<<"Estimated time for delivery : "<<getESTtime()<<"\n";
    cout<<"Plate number -> "<<getPlateNumber()<<"\n";

}
