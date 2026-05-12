#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// Forward declarations 
class Customer;
class Restaurant;
class Driver;
class Payment;

//  OrderItem  (Menue selection)

struct OrderItem {
    string itemName;
    double itemPrice;
    int    quantity;

    OrderItem(string n, double p, int q = 1)
        : itemName(n), itemPrice(p), quantity(q) {}

    double subtotal() const { return itemPrice * quantity; }
};


class Order {
private:
   
    string      orderID;
    static int  orderCount;

    //  Associations (pointers — Order does NOT own these objects) 
    Customer*   customer;       // WHO placed the order
    Restaurant* restaurant;     // WHERE the order is from
    Driver*     driver;         // WHO delivers it  (CarDriver or BikeDriver)
    Payment*    payment;        // HOW it is paid  

    // Order contents 
    vector<OrderItem> items;    // items selected from the Restaurant's Menu

    // Delivery info 
    double      deliveryDistance;   // in km
    string      deliveryAddress;

    // Status & timing 
    string status;
    string orderDate;

public:
    //  Constructors
    Order();
    Order(Customer* c, Restaurant* r, string address, double distance);

    // Item management 
    void addItem(string itemName, double price, int quantity = 1);
    void removeItem(string itemName);
    void displayItems() const;

   
    void assignDriver(Driver* d);       // attach CarDriver or BikeDriver
    void setPayment(Payment* p);        // attach a Payment object

    // ── Calculations ─────────────────────────────
    double calcSubtotal()      const;   // sum of all item subtotals
    double calcDeliveryFee()   const;   // delegated to Driver
    double calcTotal()         const;   // subtotal + delivery fee
    double getEstimatedTime()  const;   // delegated to Driver

    //Status management
    void   setStatus(string s);
    string getStatus() const;
    void   cancelOrder();

    // Getters
    string             getOrderID()          const;  
    Customer*          getCustomer()         const;
    Restaurant*        getRestaurant()       const;
    Driver*            getDriver()           const;
    Payment*           getPayment()          const;
    string             getDeliveryAddress()  const;
    double             getDeliveryDistance() const;
    string             getOrderDate()        const;
    vector<OrderItem>  getItems()            const;  // returns copy of items list

    // Setters
    // orderID has NO setter it is auto-generated and should never change
    void setCustomer(Customer* c);
    void setRestaurant(Restaurant* r);
    void setDriver(Driver* d);          // renamed from assignDriver for consistency
    void setPayment(Payment* p);
    void setOrderDate(string date);
    void setDeliveryAddress(string address);
    void setDeliveryDistance(double distance);

    // ── Display ───────────────────────────────────
    void displayOrder() const;          // full order summary
    void displayReceipt() const;        // formatted receipt
};

#endif // ORDER_H
