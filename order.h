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

    int    orderID;
    string orderTime;
    string status;      // Pending → Paid → Preparing → On the way → Delivered

    //Financial
    double totalAmount;
    string deliveryAddress;

    // Items (Composition – Order owns them) 
    vector<Item> items;

    
    Customer    customerSnapshot;  // Composition  – snapshot stored by value
    Restaurant* restaurant;        // Aggregation  – pointer, shared lifetime
    Driver*     driver;            // Aggregation  – pointer, assigned later
    Payment*    payment;           // Composition  – Order owns and deletes it

    static int nextOrderID;

public:
    //  Constructor / Destructor
    Order(Customer c, Restaurant* rest, string address, string time = "N/A");
    ~Order();

    // Setters
    void setOrderTime(string t);
    void setStatus(string s);
    void setTotalAmount(double a);
    void setDeliveryAddress(string a);
    void setDriver(Driver* d);
    void setPayment(Payment* p);

    //  Getters 
    int          getOrderID()          const;
    string       getOrderTime()        const;
    string       getStatus()           const;
    double       getTotalAmount()      const;
    string       getDeliveryAddress()  const;
    Customer     getCustomerSnapshot() const;
    Restaurant*  getRestaurant()       const;
    Driver*      getDriver()           const;
    Payment*     getPayment()          const;
    vector<Item> getItems()            const;

    // Operations 
    void   addItem(int id, string name, int qty, double price);
    double calculateTotal();
    void   updateStatus(string newStatus);
    void   displayOrder() const;
};

#endif // ORDER_H
