#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <vector>

class Order;

using namespace std;

class Driver {
protected:
    static int count;
    string driverID;
    string driverName;
    int driverPhone;
    string plateNumber;
    bool isAvailable;
    double earnings;
    Order *assignedOrder;

public:
    //constructor and destructor
    Driver();

    virtual ~Driver();

    //driver functions
    virtual double calcDeliveryFee(string custAdd, string restAdd) = 0;

    virtual double calcEstTime(string custAdd, string restAdd) = 0;

    virtual void showDetails();

    void updateOrderStatus(Order *order);

    void clearAssignedOrder();

    //setters
    void setDriverID();

    void setDriverName();

    void setDriverPhone();

    void setPlateNumber();

    void setAvailability(bool a);

    void addEarnings(double amount);

    void setAssignedOrder(Order *order);


    //getters
    string getDriverID() const;

    string getDriverName() const;

    int getDriverPhone() const;

    string getPlateNumber() const;

    bool getAvailability() const;

    double getEarnings() const;

    Order *getAssignedOrder() const;
};
#endif //DRIVER_H
