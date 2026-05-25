#ifndef COMPANY_H
#define COMPANY_H
#include <bits/stdc++.h>
#include "Customer.h"
#include "Restaurant.h"
#include "Order.h"
#include "Driver.h"
#include "BikeDriver.h"
#include "CarDriver.h"
#include "CashPayment.h"
#include "CardPayment.h"

using namespace std;

class Company {
    vector<Customer> customers;
    vector<Driver *> drivers; //because it's an abstract class
    vector<Restaurant> restaurants;

public:
    Company(); // Default constructor for Company

    ~Company(); // Destructor: deletes dynamically allocated driver objects to prevent memory leaks

    //Customer Methods
    // Registers a new customer, stores them in the customers vector, and returns a pointer to the saved customer object
    Customer *newCustomer();

    // Allows an existing customer to log in using their customer ID. If no customers exist, it redirects the user to register first
    Customer *customerLogin();

    // Allows a customer to create a new order by choosing a restaurant, adding menu items to the cart, then either cancelling or proceeding to checkout
    Order *newOrder(Customer *customer);

    // Assigns an available driver to the order. Bike drivers are preferred for same-area delivery, while car drivers are preferred for different-area delivery
    Driver *assignDriver(Order *order);

    // Handles the checkout process: assigns a driver, calculates delivery fee and total price, creates payment, prints receipt, and changes order status to Preparing
    void checkout(Order *order);

    // Displays the current customer order. If the order is still in cart, the customer can checkout or cancel. If the order is preparing, the customer can still cancel it
    void viewMyOrder(Order *&order);

    // Displays customer information and allows the customer to update personal details such as name, phone number, email, or address
    void viewCustomerInfo(Customer *customer);

    // Displays all registered restaurants so the customer can choose one
    void displayRestaurants() const;

    //Driver Methods
    // Registers a new bike driver dynamically and stores the driver pointer
    Driver *newBikeDriver();

    // Registers a new car driver dynamically and stores the driver pointer
    Driver *newCarDriver();

    // Allows an existing driver to log in using their driver ID. Returns nullptr if there are no registered drivers
    Driver *driverLogin();

    // Displays the driver's currently assigned order, if they have one
    void viewDriverOrder(Driver *driver);

    // Allows the driver to update the assigned order status. The driver can move the order from Ready for Pickup to On The Way, then from On The Way to Delivered
    void driverUpdateOrder(Driver *driver);

    // Displays driver information and allows the driver to update common details and type-specific details using dynamic_cast
    void viewDriverInfo(Driver *driver);

    //Restaurant Methods
    // Registers a new restaurant, stores it in the restaurants vector, and allows the restaurant to add extra menu items after registration
    Restaurant *newRestaurant();

    // Allows an existing restaurant to log in using its restaurant ID. If no restaurants exist, it redirects the user to register first
    Restaurant *restaurantLogin();

    // Displays restaurant information and allows the restaurant to update name, cuisine, address, preparation time, and extra time per item
    void viewRestaurantInfo(Restaurant *restaurant);

    // Displays the restaurant menu and allows the restaurant to add, edit, or remove menu items
    void viewRestaurantMenu(Restaurant *restaurant);

    // Displays the restaurant's assigned orders. If the restaurant chooses to update an order, the order status changes from Preparing to Ready for Pickup.
    void viewRestaurantOrders(Restaurant *restaurant);
};
#endif //COMPANY_H
