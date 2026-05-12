# include "customer.h"
# include<iostream>
using namespace std;


Customer::Customer() {}

Customer::Customer( int phone, string name,string email,string address) {
    PhoneNumber=phone;
    Name=name;
    Email=email;
    Address=address;
    CustomerID=++NextID;
}
int Customer::NextID=0;

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

int Customer::getCustomerID() {
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


}
