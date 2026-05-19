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
    string orderTime;         // time of order

    double distance;          // delivery distance
    vector<string> itemNames;   // stores the names of all food items added to the order
    double foodPrice;           // stores the total accumulated price of all selected food items


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


// change order status from Preparing to On The Way
void startDelivery();

// change order status from On The Way to Delivered
void deliverOrder();

// cancel the order if it has not been delivered yet
// also marks payment as failed
// and makes the driver available again
void cancelOrder();

// return the current order status as text
// (Preparing / On The Way / Delivered / Cancelled)
string getStatus();

// check if the order has been delivered
bool isDelivered();

// check if the order has been cancelled
bool isCancelled();

// calculate the final total price of the order
// by adding food price and delivery fee
double calculateTotalFee();

// display all order details including
// customer, restaurant, driver, prices, and status
void displayOrder();

// adds a food item to the order using its item ID
// retrieves the item name and price from the restaurant menu
// then stores the name and updates the total food price
void addItemToOrder(int itemID);

// calculates the final total fee of the order
// includes the total food price plus delivery fee (if driver is assigned)
double calculateTotalFee();


#endif
