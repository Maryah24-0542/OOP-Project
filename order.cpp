#include "Order.h"

// initialize static variable
int Order::nextID = 1000; //starts order IDs from 1000

// default constructor
Order::Order() {

    orderID = ++nextID;   // generate ID

    itemName = "";        // no item yet
    distance = 0;         // default distance
    foodPrice = 0;        // default price

    status = 0;           // start = Preparing

    customer = NULL;
    restaurant = NULL;
    driver = NULL;
    payment = NULL;
}

// main constructor (full order setup)
Order::Order(Customer* c, Restaurant* r, Driver* d, Payment* p,
             double dis, double food, string item) {

    orderID = ++nextID;   // generate unique ID

    customer = c;         // link customer
    restaurant = r;       // link restaurant
    driver = d;           // link driver
    payment = p;          // link payment

    distance = dis;       // set distance
    foodPrice = food;     // set food price
    itemName = item;      // set item name

    status = 0;           // start = Preparing

    // make driver busy
    if(driver != NULL)
        driver->setAvailability(false);

    // add order to customer history
    if(customer != NULL)
        customer->PLaceOrder(this);
}

// move to next status step
void Order::nextStatus() {

    // only move if not cancelled or already delivered
    if(status >= 0 && status < 2) {
        status++;
    }
}

// cancel order
void Order::cancelOrder() {

    status = -1; // cancelled

    // free driver again
    if(driver != NULL)
        driver->setAvailability(true);
}

// convert status number to text
string Order::getStatus() {

    if(status == 0) return "Preparing";
    if(status == 1) return "On The Way";
    if(status == 2) return "Delivered";
    return "Cancelled";
}

// check if order is delivered
bool Order::isDelivered() {
    return status == 2;
}

// calculate total price (food + delivery fee)
double Order::calculateTotalFee() {

    return foodPrice +
           driver->calcDeliveryFee(distance);
}

// display full order details
void Order::displayOrder() {

    cout << "\n===== ORDER DETAILS =====\n";

    cout << "Order ID: " << orderID << endl;
    cout << "Item: " << itemName << endl;

    cout << "Status: " << getStatus() << endl;

    cout << "Customer: " << customer->getName() << endl;
    cout << "Restaurant: " << restaurant->getName() << endl;
    cout << "Driver: " << driver->getName() << endl;

    cout << "Distance: " << distance << " km" << endl;
    cout << "Food Price: " << foodPrice << " OMR" << endl;

    cout << "Delivery Fee: "
         << driver->calcDeliveryFee(distance)
         << " OMR" << endl;

    cout << "Total: " << calculateTotalFee() << " OMR" << endl;

    cout << "========================\n";
}
