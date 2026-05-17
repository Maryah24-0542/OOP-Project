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

    int orderID;              // unique ID for each order
    string itemName;          // food item name
    string orderTime;         // time of order

    double distance;          // delivery distance
    double foodPrice;         // food price

    // status system:
    // 0 = Preparing
    // 1 = On The Way
    // 2 = Delivered
    // -1 = Cancelled
    int status;

    string paymentStatus;

    // relationships with other classes
    Customer* customer;
    Restaurant* restaurant;
    Driver* driver;
    Payment* payment;

    static int nextID;

public:

    // constructors
    Order();

    Order(Customer* c, Restaurant* r, Driver* d, Payment* p,
          double dis, double food, string item, string time);

    // ================= SETTERS =================

    void setItemName(string item);

    void setOrderTime(string time);

    void setDistance(double dis);

    void setFoodPrice(double price);

    void setPaymentStatus(string status);

    void setCustomer(Customer* c);

    void setRestaurant(Restaurant* r);

    void setDriver(Driver* d);

    void setPayment(Payment* p);

    // ================= GETTERS =================

    int getOrderID();

    string getFormattedOrderID();

    string getItemName();

    string getOrderTime();

    double getDistance();

    double getFoodPrice();

    int getStatusNumber();

    string getPaymentStatus();

    Customer* getCustomer();

    Restaurant* getRestaurant();

    Driver* getDriver();

    Payment* getPayment();

    // ================= ORDER FUNCTIONS =================

    void startDelivery();

    void deliverOrder();

    void cancelOrder();

    string getStatus();

    bool isDelivered();

    bool isCancelled();

    double calculateTotalFee();

    void displayOrder();
};

#endif
