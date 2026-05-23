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
    vector<Driver *> drivers; //bc abstract
    vector<Restaurant> restaurants;

public:
    Company();

    ~Company();

    //Customer Methods
    Customer *newCustomer();

    Customer *customerLogin();

    Order *newOrder(Customer *customer);

    Driver *assignDriver(Order *order);

    void checkout(Order *order);

    void viewCurrentOrder(Order *order);

    void viewCustomerInfo(Customer *customer);

    //Driver Methods
    Driver *newBikeDriver();

    Driver *newCarDriver();

    Driver *driverLogin();

    //Restaurant Methods
    Restaurant *newRestaurant();

    Restaurant *restaurantLogin();

    void displayRestaurants() const;
};
#endif //COMPANY_H
