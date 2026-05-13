

#include <iostream>
using namespace std;
#include "BikeDriver.h"

void BikeDriver::setMaxLoad() {
    cout<<"Enter Max load for bike in kg : ";
    cin>>maxLoadKg;
}

double BikeDriver::getMaxLoad() {
    return maxLoadKg;
}

void BikeDriver::setBaseFarePerKm() {
    cout<<"Enter base fare for bike: ";
    cin>>baseFarePerKm;
}

double BikeDriver::getBaseFarePerKm() {
    return baseFarePerKm;
}


void BikeDriver::setBikeModel() {
    cout<<"Enter Bike model : ";
    cin>>bikeModel;
}

string BikeDriver::getBikeModel() {
    return bikeModel;
}

void BikeDriver::setPlateNumber() {
    cout<<"Enter plate number: ";
    cin>>plateNumber;
}

string BikeDriver::getPlateNumber() {
    return plateNumber;
}


void BikeDriver::showDetails() {
    cout<<"Base Fare per kilometer: "<<getBaseFarePerKm()<<"\n";
    cout<<"Maximum load of of bike: "<<getMaxLoad()<<"\n";
    cout<<"Bike model: "<<getBikeModel()<<"\n";
    cout<<"Plate number -> "<<getPlateNumber()<<"\n";
    cout<<"Delivery fee is -> "<<calcDeliveryFee()<<"\n";
    cout<<"Estimated time for delivery -> "<<getESTtime()<<"\n";
    
    
}

