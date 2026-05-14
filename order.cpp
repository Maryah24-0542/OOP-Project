#include "Order.h"

int Order::nextID = 1000;

Order::Order() {

    orderID = ++nextID;

    orderStatus = "Preparing";

    itemName = "";

    distance = 0;
    foodPrice = 0;

    customer = NULL;
    restaurant = NULL;
    driver = NULL;
    payment = NULL;
}

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

    orderStatus = "Preparing";

    // make driver busy
    if(driver != NULL)
        driver->setAvailability(false);

    // add order to customer history
    if(customer != NULL)
        customer->PLaceOrder(this);
}

void Order::setStatus(string s) {

    orderStatus = s;
}

string Order::getStatus() {

    return orderStatus;
}

int Order::getOrderID() {

    return orderID;
}

double Order::calculateTotalFee() {

    return foodPrice +
           driver->calcDeliveryFee(distance);
}

void Order::cancelOrder() {

    orderStatus = "Cancelled";

    if(driver != NULL)
        driver->setAvailability(true);
}

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

    cout << "Payment : "
         << payment->getAmount() << endl;

    cout << "Status : "
         << orderStatus << endl;

    cout << "==================================\n";
}
