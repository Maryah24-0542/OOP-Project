#include "Restaurant.h"
#include <iostream>
using namespace std;

Restaurant::Restaurant(int id, string n):restaurantId(id),name(n) {}
void Restaurant::addToMenu(string itemName, double price){
  menu.addItem(itemName, price);
  }
void Restaurant::display() const{
        cout<<"======================================="<<endl;
        cout<<"Restaurant : "<<name<<endl;
        cout<<"Menu: "<<endl;
        menu.display();
        cout<<"======================================="<<endl;
}
