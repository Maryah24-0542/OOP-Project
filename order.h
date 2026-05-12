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
    int    itemID;       // auto-generated, no need to pass it manually
    string itemName;
    int    quantity;
    double price;

    static int nextItemID;  // shared counter across ALL items ever created

public:
    // No itemID parameter – it is assigned automatically
    Item(string name, int qty, double p);

    // Getters
    int    getItemID()   const;
    string getItemName() const;
    int    getQuantity() const;
    double getPrice()    const;

    // Setters
    void setItemName(string n);
    void setQuantity(int q);
    void setPrice(double p);

    void display() const;
};


class Order {
private:
    //Identity 
    int    orderID;
    string orderTime;
    string status;       // Pending → Paid → Preparing → On the way → Delivered

    //  Financial 
    double itemsTotal;       // sum of all item prices
    double deliveryFee;      // calculated from driver + distance
    double totalAmount;      // itemsTotal + deliveryFee
    string deliveryAddress;

    //Delivery 
    double distance;         // distance in km
    double estimatedTime;    // estimated delivery time in minutes

    // Items (Composition – Order owns them) ─
    vector<Item> items;

    //  Relationships
    Customer    customerSnapshot;  // Composition  –  stored by value
    Restaurant* restaurant;        // Aggregation  – pointer, shared lifetime
    Driver*     driver;            // Aggregation  – pointer, assigned later
    Payment*    payment;           // Composition  – Order owns and deletes it

    static int nextOrderID;

public:
    //  Constructor / Destructor 
    Order(Customer c, Restaurant* rest, string address, double distanceKm, string time = "N/A");
    ~Order();

    //Setters 
    void setOrderTime(string t);
    void setStatus(string s);
    void setDeliveryAddress(string a);
    void setDistance(double d);
    void setDriver(Driver* d);
    void setPayment(Payment* p);

    // Getters
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

    //  Operations
    void   addItem(string name, int qty, double price);  // no id needed anymore
    double calculateTotal();
    void   updateStatus(string newStatus);
    void   displayOrder() const;
};

#endif // ORDER_H
