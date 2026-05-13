#include "Order.h"
#include <iostream>
using namespace std;

// Static counter initialisations 
int Order::nextOrderID = 0;
int Item::nextItemID   = 0;



//  Item  implementations
Item::Item(string name, int qty, double p)
    : itemName(name), quantity(qty), price(p)
{
    itemID = ++nextItemID;
}

// Getters
int    Item::getItemID()   const { return itemID;   }
string Item::getItemName() const { return itemName; }
int    Item::getQuantity() const { return quantity; }
double Item::getPrice()    const { return price;    }

// Setters
void Item::setItemName(string n) { itemName = n; }
void Item::setQuantity(int q)    { quantity = q; }
void Item::setPrice(double p)    { price    = p; }

void Item::display() const {
    cout << "  [Item #" << itemID << "]  "
         << itemName
         << "  x" << quantity
         << "  @ " << price << " OMR each"
         << "  = " << (price * quantity) << " OMR" << endl;
}



//  Order  implementations
//  Constructor
//  Customer is now passed as a POINTER
// so PLaceOrder() updates the REAL customer object, not a copy
Order::Order(Customer* c, Restaurant* rest, string address, double distanceKm, string time)
    : customer(c),
      restaurant(rest),
      driver(nullptr),
      payment(nullptr),
      deliveryAddress(address),
      distance(distanceKm),
      orderTime(time),
      status("Pending"),
      itemsTotal(0.0),
      deliveryFee(0.0),
      totalAmount(0.0),
      estimatedTime(0.0),
      isCancelled(false),
      cancellationReason("")
{
    orderID = ++nextOrderID;

    // Now this actually updates the real customer's order history
    customer->PLaceOrder(this);

    cout << "Order #" << orderID << " created  (status: Pending)" << endl;
}

// Destructor 
Order::~Order() {
    delete payment;   // Order owns payment → delete it
   
}

//  Setters
void Order::setOrderTime(string t)       { orderTime       = t; }
void Order::setStatus(string s)          { status          = s; }
void Order::setDeliveryAddress(string a) { deliveryAddress = a; }

void Order::setDistance(double d) {
    distance = d;
    if (driver != nullptr) {
        deliveryFee   = driver->calcDeliveryFee(distance);
        estimatedTime = driver->getESTtime(distance);
        totalAmount   = itemsTotal + deliveryFee;
    }
}

void Order::setDriver(Driver* d) {
    driver        = d;
    deliveryFee   = driver->calcDeliveryFee(distance);
    estimatedTime = driver->getESTtime(distance);
    totalAmount   = itemsTotal + deliveryFee;
    driver->assignOrder(orderID);
    cout << "Driver \""    << driver->getName()
         << "\" assigned to Order #" << orderID             << endl;
    cout << "Delivery fee : " << deliveryFee   << " OMR"    << endl;
    cout << "Estimated ETA: " << estimatedTime << " minutes"<< endl;
}

void Order::setPayment(Payment* p) {
    payment = p;
    if (payment->processPayment()) {
        updateStatus("Paid");
    } else {
        cout << "Payment failed for Order #" << orderID << endl;
    }
}

// Getters
int          Order::getOrderID()            const { return orderID;           }
string       Order::getOrderTime()          const { return orderTime;         }
string       Order::getStatus()             const { return status;            }
double       Order::getItemsTotal()         const { return itemsTotal;        }
double       Order::getDeliveryFee()        const { return deliveryFee;       }
double       Order::getTotalAmount()        const { return totalAmount;       }
string       Order::getDeliveryAddress()    const { return deliveryAddress;   }
double       Order::getDistance()           const { return distance;          }
double       Order::getEstimatedTime()      const { return estimatedTime;     }
bool         Order::getIsCancelled()        const { return isCancelled;       }
string       Order::getCancellationReason() const { return cancellationReason;}
Customer*    Order::getCustomer()           const { return customer;          }
Restaurant*  Order::getRestaurant()         const { return restaurant;        }
Driver*      Order::getDriver()             const { return driver;            }
Payment*     Order::getPayment()            const { return payment;           }
vector<Item> Order::getItems()              const { return items;             }


