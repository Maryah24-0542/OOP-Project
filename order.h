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

    int orderID;              // unique id for each order
    string status;            // order status (Preparing, Delivered, Cancelled)

    string itemName;          // food item name
    string orderTime;         // time of order
    string paymentStatus;     // payment status

    double distance;          // delivery distance
    double foodPrice;         // price of food

    // links to other classes (relationships)
    Customer* customer;
    Restaurant* restaurant;
    Driver* driver;
    Payment* payment;

    static int nextID;        // auto increment ID

public:

    Order(); // default constructor

    Order(Customer* c , Restaurant* r ,
          Driver* d , Payment* p ,
          double dis, double food, string item);

    void setStatus(string s);     // change order status
    string getStatus();           // get order status

    int getOrderID();             // get order ID

    void assignDriver(Driver* d); // assign driver to order

    double calculateTotalFee();   // calculate total price

    void cancelOrder();           // cancel order

    bool isDelivered();           // check if delivered

    void displayOrder();          // show order details
};

#endif
