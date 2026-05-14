#include "Order.h"

// start order IDs from 1000
int Order::nextID = 1000;

// default constructor
// used when we create an empty order object
Order::Order() {

    orderID = ++nextID; // generate new unique ID automatically

    status = "Preparing"; // default status when order starts
    paymentStatus = "Pending"; // payment not done yet

    itemName = ""; // no item selected yet
    orderTime = "Unknown"; // no time set yet

    distance = 0; // default distance
    foodPrice = 0; // default price

    // pointers are empty because no links yet
    customer = NULL;
    restaurant = NULL;
    driver = NULL;
    payment = NULL;
}

// main constructor
// used when creating a full order with all details
Order::Order(Customer* c , Restaurant* r ,
             Driver* d , Payment* p ,
             double dis, double food, string item) {

    orderID = ++nextID; // generate unique ID

    // connect order with other system parts
    customer = c;
    restaurant = r;
    driver = d;
    payment = p;

    distance = dis; // set delivery distance
    foodPrice = food; // set food price
    itemName = item; // set ordered item name

    status = "Preparing"; // order starts in preparing state
    paymentStatus = "Pending"; // payment not completed yet
    orderTime = "Now"; // simple time value

    // when driver is assigned → mark him as busy
    if(driver != NULL)
        driver->setAvailability(false);

    // add this order into customer's order history
    if(customer != NULL)
        customer->PLaceOrder(this);
}

// change order status manually
void Order::setStatus(string s) {
    status = s;
}

// return current order status
string Order::getStatus() {
    return status;
}

// return order ID
int Order::getOrderID() {
    return orderID;
}

// assign a driver to this order
// can be used if driver changes later
void Order::assignDriver(Driver* d) {

    driver = d;

    // mark driver as busy
    if(driver != NULL)
        driver->setAvailability(false);
}

// calculate total price of order
// total = food price + delivery fee
double Order::calculateTotalFee() {

    return foodPrice +
           driver->calcDeliveryFee(distance);
}

// cancel order function
void Order::cancelOrder() {

    status = "Cancelled"; // update status
    paymentStatus = "Failed"; // payment is cancelled

    // make driver available again
    if(driver != NULL)
        driver->setAvailability(true);
}

// check if order is delivered
bool Order::isDelivered() {

    return status == "Delivered";
}

// display all order information
void Order::displayOrder() {

    cout << "\n========== ORDER DETAILS ==========\n";

    cout << "Order ID : " << orderID << endl; // show ID
    cout << "Item : " << itemName << endl; // show food name
    cout << "Order Time : " << orderTime << endl; // show time

    cout << "Customer : "
         << customer->getName() << endl; // customer name

    cout << "Restaurant : "
         << restaurant->getName() << endl; // restaurant name

    cout << "Driver : "
         << driver->getName() << endl; // driver name

    cout << "Distance : "
         << distance << " km" << endl; // delivery distance

    cout << "Food Price : "
         << foodPrice << " OMR" << endl; // food price

    cout << "Delivery Fee : "
         << driver->calcDeliveryFee(distance)
         << " OMR" << endl; // delivery cost

    cout << "Total Price : "
         << calculateTotalFee()
         << " OMR" << endl; // final total

    cout << "Payment Status : "
         << paymentStatus << endl; // payment state

    cout << "Order Status : "
         << status << endl; // order state

    cout << "==================================\n";
}
