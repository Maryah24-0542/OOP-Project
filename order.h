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

    int orderID;   // unique ID for each order (auto generated)

    string status; // shows current order status:
                   // Preparing, On The Way, Delivered, Cancelled

    string itemName; // name of the food item ordered (e.g. Burger)

    string orderTime; // time when order was created

    string paymentStatus; // shows payment state:
                           // Pending, Paid, Failed

    double distance;  // distance between restaurant and customer (km)

    double foodPrice; // price of the food item

    // These are pointers because Order is connected to other classes
    // It does NOT copy the objects, it just links to them
    Customer* customer;      
    Restaurant* restaurant;
    Driver* driver;
    Payment* payment;

    static int nextID; // used to automatically generate order IDs

public:

    Order(); // default constructor (empty order)

    // main constructor used when creating a real order
    Order(Customer* c , Restaurant* r ,
          Driver* d , Payment* p ,
          double dis, double food, string item);

    void setStatus(string s); // change order status

    string getStatus(); // return current status

    int getOrderID(); // return order ID

    void assignDriver(Driver* d); // assign or change driver

    double calculateTotalFee(); // calculate total cost (food + delivery)

    void cancelOrder(); // cancel the order and free driver

    bool isDelivered(); // check if order is delivered

    void displayOrder(); // print all order details on screen
};

#endif
