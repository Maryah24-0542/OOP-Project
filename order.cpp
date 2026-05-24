#include "Order.h"
#include "Driver.h"
#include <bits/stdc++.h>

// ================= STATIC VARIABLE =================
// used to generate unique IDs for each order
int Order::count = 1;

// ================= DEFAULT CONSTRUCTOR =================
Order::Order(Customer *c, Restaurant *r) {
    setOrderID();
    // initialize cart system
    items.clear(); // ensure cart starts empty
    status = "In cart";
    deliveryFee = 0.0;
    // initialize pointers to avoid dangling references
    customer = c;
    restaurant = r;
    driver = nullptr;
    payment = nullptr;
}

Order::~Order() {
    cout << "Order deleted." << endl;
}

// ================= SETTERS =================
// returns a formatted order ID in a readable style (e.g., O-0001)
void Order::setOrderID() {
    // create string stream to format the ID
    stringstream ss;
    // format ID as O-0001, O-0002, etc.
    ss << "O-" << setfill('0') << setw(4) << count++;
    // return the formatted string
    orderID = ss.str();
}

void Order::setStatus(string s) { status = s; }

void Order::setDeliveryFee() {
    deliveryFee = driver->calcDeliveryFee(customer->getAddress(), restaurant->getAddress());
}

void Order::setCustomer(Customer *c) { customer = c; }
void Order::setRestaurant(Restaurant *r) { restaurant = r; }
void Order::setDriver(Driver *d) { driver = d; }
void Order::setPayment(Payment *p) { payment = p; }

// ================= GETTERS =================
string Order::getOrderID() { return orderID; }
string Order::getStatus() { return status; }
double Order::getDeliveryFee() { return deliveryFee; }
Customer *Order::getCustomer() { return customer; }
Restaurant *Order::getRestaurant() { return restaurant; }
Driver *Order::getDriver() { return driver; }
Payment *Order::getPayment() { return payment; }
// ================= ORDER STATUS FUNCTIONS =================

void Order::updateStatus() {
    if (status == "In cart") status = "Preparing";
    else if (status == "Preparing") status = "Ready for Pickup";
    else if (status == "Ready for Pickup") status = "On The Way";
    else if (status == "On The Way") {
        status = "Delivered";
        updatePayment();
        driver->addEarnings(deliveryFee);
        driver->clearAssignedOrder();
    }
}

// cancel order if not yet delivered
void Order::cancelOrder() {
    if (status == "In cart")
        status = "Cancelled";
    if (status == "Preparing") {
        status = "Cancelled";
        driver->clearAssignedOrder();
        // restaurant->removeAssignedOrder(this);
    }
    cout << "Order cancelled successfully." << endl;
}

// ================= ADD ITEM TO ORDER =================
// adds food item from restaurant menu using item ID
void Order::addItemToOrder(int itemNumber) {
    const Menu &menu = restaurant->getMenu(); // get menu safely from restaurant
    if (!menu.isItemValid(itemNumber)) {
        // validate item selection
        cout << "Invalid item ID!\n";
        return;
    }
    OrderItem newItem; // create new item entry in cart
    // fetch item details from menu system
    newItem.name = menu.getItemName(itemNumber);
    newItem.price = menu.getItemPrice(itemNumber);
    cout << "Enter quantity: ";
    cin >> newItem.quantity;
    items.push_back(newItem);
    cout << "Added: " << newItem.name << " x" << newItem.quantity << " | " << newItem.price * newItem.quantity
            << " OMR\n";
}

// ================= PAYMENT PROCESS =================
void Order::updatePayment() {
    payment->setStatus("Completed");
}

// ================= TOTAL CALCULATION =================
// calculates final price including delivery fee if driver exists
double Order::calcFoodPrice() {
    double foodPrice = 0;
    for (OrderItem item: items) {
        foodPrice += item.price * item.quantity;
    }
    return foodPrice;
}

double Order::calculateTotalFee() {
    double total = calcFoodPrice() + deliveryFee;
    payment->setAmount(total);
    return total;
}

double Order::calcOrderTime() {
    double prepTime = restaurant->calcPrepTime(items.size());
    double deliveryTime = driver->calcEstTime(customer->getAddress(), restaurant->getAddress());
    return prepTime + deliveryTime;
}

// ================= DISPLAY ORDER =================

void Order::checkoutDisplay() {
    cout << "Order ID: " << getOrderID() << endl;
    cout << "Restaurant: " << restaurant->getName() << endl;
    cout << "Items:\n";
    for (int i = 0; i < items.size(); i++) {
        cout << i + 1 << "- " << items[i].name
                << " x" << items[i].quantity
                << " | " << items[i].price * items[i].quantity << " OMR\n";
    }
    cout << "Food Price: " << calcFoodPrice() << " OMR\n";
    cout << "======================\n";
}

// prints full order summary including items, status, and totals
void Order::customerDisplayOrder() {
    cout << "=== ORDER DETAILS ===\n";
    checkoutDisplay();
    cout << "Delivery Fee: " << deliveryFee << " OMR\n";
    cout << "Total Price: " << calculateTotalFee() << " OMR" << endl;
    cout << "======================\n";
    cout << "Estimated Time: " << calcOrderTime() << endl;
    cout << "Order Status: " << getStatus() << endl;
    cout << "Payment Type: " << payment->getPaymentType() << ", status: " << payment->getStatus() << endl;
    cout << "Driver: " << driver->getDriverName() << ", contact number: " << driver->getDriverPhone() << endl;
    cout << "======================\n";
}

void Order::driverDisplayOrder() {
    cout << "=== ASSIGNED ORDER ===\n";
    cout << "Order ID: " << getOrderID() << endl;
    cout << "======================\n";
    cout << "Pickup From:\n";
    cout << "Restaurant: " << restaurant->getName() << endl;
    cout << "Address: " << restaurant->getAddress() << endl;
    cout << "======================\n";
    cout << "Deliver To:\n";
    cout << "Customer: " << customer->getName() << endl;
    cout << "Address: " << customer->getAddress() << endl;
    cout << "Phone: " << customer->getPhone() << endl;
    cout << "======================\n";
    cout << "Order Status: " << getStatus() << endl;
    cout << "Payment Type: " << payment->getPaymentType() << endl;
    cout << "Payment Status: " << payment->getStatus() << endl;
    cout << "======================\n";
    cout << "Delivery Fee: " << deliveryFee << " OMR\n";
    cout << "Estimated Delivery Time: "
            << driver->calcEstTime(customer->getAddress(), restaurant->getAddress())
            << " minutes\n";
    cout << "======================\n";
}

void Order::restaurantDisplayOrder() {
    cout << "=== RESTAURANT ORDER ===\n";
    cout << "Order ID: " << getOrderID() << endl;
    cout << "Customer: " << customer->getName() << endl;
    cout << "Order Status: " << getStatus() << endl;
    cout << "========================\n";
    cout << "Items to Prepare:\n";
    for (int i = 0; i < items.size(); i++) {
        cout << i + 1 << "- " << items[i].name
                << " x" << items[i].quantity << endl;
    }
    cout << "========================\n";
    cout << "\nEstimated Preparation Time: "
            << restaurant->calcPrepTime(items.size())
            << " minutes\n";
    cout << "========================\n";
}
