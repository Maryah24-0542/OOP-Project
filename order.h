#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <vector>
#include <string>
#include "Customer.h"
#include "Restaurant.h"
#include "Driver.h"
#include "Payment.h"

using namespace std;


//  Item  –  stored INSIDE Order (Composition)
class Item {
private:
    int    itemID;
    string itemName;
    int    quantity;
    double price;

public:
    Item(int id, string name, int qty, double p);

    // Getters
    int    getItemID()   const;
    string getItemName() const;
    int    getQuantity() const;
    double getPrice()    const;

    // Setters
    void setItemID(int id);
    void setItemName(string n);
    void setQuantity(int q);
    void setPrice(double p);

    void display() const;
};



class Order {
private:
    // ── Identity ──────────────────────────────
    int    orderID;
    string orderTime;
    string status;       // Pending → Paid → Preparing → On the way → Delivered

    // Financial 
    double itemsTotal;       // sum of all item prices
    double deliveryFee;      // calculated from driver + distance
    double totalAmount;      // itemsTotal + deliveryFee
    string deliveryAddress;

    //  Delivery 
    double distance;         // distance in km (needed for delivery fee + ETA)
    double estimatedTime;    // estimated delivery time in minutes

    // Items (Composition – Order owns them) 
    vector<Item> items;

    // ── Relationships ─────────────────────────
    Customer    customerSnapshot;  // Composition  –  stored by value
    Restaurant* restaurant;        // Aggregation  – pointer, shared lifetime
    Driver*     driver;            // Aggregation  – pointer, assigned later
    Payment*    payment;           // Composition  – Order owns and deletes it

    static int nextOrderID;

public:
    // Constructor / Destructor 
    Order(Customer c, Restaurant* rest, string address, double distanceKm, string time = "N/A");
    ~Order();

    // Setters 
    void setOrderTime(string t);
    void setStatus(string s);
    void setDeliveryAddress(string a);
    void setDistance(double d);
    void setDriver(Driver* d);    // assigns driver, marks driver unavailable, calculates fee + ETA
    void setPayment(Payment* p);  // links payment, moves status to Paid

    //  Getters 
    int          getOrderID()          const;
    string       getOrderTime()        const;
    string       getStatus()           const;
    double       getItemsTotal()       const;
    double       getDeliveryFee()      const;
    double       getTotalAmount()      const;
    string       getDeliveryAddress()  const;
    double       getDistance()         const;
    double       getEstimatedTime()    const;
    Customer     getCustomerSnapshot() const;
    Restaurant*  getRestaurant()       const;
    Driver*      getDriver()           const;
    Payment*     getPayment()          const;
    vector<Item> getItems()            const;

    
    void   addItem(int id, string name, int qty, double price);
    double calculateTotal();   // recalculates itemsTotal + deliveryFee + totalAmount
    void   updateStatus(string newStatus);
    void   displayOrder() const;
};

#endif // ORDER_H
