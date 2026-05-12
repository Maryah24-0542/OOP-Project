#include "Restaurant.h"
#include <iostream>
using namespace std;


int Restaurant::count= 1;

Restaurant::Restaurant(string n,string co, string adr):name(n),cuisine(co),address(adr) {
  		stringstream ss;
        ss<<"R-"<<setfill('0')<<setw(4)<<count++; //total of 4 digits (including the number from count)...  i guess
        restaurantId=ss.str(); //turn it into a string like "R-0001"
        cout<<"Resturant: "<<name<<"has been added, your resturant ID: "<<restaurantId<<endl;
}

void Restaurant::addToMenu(string itemName, double price) {
  menu.addItem(itemName, price);
}
void Restaurant::display() const{
        cout<<"======================================="<<endl;
        cout<<"Restaurant : "<<name<<endl;
        cout<<"Cusinine : "<<cuisine<<endl;
        cout<<"Restaurant ID: "<<restaurantId<<endl;
        cout<<"location : "<<address<<endl;
        cout<<"Menu: "<<endl;
        menu.display();
        cout<<"======================================="<<endl;
}
string Restaurant::getName() const{return name;}
string Restaurant::getCusine() const{return cuisine;}
string Restaurant::getAddress() const{return address;}
string Restaurant::getId() const{return restaurantId;}
