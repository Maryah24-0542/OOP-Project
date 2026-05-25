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
    if (restaurants.empty()) {
        cout << "No restaurants available right now." << endl;
        return nullptr;
    }
    Order *order = nullptr;
    while (true) {
        displayRestaurants();
        int number;
        do {
            try {
                // Exception handling: prevents the user from choosing a restaurant number that does not exist in the displayed restaurant list
                cout << "Enter restaurant number: ";
                cin >> number;
                if (number < 1 || number > restaurants.size()) {
                    throw invalid_argument("Invalid restaurant number. Please choose a number from the list.");
                }
                break;
            } catch (invalid_argument &e) {
                cout << e.what() << endl;
            }
        } while (true);
        number--; // convert from user number to vector index
        cout << "=== " << restaurants[number].getName() << " Menu ===" << endl;
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
            // dynamic_cast is used to check the actual driver type because drivers are stored as Driver* pointers
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
    return nullptr;
}

void Company::checkout(Order *order) {
    cout << "=== CHECKOUT ===\n";
    order->checkoutDisplay();
    // A driver must be assigned before payment because delivery fee is needed to calculate the final order total
    Driver *assignedDriver = assignDriver(order);
    if (assignedDriver == nullptr) {
        cout << "No available drivers right now." << endl;
        cout << "Your cart is saved. You can try checkout again later from View Current Order." << endl;
        return;
    }
    // Delivery fee is calculated after the driver is assigned
    order->setDeliveryFee();
    cout << "Delivery Fee: " << order->getDeliveryFee() << " OMR\n";
    int paymentChoice;
    Payment *p = nullptr;
    cout << "\nChoose payment method:\n"
            "1. Cash\n"
            "2. Card" << endl;
    do {
        cout << "Enter choice: ";
        cin >> paymentChoice;
        if (paymentChoice == 1) {
            p = new CashPayment();
        } else if (paymentChoice == 2) {
            p = new CardPayment();
        } else {
            cout << "Invalid payment choice, please try again\n";
        }
    } while (paymentChoice != 1 && paymentChoice != 2);
    // Payment object must be attached before calculating total fee
    order->setPayment(p);
    order->calculateTotalFee();
    p->paymentReciept();
    // Changes order status from In cart to Preparing
    order->updateStatus();
    cout << "=== ORDER CONFIRMATION ===\n";
    cout << "Order placed successfully.\n";
    order->customerDisplayOrder();
}

void Company::viewMyOrder(Order *&order) {
    if (order == nullptr) {
        cout << "No orders yet" << endl;
        return;
    }
    if (order->getStatus() == "In cart") {
        order->checkoutDisplay();
        int choice;
        do {
            cout << "Your order is still in cart.\n";
            cout << "1. Proceed to Checkout\n"
                    "2. Cancel Order\n"
                    "3. Back\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) {
                for (Driver *d: drivers) {
                    if (d->getAvailability()) {
                        checkout(order);
                        return;
                    }
                }
                cout << "No available drivers yet" << endl;
                return;
            } else if (choice == 2) {
                order->cancelOrder();
                delete order;
                order = nullptr;
                return;
            } else if (choice == 3) {
                return;
            } else {
                cout << "Invalid input, please enter a valid option." << endl;
            }
        } while (choice != 3);
    } else {
        order->customerDisplayOrder();
        if (order->getStatus() == "Preparing") {
            int cancel;
            do {
                cout << "1. Cancel Order\n";
                cout << "2. Back\n";
                cout << "Enter choice: ";
                cin >> cancel;

                if (cancel == 1) {
                    order->cancelOrder();
                    delete order;
                    order = nullptr;
                    return;
                } else if (cancel == 2) {
                    return;
                } else {
                    cout << "Invalid input, please enter a valid option." << endl;
                }
            } while (cancel != 2);
        }
    }
}

void Company::viewCustomerInfo(Customer *customer) {
    customer->display();

    int update;

    do {
        cout << "1. Update my information\n"
                "2. Back" << endl;
        cout << "Enter choice: ";
        cin >> update;

        if (update == 1) {
            int infoChoice;

            do {
                cout << "What do you want to update?"
                        "\n1. Name"
                        "\n2. Phone number"
                        "\n3. Email"
                        "\n4. Address"
                        "\n5. Back" << endl;
                cout << "Enter choice: ";
                cin >> infoChoice;

                switch (infoChoice) {
                    case 1:
                        customer->setName();
                        cout << "Your name is updated to " << customer->getName() << endl;
                        return;

                    case 2:
                        customer->setPhone();
                        cout << "Your phone number is updated to " << customer->getPhone() << endl;
                        return;

                    case 3:
                        customer->setEmail();
                        cout << "Your email is updated to " << customer->getEmail() << endl;
                        return;

                    case 4:
                        customer->setAddress();
                        cout << "Your address is updated to " << customer->getAddress() << endl;
                        return;

                    case 5:
                        return;

                    default:
                        cout << "Invalid input, please enter a valid option." << endl;
                        break;
                }
            } while (infoChoice != 5);
        } else if (update == 2) {
            return;
        } else {
            cout << "Invalid input, please enter a valid option." << endl;
        }
    } while (update != 2);
}

