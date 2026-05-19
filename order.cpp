#include "Order.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// ================= STATIC VARIABLE =================
// used to generate unique IDs for each order
int Order::nextID = 0;

// ================= DEFAULT CONSTRUCTOR =================
// initializes an empty order with default values
Order::Order() {

    orderID = ++nextID;

    // initialize cart and price
    foodPrice = 0;
    items.clear();

    orderTime = "Unknown";
    distance = 0;

    status = 0;
    paymentStatus = "Pending";

    // initialize pointers
    customer = NULL;
    restaurant = NULL;
    driver = NULL;
    payment = NULL;
}

// ================= MAIN CONSTRUCTOR =================
// creates a fully linked order with customer, restaurant, driver, and payment
Order::Order(Customer* c, Restaurant* r, Driver* d, Payment* p,
             double dis, string time) {

    orderID = ++nextID;

    customer = c;
    restaurant = r;
    driver = d;
    payment = p;

    distance = dis;
    orderTime = time;

    // initialize cart system
    foodPrice = 0;
    items.clear();

    status = 0;
    paymentStatus = "Pending";

    // mark driver as busy when assigned to this order
    if (driver != NULL)
        driver->setAvailability(false);

    // store order in customer's order history
    if (customer != NULL)
        customer->PLaceOrder(this);
}

// ================= SETTERS =================
void Order::setOrderTime(string time) {
    orderTime = time;
}

void Order::setDistance(double dis) {
    distance = dis;
}

void Order::setPaymentStatus(string statusText) {
    paymentStatus = statusText;
}

void Order::setCustomer(Customer* c) {
    customer = c;
}

void Order::setRestaurant(Restaurant* r) {
    restaurant = r;
}

void Order::setDriver(Driver* d) {
    driver = d;
}

void Order::setPayment(Payment* p) {
    payment = p;
}

// ================= GETTERS =================
int Order::getOrderID() {
    return orderID;
}

string Order::getOrderTime() {
    return orderTime;
}

double Order::getDistance() {
    return distance;
}

double Order::getFoodPrice() {
    return foodPrice;
}

string Order::getPaymentStatus() {
    return paymentStatus;
}

// ================= ORDER STATUS FUNCTIONS =================

// change status from Preparing → On The Way
void Order::startDelivery() {
    if (status == 0)
        status = 1;
}

// change status from On The Way → Delivered
void Order::deliverOrder() {
    if (status == 1)
        status = 2;
}

// cancel order if not delivered yet
// also updates payment and frees driver
void Order::cancelOrder() {

    if (status != 2) {

        status = -1;
        paymentStatus = "Failed";

        // make driver available again
        if (driver != NULL)
            driver->setAvailability(true);
    }
}

// return order status as readable text
string Order::getStatus() {

    if (status == 0) return "Preparing";
    if (status == 1) return "On The Way";
    if (status == 2) return "Delivered";

    return "Cancelled";
}

// ================= ADD ITEM TO ORDER =================
// adds item from menu using item ID
// updates cart and total price
void Order::addItemToOrder(int itemID) {

    // check if restaurant is assigned
    if (restaurant == NULL) {
        cout << "No restaurant assigned!\n";
        return;
    }

    // get menu from restaurant
    const Menu& menu = restaurant->getMenu();

    // validate item ID
    if (!menu.isItemValid(itemID)) {
        cout << "Invalid item ID!\n";
        return;
    }

    // get item details from menu
    string name = menu.getItemName(itemID);
    double price = menu.getItemPrice(itemID);

    // check if item already exists in cart
    for (int i = 0; i < items.size(); i++) {

        if (items[i].name == name) {

            // increase quantity if item already exists
            items[i].quantity++;
            foodPrice += price;

            cout << "Increased quantity: " << name << "\n";
            return;
        }
    }

    // create new cart item
    OrderItem newItem;
    newItem.name = name;
    newItem.price = price;
    newItem.quantity = 1;

    // add item to cart
    items.push_back(newItem);
    foodPrice += price;

    cout << "Added: " << name << " | " << price << " OMR\n";
}

// ================= TOTAL CALCULATION =================
// calculates final price including delivery fee
double Order::calculateTotalFee() {

    if (driver == NULL)
        return foodPrice;

    return foodPrice + driver->calcDeliveryFee(distance);
}

// ================= DISPLAY ORDER =================
// prints full order details including items, customer, and total
void Order::displayOrder() {

    cout << "\n===== ORDER DETAILS =====\n";

    cout << "Order ID: " << orderID << endl;

    cout << "Items:\n";

    // display all items in cart
    for (int i = 0; i < items.size(); i++) {

        cout << "- " << items[i].name
             << " x" << items[i].quantity
             << " | " << items[i].price << " OMR each\n";
    }

    cout << "Time: " << orderTime << endl;
    cout << "Status: " << getStatus() << endl;
    cout << "Payment Status: " << paymentStatus << endl;

    // display related objects if available
    if (customer != NULL)
        cout << "Customer: " << customer->getName() << endl;

    if (restaurant != NULL)
        cout << "Restaurant: " << restaurant->getName() << endl;

    if (driver != NULL)
        cout << "Driver: " << driver->getName() << endl;

    cout << "Distance: " << distance << " km" << endl;

    cout << "Food Price: " << foodPrice << " OMR" << endl;
    cout << "Total Price: " << calculateTotalFee() << " OMR" << endl;

    cout << "========================\n";
}
