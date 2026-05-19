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

    // initialize cart system
    foodPrice = 0;
    items.clear(); // ensure cart starts empty

    orderTime = "Unknown";
    distance = 0;

    status = 0; // 0 = Preparing
    paymentStatus = "Pending";

    // initialize pointers to avoid dangling references
    customer = NULL;
    restaurant = NULL;
    driver = NULL;
    payment = NULL;
}

// ================= MAIN CONSTRUCTOR =================
// creates a complete order linked with all system entities
Order::Order(Customer* c, Restaurant* r, Driver* d, Payment* p,
             double dis, string time) {

    orderID = ++nextID;

    customer = c;
    restaurant = r;
    driver = d;
    payment = p;

    distance = dis;
    orderTime = time;

    // initialize cart system for new order
    foodPrice = 0;
    items.clear();

    status = 0;
    paymentStatus = "Pending";

    // mark driver as unavailable when assigned to this order
    if (driver != NULL)
        driver->setAvailability(false);

    // add this order to customer's order history
    if (customer != NULL)
        customer->PLaceOrder(this);
}

// ================= SETTERS =================
void Order::setOrderTime(string time) { orderTime = time; }
void Order::setDistance(double dis) { distance = dis; }

void Order::setPaymentStatus(string statusText) {
    paymentStatus = statusText;
}

void Order::setCustomer(Customer* c) { customer = c; }
void Order::setRestaurant(Restaurant* r) { restaurant = r; }
void Order::setDriver(Driver* d) { driver = d; }
void Order::setPayment(Payment* p) { payment = p; }

// ================= GETTERS =================
int Order::getOrderID() { return orderID; }
string Order::getOrderTime() { return orderTime; }
double Order::getDistance() { return distance; }
double Order::getFoodPrice() { return foodPrice; }
string Order::getPaymentStatus() { return paymentStatus; }

// ================= ORDER STATUS FUNCTIONS =================

// move order from Preparing → On The Way
void Order::startDelivery() {
    if (status == 0)
        status = 1;
}

// move order from On The Way → Delivered
void Order::deliverOrder() {
    if (status == 1)
        status = 2;
}

// cancel order if not yet delivered
void Order::cancelOrder() {

    if (status != 2) {

        status = -1;
        paymentStatus = "Failed";

        // release driver back to available state
        if (driver != NULL)
            driver->setAvailability(true);
    }
}

// convert numeric status into readable text
string Order::getStatus() {

    if (status == 0) return "Preparing";
    if (status == 1) return "On The Way";
    if (status == 2) return "Delivered";

    return "Cancelled";
}


// returns a formatted order ID in a readable style (e.g., O-0001)
string Order::getFormattedOrderID() {

    // create string stream to format the ID
    stringstream ss;

    // format ID as O-0001, O-0002, etc.
    ss << "O-" << setfill('0') << setw(4) << orderID;

    // return the formatted string
    return ss.str();
}


// ================= ADD ITEM TO ORDER =================
// adds food item from restaurant menu using item ID
void Order::addItemToOrder(int itemID) {

    // ensure order is linked to a restaurant
    if (restaurant == NULL) {
        cout << "No restaurant assigned!\n";
        return;
    }

    // get menu safely from restaurant
    const Menu& menu = restaurant->getMenu();

    // validate item selection
    if (!menu.isItemValid(itemID)) {
        cout << "Invalid item ID!\n";
        return;
    }

    // fetch item details from menu system
    string name = menu.getItemName(itemID);
    double price = menu.getItemPrice(itemID);

    // check if item already exists in cart (avoid duplicates)
    for (int i = 0; i < items.size(); i++) {

        if (items[i].name == name) {

            // increase quantity instead of adding duplicate
            items[i].quantity++;
            foodPrice += price;

            cout << "Increased quantity: " << name << "\n";
            return;
        }
    }

    // create new item entry in cart
    OrderItem newItem;
    newItem.name = name;
    newItem.price = price;
    newItem.quantity = 1;

    items.push_back(newItem);
    foodPrice += price;

    cout << "Added: " << name << " | " << price << " OMR\n";
}

// ================= PAYMENT PROCESS =================
// handles payment using polymorphism (Card or Cash automatically)
void Order::processPayment() {

    if (payment == NULL) {
        cout << "No payment method selected!\n";
        return;
    }

    // set final calculated amount before payment processing
    payment->setAmount(foodPrice);

    // execute payment based on actual object type (CardPayment / CashPayment)
    bool success = payment->processPayment();

    if (success)
        paymentStatus = "Completed";
    else
        paymentStatus = "Failed";
}

// ================= TOTAL CALCULATION =================
// calculates final price including delivery fee if driver exists
double Order::calculateTotalFee() {

    if (driver == NULL)
        return foodPrice;

    return foodPrice + driver->calcDeliveryFee(distance);
}

// ================= DISPLAY ORDER =================
// prints full order summary including items, status, and totals
void Order::displayOrder() {

    cout << "\n===== ORDER DETAILS =====\n";

    cout << "Order ID: " << getFormattedOrderID() << endl;

    cout << "Items:\n";

    // loop through cart and display all items
    for (int i = 0; i < items.size(); i++) {

        cout << "- " << items[i].name
             << " x" << items[i].quantity
             << " | " << items[i].price << " OMR each\n";
    }

    cout << "Time: " << orderTime << endl;
    cout << "Status: " << getStatus() << endl;
    cout << "Payment Status: " << paymentStatus << endl;

    // display linked objects only if they exist
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
