#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>

#include "Customer.h"
#include "Restaurant.h"
#include "Driver.h"
#include "Payment.h"

using namespace std;

class Order {

private:

    int orderID;
    string status;

    string itemName;
    string orderTime;
    string paymentStatus;

    double distance;
    double foodPrice;

    Customer* customer;
    Restaurant* restaurant;
    Driver* driver;
    Payment* payment;

    static int nextID;

public:

    Order();

    Order(Customer* c , Restaurant* r ,
          Driver* d , Payment* p ,
          double dis, double food, string item);

    void setStatus(string s);
    string getStatus();

    int getOrderID();

    void assignDriver(Driver* d);

    double calculateTotalFee();

    void cancelOrder();

    bool isDelivered();

    void displayOrder();

};

#endif
