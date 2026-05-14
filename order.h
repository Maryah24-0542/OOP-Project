#ifndef UNTITLED_ORDER_H
#define UNTITLED_ORDER_H

#include <iostream>
#include <string>

#include "customer.h"
#include "Restaurant.h"
#include "Driver.h"
#include "Payment.h"

using namespace std;

class Order {

private:

    int orderID;
    string orderStatus;
    double distance;

    Customer* customer;
    Restaurant* restaurant;
    Driver* driver;
    Payment* payment;

    static int nextID;

public:

    Order();

    Order(Customer* c , Restaurant* r ,
          Driver* d , Payment* p ,
          double dis);

    void setStatus(string s);

    string getStatus();

    int getOrderID();

    double calculateTotalFee();

    void displayOrder();

};

#endif
