
#ifndef UNTITLED_DRIVER_H
#define UNTITLED_DRIVER_H

#endif //UNTITLED_DRIVER_H

#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Driver {
private:
    int DriverID;
    string DriverName;
    int DriverPhoneNumber;
    string vehicleNumber;

    bool isAvailable;
    double earnings;

public:
    Driver();
    Driver(int ID,string n,int p,string vn,bool isav,double e=0.0)
    : DriverID(ID),DriverName(n),DriverPhoneNumber(p),vehicleNumber(vn),isAvailable(isav),earnings(e){}
    virtual double calcDeliveryFee(double distance)=0;
    virtual double getESTtime(double distance)=0;
    virtual ~Driver();

    void setDriverID();
    void setName();
    void setNumber();
    void setVehicleNumber();
    void setEarnings();

    int getDriverID();
    string getName();
    int getNumber();
    string getVehicleNumber();
    double getEarnings();

    void showDetails();

    int assignOrder(int orderID);


};
