#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
using namespace std;

class Customer {
    static int count;
    int phoneNumber;
    string name, email, address, customerID;

public:
    // constructor
    Customer();
// setters
    void setPhone();

    void setName();

    void setEmail();

    void setAddress();
// getters
    int getPhone();

    string getName();

    string getEmail();

    string getAddress();

    string getCustomerID();
// display method
    void display();

};
#endif //CUSTOMER_H