void Company::displayRestaurants() const {
    cout << "=== Restaurants ===" << endl;
    for (int i = 0; i < restaurants.size(); i++)
        cout << "(" << i + 1 << ") " << restaurants[i].getName()
                << " (" << restaurants[i].getCuisine() << " Cuisine)" << endl;
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

void Company::viewDriverOrder(Driver *driver) {
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
    if (order->getStatus() == "Preparing") {
        cout << "The order is still being prepared by the restaurant, "
                "please wait until the restaurant marks it as Ready for Pickup." << endl;
        return;
    }
    if (order->getStatus() == "Ready for Pickup" || order->getStatus() == "On The Way") {
        order->updateStatus();
        cout << "Status updated to: " << order->getStatus() << endl;
    }
}

void Company::viewDriverInfo(Driver *driver) {
    driver->showDetails();

    int update;

    do {
        cout << "1. Update my information\n"
                "2. Back" << endl;
        cout << "Enter choice: ";
        cin >> update;

        if (update == 1) {
            int infoChoice;

            do {
                cout << "What do you want to update?"
                        "\n1. Name"
                        "\n2. Phone number"
                        "\n3. Plate number"
                        "\n4. Base fare";
                // Common driver information is updated through the Driver pointer
                // Child-specific information is updated after checking the real driver type
                if (dynamic_cast<BikeDriver *>(driver) != nullptr) {
                    cout << "\n5. Bike model"
                            "\n6. Max load"
                            "\n7. Back";
                } else if (dynamic_cast<CarDriver *>(driver) != nullptr) {
                    cout << "\n5. Car model"
                            "\n6. Back";
                }

                cout << endl;
                cout << "Enter choice: ";
                cin >> infoChoice;

                switch (infoChoice) {
                    case 1:
                        driver->setDriverName();
                        cout << "Your name is updated to " << driver->getDriverName() << endl;
                        return;

                    case 2:
                        driver->setDriverPhone();
                        cout << "Your phone number is updated to " << driver->getDriverPhone() << endl;
                        return;

                    case 3:
                        driver->setPlateNumber();
                        cout << "Your plate number is updated to " << driver->getPlateNumber() << endl;
                        return;

                    case 4:
                        driver->setBaseFare();
                        cout << "Your base fare is updated to " << driver->getBaseFare() << endl;
                        return;

                    case 5:
                        if (dynamic_cast<BikeDriver *>(driver) != nullptr) {
                            BikeDriver *bike = dynamic_cast<BikeDriver *>(driver);
                            bike->setBikeModel();
                            cout << "Your bike model is updated to " << bike->getBikeModel() << endl;
                            return;
                        } else if (dynamic_cast<CarDriver *>(driver) != nullptr) {
                            CarDriver *car = dynamic_cast<CarDriver *>(driver);
                            car->setCarModel();
                            cout << "Your car model is updated to " << car->getCarModel() << endl;
                            return;
                        }
                        break;

                    case 6:
                        if (dynamic_cast<BikeDriver *>(driver) != nullptr) {
                            BikeDriver *bike = dynamic_cast<BikeDriver *>(driver);
                            bike->setMaxLoad();
                            cout << "Your max load is updated to " << bike->getMaxLoad() << endl;
                            return;
                        } else if (dynamic_cast<CarDriver *>(driver) != nullptr) {
                            return;
                        }
                        break;

                    case 7:
                        if (dynamic_cast<BikeDriver *>(driver) != nullptr) {
                            return;
                        }
                        cout << "Invalid input, please enter a valid option." << endl;
                        break;

                    default:
                        cout << "Invalid input, please enter a valid option." << endl;
                        break;
                }
            } while (true);
        } else if (update == 2) {
            return;
        } else {
            cout << "Invalid input, please enter a valid option." << endl;
        }
    } while (update != 2);
}

//Restaurant
Restaurant *Company::newRestaurant() {
    cout << "=== Register as New Restaurant ===" << endl;
    cout << "Welcome, Please enter the following information:" << endl;
    Restaurant newR = Restaurant();
    restaurants.push_back(newR);
    Restaurant *restaurant = &restaurants.back();
    char choice;
    do {
        cout << "Do you want to add another menu item? (y/n): ";
        cin >> choice;

        if (choice == 'y') {
            restaurant->addToMenu();
        } else if (choice == 'n') {
            return restaurant;
        } else {
            cout << "Invalid input, please enter y or n." << endl;
        }
    } while (choice != 'n');

    return restaurant;
}

Restaurant *Company::restaurantLogin() {
    if (restaurants.empty()) {
        cout << "No restaurants in the system yet, please register as a new restaurant." << endl;
        return newRestaurant();
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

void Company::viewRestaurantInfo(Restaurant *restaurant) {
    restaurant->display();

    int update;

    do {
        cout << "1. Update restaurant information\n"
                "2. Back" << endl;
        cout << "Enter choice: ";
        cin >> update;

        if (update == 1) {
            int infoChoice;

            do {
                cout << "What do you want to update?"
                        "\n1. Name"
                        "\n2. Cuisine"
                        "\n3. Address"
                        "\n4. Base preparation time"
                        "\n5. Extra time per item"
                        "\n6. Back" << endl;

                cout << "Enter choice: ";
                cin >> infoChoice;

                switch (infoChoice) {
                    case 1:
                        restaurant->setName();
                        cout << "Restaurant name is updated to " << restaurant->getName() << endl;
                        return;

                    case 2:
                        restaurant->setCuisine();
                        cout << "Restaurant cuisine is updated to " << restaurant->getCuisine() << endl;
                        return;

                    case 3:
                        restaurant->setAddress();
                        cout << "Restaurant address is updated to " << restaurant->getAddress() << endl;
                        return;

                    case 4:
                        restaurant->setBasePrepTime();
                        cout << "Base preparation time is updated to "
                                << restaurant->getBasePrepTime() << " minutes" << endl;
                        return;

                    case 5:
                        restaurant->setExtraTimePerItem();
                        cout << "Extra time per item is updated to "
                                << restaurant->getExtraTimePerItem() << " minutes" << endl;
                        return;

                    case 6:
                        return;

                    default:
                        cout << "Invalid input, please enter a valid option." << endl;
                        break;
                }
            } while (infoChoice != 6);
        } else if (update == 2) {
            return;
        } else {
            cout << "Invalid input, please enter a valid option." << endl;
        }
    } while (update != 2);
}

void Company::viewRestaurantMenu(Restaurant *restaurant) {
    cout << "=== RESTAURANT MENU ===" << endl;
    restaurant->getMenu().display();
    int update;
    do {
        cout << "=======================" << endl;
        cout << "1. Edit menu\n"
                "2. Back" << endl;
        cout << "Enter choice: ";
        cin >> update;
        if (update == 1) {
            int menuChoice, itemNumber;
            do {
                cout << "What do you want to do?"
                        "\n1. Add item"
                        "\n2. Edit item"
                        "\n3. Remove item"
                        "\n4. Back" << endl;
                cout << "Enter choice: ";
                cin >> menuChoice;
                switch (menuChoice) {
                    case 1:
                        restaurant->addToMenu();
                        return;
                    case 2: {
                        restaurant->getMenu().display();
                        cout << "Enter item number to edit: ";
                        cin >> itemNumber;
                        restaurant->updateMenu(itemNumber);
                        return;
                    }

                    case 3: {
                        restaurant->getMenu().display();
                        cout << "Enter item number to remove: ";
                        cin >> itemNumber;
                        restaurant->getMenu().removeItem(itemNumber);
                        return;
                    }
                    case 4:
                        return;
                    default:
                        cout << "Invalid input, please enter a valid option." << endl;
                        break;
                }
            } while (menuChoice != 4);
        } else if (update == 2) {
            return;
        } else {
            cout << "Invalid input, please enter a valid option." << endl;
        }
    } while (update != 2);
}

void Company::viewRestaurantOrders(Restaurant *restaurant) {
    bool hasOrders = restaurant->displayAssignedOrders();
    if (!hasOrders) {
        return;
    }
    char choice;
    do {
        cout << "Do you want to update an order status? (y/n): ";
        cin >> choice;
        if (choice == 'y') {
            string orderID;
            Order *selectedOrder = nullptr;
            do {
                cout << "Enter Order ID: ";
                cin >> orderID;
                selectedOrder = restaurant->searchOrderByID(orderID);
                if (selectedOrder == nullptr) {
                    cout << "Invalid Order ID. Please try again.\n";
                }
            } while (selectedOrder == nullptr);
            selectedOrder->updateStatus(); // Preparing -> Ready for Pickup
            cout << "Order status updated to: " << selectedOrder->getStatus() << endl;
            return;
        } else if (choice == 'n') {
            return;
        } else {
            cout << "Invalid input, please enter y or n." << endl;
        }
    } while (choice != 'n');
}
