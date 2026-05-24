#include "Company.h"
#include "Order.h"
#include <bits/stdc++.h>

Company::Company() {
}

Company::~Company() {
    for (Driver *d: drivers) {
        delete d;
    }
}

//Customer Methods
Customer *Company::newCustomer() {
    cout << "=== Register as New Customer ===" << endl;
    cout << "Welcome, Please enter the following information:" << endl;
    Customer newC = Customer();
    customers.push_back(newC);
    return &customers.back();
}

Customer *Company::customerLogin() {
    if (customers.empty()) {
        cout << "No customers in the system yet, please sign in as a new customer." << endl;
        return newCustomer();
    }
    cout << "=== Login ===" << endl;
    cout << "Enter your ID: ";
    string id;
    cin >> id;
    for (Customer &customer: customers) {
        if (customer.getCustomerID() == id) {
            cout << "Welcome back, " << customer.getName() << "!" << endl;
            return &customer; //so that it stops executing the rest of the method
        }
    }
    cout << "Invalid ID! Try Again" << endl;
    return customerLogin();
}

Order *Company::newOrder(Customer *c) {
    Order *order = nullptr;
    while (true) {
        displayRestaurants();
        cout << "Enter restaurant number: ";
        int number;
        cin >> number;
        cout << "=== " << restaurants[--number].getName() << " ===" << endl;
        restaurants[number].getMenu().display();
        cout << "Would you like to add items from this restaurant to your cart? (y/n) ";
        char choice;
        cin >> choice;
        if (choice == 'y') {
            if (order == nullptr) {
                order = new Order(c, &restaurants[number]);
            }
            char addMore = 'y';
            while (addMore == 'y') {
                cout << "Enter item number: ";
                int itemNumber;
                cin >> itemNumber;
                order->addItemToOrder(itemNumber);
                cout << "Would you like to add more items from this restaurant? (y/n) ";
                cin >> addMore;
            }
        }
        if (order != nullptr) {
            int nextChoice;
            cout << "What would you like to do?\n"
                    "1. Cancel Order\n"
                    "2. Checkout" << endl;
            cout << "Enter choice: ";
            cin >> nextChoice;
            if (nextChoice == 1) {
                order->cancelOrder();
                delete order;
                order = nullptr;
            }
            if (nextChoice == 2) {
                checkout(order);
                return order;
            }
        } else {
            cout << "Your cart is empty." << endl;
            return order;
        }
    }
}

Driver *Company::assignDriver(Order *order) {
    string custAdd = order->getCustomer()->getAddress();
    string restAdd = order->getRestaurant()->getAddress();
    // Same area: prefer BikeDriver
    if (custAdd == restAdd) {
        for (Driver *d: drivers) {
            if (d->getAvailability() && dynamic_cast<BikeDriver *>(d) != nullptr) {
                d->setAssignedOrder(order);
                order->setDriver(d);
                return d;
            }
        }
    }
    // Different area: prefer CarDriver
    else {
        for (Driver *d: drivers) {
            if (d->getAvailability() && dynamic_cast<CarDriver *>(d) != nullptr) {
                d->setAssignedOrder(order);
                order->setDriver(d);
                return d;
            }
        }
    }
    // If preferred type is not available, assign any available driver
    for (Driver *d: drivers) {
        if (d->getAvailability()) {
            d->setAssignedOrder(order);
            order->setDriver(d);
            return d;
        }
    }
}

void Company::checkout(Order *order) {
    cout << "=== CHECKOUT ===\n";
    order->checkoutDisplay();
    int paymentChoice;
    cout << "\nChoose payment method:\n"
            "1. Cash\n"
            "2. Card" << endl;
    do {
        cout << "Enter choice: ";
        cin >> paymentChoice;
        if (paymentChoice == 1) {
            Payment *p = new CashPayment();
            order->setPayment(p);
            p->paymentReciept();
        } else if (paymentChoice == 2) {
            Payment *p = new CardPayment();
            order->setPayment(p);
            p->paymentReciept();
        } else {
            cout << "Invalid payment choice, please try again\n";
        }
    } while (paymentChoice != 1 && paymentChoice != 2);
    Driver *assignedDriver = assignDriver(order);
    order->updateStatus();
    cout << "=== ORDER CONFIRMATION ===\n";
    cout << "Order placed successfully.\n";
    order->customerDisplayOrder();
}

