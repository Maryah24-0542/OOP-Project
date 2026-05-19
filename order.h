#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>

#include "Customer.h"
#include "Restaurant.h"
#include "Driver.h"
#include "Payment.h"

using namespace std;

class Order {

private:

    int orderID;   // unique identifier for each order

    // structure representing a single food item in the order
    struct OrderItem {
        string name;     // name of the food item
        double price;    // price of one unit
        int quantity;    // number of times the item is ordered
    };

    vector<OrderItem> items;  // stores all items in the order (cart system)
    double foodPrice;         // total price of all food items in the order

    string orderTime;         // time when the order was placed
    double distance;          // delivery distance in kilometers

    int status;               // order status (0=Preparing, 1=On The Way, 2=Delivered, -1=Cancelled)
    string paymentStatus;     // payment status (Pending / Paid / Failed)

    // pointers to related classes (associations)
    Customer* customer;      // customer who placed the order
    Restaurant* restaurant;  // restaurant fulfilling the order
    Driver* driver;          // delivery driver assigned
    Payment* payment;        // payment information

    static int nextID;       // used to generate unique order IDs

public:

    // ================= CONSTRUCTORS =================

    Order();

    Order(Customer* c, Restaurant* r, Driver* d, Payment* p,
          double dis, string time);

    // ================= SETTERS =================

    void setOrderTime(string time);           // set order time
    void setDistance(double dis);             // set delivery distance
    void setFoodPrice(double price);          // set total food price manually
    void setPaymentStatus(string status);     // update payment status

    void setCustomer(Customer* c);            // assign customer
    void setRestaurant(Restaurant* r);        // assign restaurant
    void setDriver(Driver* d);                // assign driver
    void setPayment(Payment* p);              // assign payment object

    // ================= GETTERS =================

    int getOrderID();                         // return order ID
    string getFormattedOrderID();             // return formatted order ID(eg,0-0001)

    string getOrderTime();                    // return order time
    double getDistance();                     // return delivery distance
    double getFoodPrice();                    // return total food price
    int getStatusNumber();                    // return numeric status
    string getPaymentStatus();                // return payment status

    Customer* getCustomer();                  // get customer object
    Restaurant* getRestaurant();              // get restaurant object
    Driver* getDriver();                      // get driver object
    Payment* getPayment();                    // get payment object

    // ================= ORDER FUNCTIONS =================

    void startDelivery();                     // change status: Preparing → On The Way
    void deliverOrder();                      // change status: On The Way → Delivered
    void cancelOrder();                       // cancel order and update payment status

    string getStatus();                       // return status as text
    bool isDelivered();                       // check if order is delivered
    bool isCancelled();                       // check if order is cancelled

    double calculateTotalFee();               // calculate total (food + delivery fee)

    void displayOrder();                      // display full order details

    void addItemToOrder(int itemID);          // add item from menu using its ID

};

#endif
