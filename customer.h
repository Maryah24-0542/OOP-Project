#ifndef UNTITLED_CUSTOMER_H
#define UNTITLED_CUSTOMER_H
#endif //UNTITLED_CUSTOMER_H

# include<iostream>
#include <vector>
using namespace std;

class Order;
class Customer {
private:
    static int NextID;
    int PhoneNumber;
    string Name,Email,Address,CustomerID;
    vector<Order*> orderHistory;
public:
    Customer();
    Customer( int phone, string name,string email,string address);
    void PLaceOrder(Order* order);
    void setPhone();
    void setName();
    void setEmail();
    void setAddress();
    int getPhone();
    string getName();
    string getEmail();
    string getAddress();
    int getCustomerID();
    vector<Order*> getOrderHistory();
    void Display();

};
