#include <bits/stdc++.h>
#include "Company.h"

using namespace std;

int main() {
    Company company = Company();
    Order *o = nullptr;
    Customer *c = nullptr;
    Driver *d = nullptr;
    Restaurant *r = nullptr;
    int userChoice, customerChoice, driverChoice, restaurantChoice;
    do {
        cout << "=== FOOD DELIVERY SYSTEM ===" << endl;
        cout << "Login as: \n"
                "1. Customer\n"
                "2. Driver\n"
                "3. Restaurant\n"
                "4. Exit" << endl;
        cout << "Enter your choice number: ";
        cin >> userChoice;
        switch (userChoice) {
            case 1:
                do {
                    cout << "=== Customer Sign In Menu ===" << endl;
                    cout << "1. Register as New Customer\n"
                            "2. Login\n"
                            "3. Back" << endl;
                    cout << "Enter your choice number: ";
                    cin >> customerChoice;
                    switch (customerChoice) {
                        case 1:
                            c = company.newCustomer();
                            break;
                        case 2:
                            c = company.customerLogin();
                            int customerDashboard;
                            do {
                                cout << "=== Customer Dashboard ===\n";
                                cout << "1. Create New Order\n"
                                        "2. View My Order\n"
                                        "3. View My Information\n"
                                        "4. Back to Main Menu\n";
                                cout << "Enter your choice: ";
                                cin >> customerDashboard;
                                switch (customerDashboard) {
                                    case 1:
                                        o = company.newOrder(c);
                                        break;
                                    case 2:
                                        company.viewMyOrder(o);
                                        break;
                                    case 3:
                                        company.viewCustomerInfo(c);
                                        break;
                                    case 4:
                                        break;
                                    default:
                                        cout << "Invalid input, please enter a valid option." << endl;
                                        customerDashboard = 5;
                                        break;
                                }
                            } while (customerDashboard != 4);
                            break;
                        case 3:
                            break;
                        default:
                            cout << "Invalid input, please enter a valid option." << endl;
                            customerChoice = 4;
                            break;
                    }
                } while (customerChoice != 3);
                break;
            case 2:
                do {
                    cout << "=== Driver Sign In Menu ===" << endl;
                    cout << "1. Register as Bike Driver\n"
                            "2. Register as Car Driver\n"
                            "3. Login\n"
                            "4. Back\n";
                    cout << "Enter your choice number: ";
                    cin >> driverChoice;
                    switch (driverChoice) {
                        case 1:
                            d = company.newBikeDriver();
                            break;

                        case 2:
                            d = company.newCarDriver();
                            break;

                        case 3:
                            d = company.driverLogin();

                            if (d != nullptr) {
                                int driverDashboard;

                                do {
                                    cout << "=== Driver Dashboard ===\n"
                                            "1. View My Assigned Order\n"
                                            "2. Update Order Status\n"
                                            "3. View My Information\n"
                                            "4. Back\n";
                                    cout << "Enter your choice: ";
                                    cin >> driverDashboard;

                                    switch (driverDashboard) {
                                        case 1:
                                            company.viewDriverOrder(d);
                                            break;

                                        case 2:
                                            company.driverUpdateOrder(d);
                                            break;

                                        case 3:
                                            company.viewDriverInfo(d);
                                            break;

                                        case 4:
                                            break;

                                        default:
                                            cout << "Invalid input, please enter a valid option." << endl;
                                            break;
                                    }
                                } while (driverDashboard != 4);
                            }

                            break;
                        case 4:
                            break;
                        default:
                            cout << "Invalid input, please enter a valid option." << endl;
                            break;
                    }
                } while (driverChoice != 4);

                break;
            case 3:
                do {
                    cout << "=== Restaurant Sign In Menu ===\n"
                            "1. Register as New Restaurant\n"
                            "2. Login\n"
                            "3. Back\n";
                    cout << "Enter your choice number: ";
                    cin >> restaurantChoice;

                    switch (restaurantChoice) {
                        case 1:
                            r = company.newRestaurant();
                            break;

                        case 2:
                            r = company.restaurantLogin();
                            int restaurantDashboard;

                            do {
                                cout << "=== Restaurant Dashboard ===\n";
                                cout << "1. View My Information\n"
                                        "2. View My Menu\n"
                                        "3. View My Orders\n"
                                        "4. Back to Main Menu\n";
                                cout << "Enter your choice: ";
                                cin >> restaurantDashboard;

                                switch (restaurantDashboard) {
                                    case 1:
                                        company.viewRestaurantInfo(r);
                                        break;

                                    case 2:
                                        company.viewRestaurantMenu(r);
                                        break;

                                    case 3:
                                        company.viewRestaurantOrders(r);
                                        break;

                                    case 4:
                                        break;

                                    default:
                                        cout << "Invalid input, please enter a valid option." << endl;
                                        break;
                                }
                            } while (restaurantDashboard != 4);
                            break;

                        case 3:
                            break;

                        default:
                            cout << "Invalid input, please enter a valid option." << endl;
                            break;
                    }
                } while (restaurantChoice != 3);
                break;
            case 4:
                cout << "Exit program." << endl;
                break;
            default:
                cout << "Invalid input, please enter a valid option." << endl;
                userChoice = 5;
                break;
        }
    } while (userChoice != 4);
    return 0;
}
