#include <iostream>
using namespace std;

// Related classes
class Customer;
class Driver;
class Restaurant;

class Order {

private:
    int orderID;
    string status;
    double totalAmount;

    // Relationships
    Customer* customer;
    Driver* driver;
    Restaurant* restaurant;

public:

    // Constructor
    Order(int id) {
        orderID = id;
        status = "Pending";
        totalAmount = 0.0;
    }

};
