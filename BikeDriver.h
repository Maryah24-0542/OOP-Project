
#ifndef UNTITLED_BIKEDRIVER_H
#define UNTITLED_BIKEDRIVER_H
#endif //UNTITLED_BIKEDRIVER_H

#include "Driver.h"
#include<iostream>
using namespace std;
class BikeDriver : public Driver{
private:
    double baseFarePerKm;
    string bikeModel;
    double maxLoadKg;

public:
    BikeDriver(){}
    BikeDriver(int ID,string n,int p,string vn,bool isav,double e,double b,string model,double max)
        :Driver(ID,n,p,vn,isav,e),baseFarePerKm(b),bikeModel(model),maxLoadKg(max){}
    double calcDeliveryFee(double distance) override {
        return baseFarePerKm*distance;
    }

    double getESTtime(double distance) override {
        return (distance/30)*60;    //30 km/h average
    }

    void setBaseFarePerKm();
    double getBaseFarePerKm();
    void setBikeModel();
    string getBikeModel();
    void setMaxLoad();
    double getMaxLoad();
};