#include "Order.h"
#include <iomanip>
#include <sstream>



// ================= DEFAULT CONSTRUCTOR =================

Order::Order() {

    orderID = ++nextID;

    itemName = "";

    orderTime = "Unknown";

    distance = 0;

    foodPrice = 0;

    status = 0;

    paymentStatus = "Pending";

    customer = NULL;

    restaurant = NULL;

    driver = NULL;

    payment = NULL;
}

// ================= MAIN CONSTRUCTOR =================

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

    status = 0;

    paymentStatus = "Pending";

    // make driver busy
// when the order is created, the assigned driver becomes unavailable
// because they are currently delivering this order
    if(driver != NULL)

        driver->setAvailability(false);

    

  // save order in customer history
// add this order to the customer's previous orders list
// so the customer can view their order history later
    if(customer != NULL)

        customer->PLaceOrder(this);
}

// ================= SETTERS =================

void Order::setItemName(string item) {

    itemName = item;
}

void Order::setOrderTime(string time) {

    orderTime = time;
}

void Order::setDistance(double dis) {

    distance = dis;
}

void Order::setFoodPrice(double price) {

    foodPrice = price;
}

void Order::setPaymentStatus(string statusText) {

    paymentStatus = statusText;
}


// link the customer object with this order
// so this order belongs to that customer
void Order::setCustomer(Customer* c) {

    customer = c;
}

void Order::setRestaurant(Restaurant* r) {

    restaurant = r;
}

void Order::setDriver(Driver* d) {

    driver = d;
}
// update payment status (Paid / Failed / Pending)
void Order::setPayment(Payment* p) {

    payment = p;
}

// ================= GETTERS =================

int Order::getOrderID() {

    return orderID;
}

string Order::getFormattedOrderID() {   
}

string Order::getItemName() {

    return itemName;
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

int Order::getStatusNumber() {

    return status;
}

string Order::getPaymentStatus() {

    return paymentStatus;
}


Customer* Order::getCustomer() {

    return customer;
}

Restaurant* Order::getRestaurant() {

    return restaurant;
}

Driver* Order::getDriver() {

    return driver;
}

Payment* Order::getPayment() {

    return payment;
}

// ================= ORDER FUNCTIONS =================

// Preparing → On The Way
void Order::startDelivery() {

    if(status == 0)

        status = 1;
}

// On The Way → Delivered
void Order::deliverOrder() {

    if(status == 1)

        status = 2;
}

// cancel order
void Order::cancelOrder() {

    if(status != 2) {

        status = -1;

        paymentStatus = "Failed";

        // make driver available again
        if(driver != NULL)

            driver->setAvailability(true);
    }
}

// ================= STATUS CHECK =================

string Order::getStatus() {

    if(status == 0)

        return "Preparing";

    if(status == 1)

        return "On The Way";

    if(status == 2)

        return "Delivered";

    return "Cancelled";
}

bool Order::isDelivered() {

    return status == 2;
}

bool Order::isCancelled() {

    return status == -1;
}

// ================= PRICE CALCULATION =================

double Order::calculateTotalFee() {

    // if no driver assigned
    if(driver == NULL)

        return foodPrice;

    return foodPrice + driver->calcDeliveryFee(distance);
}


// ================= ADD ITEM (MAIN FEATURE) ==============================
void Order::addItemToOrder(int itemID) {

    // check if a restaurant is assigned to this order
    if (restaurant == NULL) {
        cout << "No restaurant assigned to order!\n";
        return;
    }

    // retrieve the menu from the restaurant
    Menu menu = restaurant->getMenu();

    // check if the selected item ID is valid in the menu
    if (menu.isItemValid(itemID)) {

        // get item name and price from the menu
        string name = menu.getItemName(itemID);
        double price = menu.getItemPrice(itemID);

        // add item name to the order list
        itemNames.push_back(name);

        // update total food price
        foodPrice += price;

        cout << "Added: " << name << " | " << price << " OMR\n";
    }
    else {
        // handle invalid item selection
        cout << "Invalid item ID!\n";
    }
}


// ================= DISPLAY FUNCTION =================

void Order::displayOrder() {

    cout << "\n===== ORDER DETAILS =====\n";

    cout << "Order ID: "
         << orderID << endl;

    cout << "Item: "
         << itemName << endl;

    cout << "Time: "
         << orderTime << endl;

    cout << "Status: "
         << getStatus() << endl;

    cout << "Payment Status: "
         << paymentStatus << endl;

    if(customer != NULL)

        cout << "Customer: "
             << customer->getName() << endl;

    if(restaurant != NULL)

        cout << "Restaurant: "
             << restaurant->getName() << endl;

    if(driver != NULL)

        cout << "Driver: "
             << driver->getName() << endl;

    cout << "Distance: "
         << distance << " km" << endl;

    cout << "Food Price: "
         << foodPrice << " OMR" << endl;

    cout << "Total Price: "
         << calculateTotalFee()
         << " OMR" << endl;

    cout << "========================\n";
}