// addItem 
void Order::addItem(string name, int qty, double price) {

    // Block if cancelled 
    if (isCancelled) {
        cout << "Cannot add items – Order #" << orderID << " is cancelled." << endl;
        return;
    }

    //  Quantity validation 
    if (qty <= 0) {
        cout << "Invalid quantity \"" << qty << "\" – must be greater than 0." << endl;
        return;
    }

 
    if (restaurant != nullptr) {
        if (!restaurant->getMenu().hasItem(name)) {
            cout << "\"" << name << "\" is not on the menu of "
                 << "this restaurant. Item not added." << endl;
            return;
        }
        // Use the real menu price instead of whatever the caller passed
        price = restaurant->getMenu().getItemPrice(name);
    }

    // All checks passed – add the item 
    items.push_back(Item(name, qty, price));
    calculateTotal();
    cout << "Added [Item #" << items.back().getItemID() << "] "
         << name << "  x" << qty
         << "  @ " << price << " OMR" << endl;
}

//removeItem 
void Order::removeItem(int itemID) {

    // Rule: can only remove while still Pending
    if (status != "Pending") {
        cout << "Cannot remove items – Order #" << orderID
             << " is already \"" << status << "\"." << endl;
        return;
    }

    // Search for the item by ID
    for (int i = 0; i < items.size(); i++) {
        if (items[i].getItemID() == itemID) {
            cout << "Removed [Item #" << itemID << "] "
                 << items[i].getItemName()
                 << " from Order #" << orderID << endl;
            items.erase(items.begin() + i);
            calculateTotal();   // update total after removal
            return;
        }
    }

    cout << "Item #" << itemID << " not found in Order #" << orderID << endl;
}

// cancelOrder 
bool Order::cancelOrder(string reason) {

    // Rule: can only cancel while still Pending
    if (status != "Pending") {
        cout << "Cannot cancel Order #" << orderID
             << " – it is already \"" << status << "\"." << endl;
        return false;
    }

    isCancelled        = true;
    cancellationReason = reason;
    updateStatus("Cancelled");

    // Free the driver if one was pre-assigned
    if (driver != nullptr) {
        // driver->setAvailable(true);  // uncomment once Driver has this setter
        driver = nullptr;
    }

    cout << "Order #" << orderID
         << " cancelled. Reason: " << reason << endl;
    return true;
}

//calculateTotal 
double Order::calculateTotal() {
    itemsTotal = 0.0;
    for (int i = 0; i < items.size(); i++) {
        itemsTotal += items[i].getPrice() * items[i].getQuantity();
    }
    if (driver != nullptr) {
        deliveryFee = driver->calcDeliveryFee(distance);
    }
    totalAmount = itemsTotal + deliveryFee;
    return totalAmount;
}

// updateStatus
void Order::updateStatus(string newStatus) {
    status = newStatus;
    cout << "Order #" << orderID << "  status → " << status << endl;
}

// displayOrder
void Order::displayOrder() const {
    cout << "\n========================================" << endl;
    cout << "        ORDER SUMMARY  #" << orderID        << endl;
    cout << "========================================" << endl;
    cout << "Time          : " << orderTime              << endl;
    cout << "Status        : " << status                 << endl;

    if (isCancelled)
        cout << "Cancel Reason : " << cancellationReason << endl;

    cout << "Address       : " << deliveryAddress        << endl;
    cout << "Distance      : " << distance << " km"      << endl;

    // Customer
    cout << "\n--- Customer ---"                          << endl;
    cout << "Name          : " << customer->getName()    << endl;
    cout << "Phone         : " << customer->getPhone()   << endl;
    cout << "Email         : " << customer->getEmail()   << endl;

    // Restaurant
    if (restaurant != nullptr) {
        cout << "\n--- Restaurant ---" << endl;
        restaurant->display();
    }

    // Items 
    cout << "\n--- Items Ordered ---" << endl;
    if (items.empty()) {
        cout << "  (no items)" << endl;
    } else {
        for (int i = 0; i < items.size(); i++) {
            items[i].display();
        }
    }
    cout << "Items Total   : " << itemsTotal  << " OMR" << endl;
    cout << "Delivery Fee  : " << deliveryFee << " OMR" << endl;
    cout << "GRAND TOTAL   : " << totalAmount << " OMR" << endl;

    // Driver 
    if (driver != nullptr) {
        cout << "\n--- Driver ---"                                 << endl;
        driver->showDetails();
        cout << "Estimated ETA : " << estimatedTime << " minutes" << endl;
    } else {
        cout << "\nDriver        : Not assigned yet" << endl;
    }

    //Payment
    if (payment != nullptr) {
        cout << "\n--- Payment ---"                                   << endl;
        cout << "Payment ID    : " << payment->getPaymentID()        << endl;
        cout << "Amount        : " << payment->getAmount() << " OMR" << endl;
        cout << "Status        : " << payment->getStatus()           << endl;
        cout << "Type          : " << payment->getPaymentType()      << endl;
    } else {
        cout << "\nPayment       : Not processed yet" << endl;
    }

    cout << "========================================\n" << endl;
}
