#ifndef CUSTOMER_H
#define CUSTOMER_H
#endif CUSTOMER_H

# include<iostream>
#include <sstream>
using namespace std;

class Customer {
private:
    static int countID;
    int PhoneNumber;
    string Name,Email,Address,CustomerID;

public:
    Customer();
    Customer( int phone, string name,string email,string address);
    void setPhone();
    void setName();
    void setEmail();
    void setAddress();
    int getPhone();
    string getName();
    string getEmail();
    string getAddress();
    string getCustomerID();
    void Display();

};
