#include "Restaurant.h"
#include <iostream>
using namespace std;

Restaurant::Restaurant(string n,string co, string adr):name(n),cuisine(co),address(adr) {
  		stringstream ss;
        ss<<"R-"<<setfill('0')<<setw(4)<<count++; //total of 4 digits (including the number from count)...  i guess
        restaurantId=ss.str(); //turn it into a string like "R-0001"
        cout<<"Restaurant: "<<name<<"has been added, your restaurant ID: "<<restaurantId<<endl;
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
