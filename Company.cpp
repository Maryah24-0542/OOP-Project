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
    //stopped here
    return nullptr;
}

void Company::checkout(Order *order) {
    cout << "=== CHECKOUT ===\n";
    order->checkoutDisplay();
    cout << "\nChoose payment method:\n"
            "1. Cash\n"
            "2. Card\n";
    cout << "Enter choice: ";
    int paymentChoice;
    cin >> paymentChoice;
    //incomplete, waiting for assignDriver
}

void Company::viewCurrentOrder(Order *order) {
    if (order == nullptr) {
        cout << "No orders yet" << endl;
        return;
    } else {
        cout << "=== Current order ===" << endl;
        order->displayOrder();
        if (order->getStatus() == "Preparing") {
            int cancel;
            cout << "1. Cancel Order\n"
                    "2. Back";
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
            "2. Back";
    cout << "Enter choice: ";
    cin >> update;
    if (update == 1) {
        cout << "What do you want to update?"
                "\n1. Name"
                "\n2. Phone number"
                "\n3. Email"
                "\n4. Address";
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
