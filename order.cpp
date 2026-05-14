#include "Order.h"

int Order::nextID = 1000; // start order IDs from 1000

// default constructor
Order::Order() {

    orderID = ++nextID; // generate new ID

    orderStatus = "Preparing"; // default status

    itemName = "";
    distance = 0;
    foodPrice = 0;

    // initialize pointers to NULL (no data yet)
    customer = NULL;
    restaurant = NULL;
    driver = NULL;
    payment = NULL;
}

// main constructor
Order::Order(Customer* c , Restaurant* r ,
             Driver* d , Payment* p ,
             double dis, double food, string item) {

    orderID = ++nextID; // new ID

    customer = c;       // link customer
    restaurant = r;     // link restaurant
    driver = d;         // link driver
    payment = p;        // link payment

    distance = dis;     // set distance
    foodPrice = food;   // set food price
    itemName = item;    // set item name

    orderStatus = "Preparing"; // initial status

    // make driver busy when assigned
    if(driver != NULL)
        driver->setAvailability(false);

    // add order to customer's history
    if(customer != NULL)
        customer->PLaceOrder(this);
}

// change order status
void Order::setStatus(string s) {
    orderStatus = s;
}

// return order status
string Order::getStatus() {
    return orderStatus;
}

// return order ID
int Order::getOrderID() {
    return orderID;
}

// calculate total cost (food + delivery)
double Order::calculateTotalFee() {
    return foodPrice +
           driver->calcDeliveryFee(distance);
}

// cancel order
void Order::cancelOrder() {

    orderStatus = "Cancelled";

    // make driver available again
    if(driver != NULL)
        driver->setAvailability(true);
}

// display all order details
void Order::displayOrder() {

    cout << "\n========== ORDER DETAILS ==========\n";

    cout << "Order ID : " << orderID << endl;
    cout << "Item : " << itemName << endl;

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

    cout << "Estimated Time : "
         << driver->getESTtime(distance)
         << " minutes" << endl;

    cout << "Payment Amount : "
         << payment->getAmount() << endl;

    cout << "Order Status : "
         << orderStatus << endl;

    cout << "==================================\n";
}
