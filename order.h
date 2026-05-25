#ifndef ORDER_H
#define ORDER_H

#include <bits/stdc++.h>

#include "Customer.h"
#include "Payment.h"
using namespace std;

class Driver;
class Restaurant;

class Order {
    static int count; // used to generate unique order IDs
    string orderID; // unique identifier for each order
    string status; // order status (In cart, Preparing, Ready for Pickup, On The Way, Delivered, Cancelled)
    double deliveryFee;

    // structure representing a single food item in the order
    struct OrderItem {
        string name; // name of the food item
        double price; // price of one unit
        int quantity; // number of times the item is ordered
    };

    vector<OrderItem> items; // stores all items in the order (cart system)
    // pointers to related classes (associations)
    Customer *customer; // customer who placed the order
    Restaurant *restaurant; // restaurant fulfilling the order
    Driver *driver; // delivery driver assigned
    Payment *payment; // payment information

public:
    // ================= CONSTRUCTOR & DESTRUCTOR =================

    Order(Customer *c, Restaurant *r);

    ~Order();

    // ================= SETTERS =================
    void setOrderID();
    void setStatus(string status);
    void setDeliveryFee();
    void setCustomer(Customer *c); // assign customer
    void setRestaurant(Restaurant *r); // assign restaurant
    void setDriver(Driver *d); // assign driver
    void setPayment(Payment *p); // assign payment object

    // ================= GETTERS =================

    string getOrderID(); // return formatted order ID(eg,0-0001)
    string getStatus(); // return numeric status
    double getDeliveryFee();
    Customer *getCustomer(); // get customer object
    Restaurant *getRestaurant(); // get restaurants
    Driver *getDriver(); // get driver object
    Payment *getPayment(); // get payment object

    // ================= ORDER FUNCTIONS =================

    void updateStatus(); // change status: Preparing → On The Way

    void cancelOrder(); // cancel order and update payment status

    double calculateTotalFee(); // calculate total (food + delivery fee)

    void addItemToOrder(int itemID); // add item from menu using its ID

    void updatePayment();

    double calcOrderTime();

    double calcFoodPrice();

    void checkoutDisplay();

    void customerDisplayOrder(); // display order details for customer view

    void driverDisplayOrder(); // display order details for driver view

    friend ostream &operator<<(ostream &out, Order &order); // display order details for restaurant view
};

#endif //ORDER_H
