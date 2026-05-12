# include "customer.h"
# include<iostream>
# include<iomanip>
#include <sstream>
using namespace std;


Customer::Customer() {}

Customer::Customer( int phone, string name,string email,string address) {
    PhoneNumber=phone;
    Name=name;
    Email=email;
    Address=address;
    stringstream ss;
    ss<<"C-"<<setfill('0')<<setw(4)<<countID; //total of 4 digits (including the number from count)...  i guess
   CustomerID=ss.str(); //turn it into a string like "C-0001"
    countID++;
}
int Customer::NextID=1;

void Customer::setName() {
    cout<<"Welcome , Please enter the following information !"<<endl;
    cout<<"Enter your name: ";
    cin>>Name;
    cout<<endl;

}

string Customer::getName() {
    return Name;
}

void Customer::setPhone() {
    cout<<"Enter your phone number: ";
    cin>>PhoneNumber;
    cout<<endl;

}

int Customer::getPhone() {
    return PhoneNumber;
}




void Customer::setEmail() {
    cout<<"Enter your Email address: ";
    cin>>Email;
    cout<<endl;
}
string Customer::getEmail() {
    return Email;
}

void Customer::setAddress() {
    cout<<"Enter your Address: ";
    cin>>Address;
    cout<<endl;

}

string Customer::getAddress() {
    return Address;
}

string Customer::getCustomerID() {
    return CustomerID;
}



void Customer::Display() {
    cout<<"----------------------------------------\n";
    cout<<"----------Customer Information----------\n";
    cout<<"----------------------------------------\n";
    cout<<endl;
    cout<<"Name -> "<<getName()<<"\n";
    cout<<"Phone number -> "<<getPhone()<<"\n";
    cout<<"Email -> "<<getEmail()<<"\n";
    cout<<"Address -> "<<getAddress()<<"\n";
    cout<<"Customer ID -> "<<getCustomerID()<<"\n";


}
