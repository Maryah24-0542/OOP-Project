#include "Order.h"

// initialize static variable
int Order::nextID = 1000; // start IDs from 1000

// default constructor
Order::Order() {

    orderID = ++nextID; // generate unique ID

    itemName = "";
    orderTime = "Unknown";

    distance = 0;
    foodPrice = 0;

    status = 0; // default = Preparing
    paymentStatus = "Pending";

    // pointers start empty (no connections yet)
    customer = NULL;
    restaurant = NULL;
    driver = NULL;
    payment = NULL;
}

// main constructor (full order setup)
Order::Order(Customer* c, Restaurant* r, Driver* d, Payment* p,
             double dis, double food, string item, string time) {

    orderID = ++nextID;

    customer = c;
    restaurant = r;
    driver = d;
    payment = p;

    distance = dis;
    foodPrice = food;
    itemName = item;
    orderTime = time;

    status = 0; // Preparing
    paymentStatus = "Pending";

    // when driver is assigned → mark him as busy
    if(driver != NULL)
        driver->setAvailability(false);

    // add order to customer's history
    if(customer != NULL)
        customer->PLaceOrder(this);
}

// move order from Preparing → On The Way
void Order::startDelivery() {

    // only allowed from Preparing state
    if(status == 0)
        status = 1;
}

// move order from On The Way → Delivered
void Order::deliverOrder() {

    // only allowed from On The Way state
    if(status == 1)
        status = 2;
}

// cancel order safely
void Order::cancelOrder() {

    // cannot cancel if already delivered
    if(status != 2) {

        status = -1; // cancelled
        paymentStatus = "Failed";

        // make driver available again
        if(driver != NULL)
            driver->setAvailability(true);
    }
}

// return status as readable text
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

// check if order is cancelled
bool Order::isCancelled() {
    return status == -1;
}

// calculate total price
double Order::calculateTotalFee() {

    // safety check
    if(driver == NULL)
        return foodPrice;

    return foodPrice + driver->calcDeliveryFee(distance);
}

// display full order details
void Order::displayOrder() {

    cout << "\n===== ORDER DETAILS =====\n";

    cout << "Order ID: " << orderID << endl;
    cout << "Item: " << itemName << endl;
    cout << "Time: " << orderTime << endl;

    cout << "Status: " << getStatus() << endl;
    cout << "Payment Status: " << paymentStatus << endl;

    // safety checks to avoid crashes
    if(customer != NULL)
        cout << "Customer: " << customer->getName() << endl;

    if(restaurant != NULL)
        cout << "Restaurant: " << restaurant->getName() << endl;

    if(driver != NULL)
        cout << "Driver: " << driver->getName() << endl;

    cout << "Distance: " << distance << " km" << endl;
    cout << "Food Price: " << foodPrice << " OMR" << endl;

    cout << "Total Price: " << calculateTotalFee() << " OMR" << endl;

    cout << "========================\n";
}
