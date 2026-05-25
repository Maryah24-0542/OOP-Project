#include "Restaurant.h"
#include <bits/stdc++.h>
#include "Order.h"
using namespace std;

int Restaurant::count = 1;

Restaurant::Restaurant() {
    setName();
    setCuisine();
    setAddress();
    setBasePrepTime();
    setExtraTimePerItem();
    stringstream ss;
    ss << "R-" << setfill('0') << setw(4) << count++; //total of 4 digits (including the number from count)...  i guess
    restaurantId = ss.str(); //turn it into a string like "R-0001"
    cout << "Restaurant: " << name << " has been added, your restaurant ID: " << restaurantId << endl;
    cout << "You must add at least one item to the menu" << endl;
    addToMenu();
}

void Restaurant::addToMenu() {
    menu.addItemName();
    menu.addItemPrice();
    cout << "Item added successfully." << endl;
}

void Restaurant::updateMenu(int ch) {
    menu.updateItemName(ch);
    menu.updateItemPrice(ch);
    cout << "Item updated successfully." << endl;
}

double Restaurant::calcPrepTime(int itemCount) {
    if (itemCount <= 2)
        return basePrepTime;
    return basePrepTime + (itemCount - 2) * extraTimePerItem;
}

void Restaurant::display() {
    cout << "=== Restaurant Info ===" << endl;
    cout << "Restaurant ID: " << restaurantId << endl;
    cout << "Restaurant: " << name << endl;
    cout << "Cuisine: " << cuisine << endl;
    cout << "Location: " << address << endl;
    cout << "Base preparation time: " << basePrepTime << endl;
    cout << "Extra time per item: " << extraTimePerItem << endl;
    cout << "Menu: " << endl;
    menu.display();
    cout << "=======================" << endl;
}

//getters
string Restaurant::getName() const { return name; }
string Restaurant::getCuisine() const { return cuisine; }
string Restaurant::getAddress() const { return address; }
string Restaurant::getId() const { return restaurantId; }
double Restaurant::getBasePrepTime() const { return basePrepTime; }
double Restaurant::getExtraTimePerItem() const { return extraTimePerItem; }
// returns the restaurant's menu object
// allows access to all menu items (names and prices)
Menu &Restaurant::getMenu() { return menu; }
//setters
void Restaurant::setName() {
    cout << "Enter restaurant's name: ";
    cin >> name;
}

void Restaurant::setCuisine() {
    cout << "Enter restaurant's cuisine: ";
    cin >> cuisine;
}

void Restaurant::setAddress() {
    cout << "Enter restaurant's address: ";
    cin >> address;
}

void Restaurant::setBasePrepTime() {
    cout << "Enter restaurant's base preparation time: ";
    cin >> basePrepTime;
}

void Restaurant::setExtraTimePerItem() {
    cout << "Enter restaurant's extra time per item: ";
    cin >> extraTimePerItem;
}

void Restaurant::updateOrderStatus(Order *order) {
    order->updateStatus(); //update order state
}

void Restaurant::addAssignedOrder(Order *order) {
    assignedOrders.push_back(order);
}

bool Restaurant::displayAssignedOrders() const {
    if (assignedOrders.empty()) {
        cout << "No assigned orders.\n";
        return false;
    }
    cout << "=== ASSIGNED ORDERS ===\n";
    for (int i = 0; i < assignedOrders.size(); i++) {
        cout << "Order #" << i + 1 << endl;
        cout << *assignedOrders[i];
    }
    return true;
}

void Restaurant::clearAssignedOrder(Order *order) {
    for (int i = 0; i < assignedOrders.size(); i++) {
        if (assignedOrders[i] == order) {
            assignedOrders[i] = assignedOrders.back(); //we replace it with last element
            assignedOrders.pop_back(); //then we remove last element (the order)
            return;
        }
    }
}

Order *Restaurant::searchOrderByID(string orderID) {
    for (Order *order: assignedOrders) {
        if (order->getOrderID() == orderID) {
            return order;
        }
    }
    return nullptr;
}
