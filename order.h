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

    int orderID;        // unique ID for each order
    string itemName;    // food item name
    string orderTime;   // time when order is created

    double distance;    // delivery distance in km
    double foodPrice;   // price of the food

    // Order status system:
    // 0 = Preparing
    // 1 = On The Way
    // 2 = Delivered
    // -1 = Cancelled
    int status;

    string paymentStatus; // shows payment state (Pending / Paid / Failed)

    // pointers (relationships between classes)
    Customer* customer;
    Restaurant* restaurant;
    Driver* driver;
    Payment* payment;

    static int nextID; // auto-generated order IDs

public:

    Order(); // default constructor

    // main constructor to create full order
    Order(Customer* c, Restaurant* r, Driver* d, Payment* p,
          double dis, double food, string item, string time);

    // move order from Preparing → On The Way
    void startDelivery();

    // move order from On The Way → Delivered
    void deliverOrder();

    // cancel order safely
    void cancelOrder();

    // return order status as text
    string getStatus();

    // check if order is delivered
    bool isDelivered();

    // check if order is cancelled
    bool isCancelled();

    // calculate total cost (food + delivery fee)
    double calculateTotalFee();

    // display full order information
    void displayOrder();
};

#endif
