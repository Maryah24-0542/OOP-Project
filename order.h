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

    int orderID;          // unique ID for each order
    string itemName;      // food item name

    double distance;      // delivery distance
    double foodPrice;     // price of food

    // ORDER STATUS SYSTEM:
    // 0 = Preparing
    // 1 = On The Way
    // 2 = Delivered
    // -1 = Cancelled
    int status;

    // connections with other classes (relationships)
    Customer* customer;
    Restaurant* restaurant;
    Driver* driver;
    Payment* payment;

    static int nextID;    // auto generate order IDs

public:

    Order();  // default constructor

    Order(Customer* c, Restaurant* r, Driver* d, Payment* p,
          double dis, double food, string item);

    void nextStatus();        // move order to next stage
    void cancelOrder();       // cancel the order

    string getStatus();       // convert status to text

    bool isDelivered();       // check if delivered

    double calculateTotalFee(); // total price

    void displayOrder();      // print order info
};

#endif
