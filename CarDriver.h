#ifndef CARDRIVER_H
#define CARDRIVER_H


#include<iostream>
using namespace std;

class CarDriver : public Driver {
private:
    int seatingCapacity;
    string carModel;
    double baseFarePerKm;
    string plateNumber;
public:
    CarDriver();
    CarDriver(int ID,string n,int p,string vn,bool isav,double e,int st,string model,double base,string num)
    : Driver(ID,n,p,vn,isav,e),seatingCapacity(st),carModel(model),baseFarePerKm(base),plateNumber(num){}

    double calcDeliveryFee(double distance) override {
        return (baseFarePerKm*distance);
    }
    double getESTtime(double distance) override {
        return (distance/40)*60;    //40 km/h average
    }
    void setSeatingCapacity();
    int getSeatingCapacity();
    void setBaseFarePerKm();
    double getBaseFarePerKm();
    void setCarModel();
    string getCarModel();
    void setPlateNumber();
    string getPlateNumber();

    void showDetails();

};
#endif
