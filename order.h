#ifndef UNTITLED_ORDER_H
#define UNTITLED_ORDER_H

#include <iostream>
#include <string>

#include "customer.h"
#include "Restaurant.h"
#include "Driver.h"
#include "Payment.h"

using namespace std;

// Order class represents a food order in the system
class Order {

private:

    int orderID;              // unique ID for each order
    string orderStatus;      // status of the order (Preparing, Delivered, Cancelled)

    string itemName;         // name of food item(burger, pizza,......)

    double distance;         // delivery distance
    double foodPrice;        // price of food

    // (associations)
    Customer* customer;      
    Restaurant* restaurant;
    Driver* driver;
    Payment* payment;

    static int nextID;       // auto increment order ID

public:

    Order();  // default constructor

    // constructor with all order details
    Order(Customer* c , Restaurant* r ,
          Driver* d , Payment* p ,
          double dis, double food, string item);

    void setStatus(string s);  // change order status
    string getStatus();        // get order status

    int getOrderID();          // get order ID

    double calculateTotalFee(); // calculate total price

    void cancelOrder();        // cancel the order

    void displayOrder();       // show order details
};

#endif