void Company::viewCurrentOrder(Order *order) {
    if (order == nullptr) {
        cout << "No orders yet" << endl;
        return;
    } else {
        cout << "=== Current order ===" << endl;
        order->customerDisplayOrder();
        if (order->getStatus() == "Preparing") {
            int cancel;
            cout << "1. Cancel Order\n"
                    "2. Back" << endl;
            cin >> cancel;
            if (cancel == 1) {
                order->cancelOrder();
                delete order;
                order = nullptr;
                return;
            } else return;
        }
    }
}

void Company::viewCustomerInfo(Customer *customer) {
    customer->display();
    int update;
    cout << "1. Update my information\n"
            "2. Back" << endl;
    cout << "Enter choice: ";
    cin >> update;
    if (update == 1) {
        cout << "What do you want to update?"
                "\n1. Name"
                "\n2. Phone number"
                "\n3. Email"
                "\n4. Address" << endl;
        cout << "Enter choice: ";
        cin >> update;
        if (update == 1) {
            customer->setName();
            cout << "Information Updated" << endl;
        } else if (update == 2) {
            customer->setPhone();
            cout << "Information Updated" << endl;
        } else if (update == 3) {
            customer->setEmail();
            cout << "Information Updated" << endl;
        } else if (update == 4) {
            customer->setAddress();
            cout << "Information Updated" << endl;
        } else {
            cout << "Information wasn't updated" << endl;
            return;
        }
    } else return;
    return;
}

//Driver
Driver *Company::newBikeDriver() {
    cout << "=== Register as New Bike Driver ===" << endl;
    cout << "Welcome, Please enter the following information:" << endl;
    Driver *newD = new BikeDriver();
    drivers.push_back(newD);
    return newD;
}

Driver *Company::newCarDriver() {
    cout << "=== Register as New Car Driver ===" << endl;
    cout << "Welcome, Please enter the following information:" << endl;
    Driver *newD = new CarDriver();
    drivers.push_back(newD);
    return newD;
}

Driver *Company::driverLogin() {
    if (drivers.empty()) {
        cout << "No drivers in the system yet, please sign in as a new driver." << endl;
        return nullptr;
    }
    cout << "=== Login ===" << endl;
    cout << "Enter your ID: ";
    string id;
    cin >> id;

    for (Driver *driver: drivers) {
        if (driver->getDriverID() == id) {
            cout << "Welcome back, " << driver->getDriverName() << "!" << endl;
            return driver;
        }
    }
    cout << "Invalid ID! Try again" << endl;
    return driverLogin();
}

void Company::viewAssignedOrder(Driver *driver) {
    Order *order = driver->getAssignedOrder();
    if (order == nullptr) {
        cout << "You have no assigned order right now." << endl;
        return;
    }
    order->driverDisplayOrder();
}
void Company::driverUpdateOrder(Driver *driver) {
    Order *order = driver->getAssignedOrder();
    if (order == nullptr) {
        cout << "You have no assigned order right now." << endl;
        return;
    }
    cout << "=== UPDATE ORDER STATUS ===" << endl;
    cout << "Current Status: " << order->getStatus() << endl;
    //stopped here
}
//Restaurant
Restaurant *Company::newRestaurant() {
    cout << "=== Register as New Restaurant ===" << endl;
    cout << "Welcome, Please enter the following information:" << endl;
    Restaurant newR = Restaurant();
    restaurants.push_back(newR);
    return &restaurants.back();
}

Restaurant *Company::restaurantLogin() {
    if (restaurants.empty()) {
        cout << "No restaurants in the system yet, please register as a new restaurant." << endl;
        return nullptr;
    }
    cout << "=== Login ===" << endl;
    cout << "Enter your Restaurant ID: ";
    string id;
    cin >> id;

    for (Restaurant &restaurant: restaurants) {
        if (restaurant.getId() == id) {
            cout << "Welcome back!" << endl;
            return &restaurant;
        }
    }
    cout << "Invalid ID! Try again." << endl;
    return restaurantLogin();
}


void Company::displayRestaurants() const {
    cout << "=== Restaurants ===" << endl;
    for (int i = 0; i < restaurants.size(); i++)
        cout << "(" << i + 1 << ") " << restaurants[i].getName()
                << " (" << restaurants[i].getCuisine() << " Cuisine)" << endl;
}
