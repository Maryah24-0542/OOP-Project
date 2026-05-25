#include "Customer.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

int Customer::count = 1;

Customer::Customer() {
    setName();
    setPhone();
    setEmail();
    setAddress();
    stringstream ss;
    ss << "C-" << setfill('0') << setw(4) << count++; //total of 4 digits (including the number from count)
    customerID = ss.str(); //turns it into a string like "C-0001"
    cout << "Customer: " << name << " has been added, your ID: " << customerID << endl;
}

void Customer::setName() {
    cout << "Enter your name: ";
    cin >> name;
}

string Customer::getName() {
    return name;
}

void Customer::setPhone() {
    cout << "Enter your phone number: ";
    cin >> phoneNumber;
}

int Customer::getPhone() {
    return phoneNumber;
}

void Customer::setEmail() {
    cout << "Enter your email address: ";
    cin >> email;
}

string Customer::getEmail() {
    return email;
}

void Customer::setAddress() {
    cout << "Enter delivery address: ";
    cin >> address;
}

string Customer::getAddress() {
    return address;
}

string Customer::getCustomerID() {
    return customerID;
}

void Customer::display() {
    cout << "=== Customer Information ===\n";
    cout << "Customer ID: " << getCustomerID() << "\n";
    cout << "Name: " << getName() << "\n";
    cout << "Phone number: " << getPhone() << "\n";
    cout << "Email: " << getEmail() << "\n";
    cout << "Address: " << getAddress() << "\n";
    cout << "============================\n";

}
