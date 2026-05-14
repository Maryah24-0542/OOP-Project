#include "Order.h"

int Order::nextID = 1000;

// default constructor
Order::Order() {

    orderID = ++nextID;

    status = "Preparing";
    paymentStatus = "Pending";

    itemName = "";
    orderTime = "Unknown";

    distance = 0;
    foodPrice = 0;

    customer = NULL;
    restaurant = NULL;
    driver = NULL;
    payment = NULL;
}

// main constructor
Order::Order(Customer* c , Restaurant* r ,
             Driver* d , Payment* p ,
             double dis, double food, string item) {

    orderID = ++nextID;

    customer = c;
    restaurant = r;
    driver = d;
    payment = p;

    distance = dis;
    foodPrice = food;
    itemName = item;

    status = "Preparing";
    paymentStatus = "Pending";
    orderTime = "Now";

    if(driver != NULL)
        driver->setAvailability(false);

    if(customer != NULL)
        customer->PLaceOrder(this);
}

// change status
void Order::setStatus(string s) {
    status = s;
}

// get status
string Order::getStatus() {
    return status;
}

// assign driver later
void Order::assignDriver(Driver* d) {

    driver = d;

    if(driver != NULL)
        driver->setAvailability(false);
}

// calculate total price
double Order::calculateTotalFee() {

    return foodPrice +
           driver->calcDeliveryFee(distance);
}

// cancel order
void Order::cancelOrder() {

    status = "Cancelled";
    paymentStatus = "Failed";

    if(driver != NULL)
        driver->setAvailability(true);
}

// check if delivered
bool Order::isDelivered() {

    return status == "Delivered";
}

// display order details
void Order::displayOrder() {

    cout << "\n========== ORDER DETAILS ==========\n";

    cout << "Order ID : " << orderID << endl;

    cout << "Item : " << itemName << endl;

    cout << "Order Time : " << orderTime << endl;

    cout << "Customer : "
         << customer->getName() << endl;

    cout << "Restaurant : "
         << restaurant->getName() << endl;

    cout << "Driver : "
         << driver->getName() << endl;

    cout << "Distance : "
         << distance << " km" << endl;

    cout << "Food Price : "
         << foodPrice << " OMR" << endl;

    cout << "Delivery Fee : "
         << driver->calcDeliveryFee(distance)
         << " OMR" << endl;

    cout << "Total Price : "
         << calculateTotalFee()
         << " OMR" << endl;

    cout << "Payment Status : "
         << paymentStatus << endl;

    cout << "Order Status : "
         << status << endl;

    cout << "==================================\n";
}
