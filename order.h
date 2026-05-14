#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <string>

using namespace std;

class Driver {

protected:

    int DriverID;
    string DriverName;
    int DriverPhoneNumber;
    string vehicleNumber;

    bool isAvailable;
    double earnings;

public:

    Driver();

    Driver(int ID,string n,int p,
           string vn,bool isav,double e=0.0);

    virtual ~Driver();

    virtual double calcDeliveryFee(double distance)=0;

    virtual double getESTtime(double distance)=0;

    void setAvailability(bool a);

    bool getAvailability();

    string getName();

    double getEarnings();

    void addEarnings(double amount);

    void showDetails();
};

#endif
