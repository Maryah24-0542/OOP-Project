#include "Menu.h"
#include <iostream>
using namespace std;

Menu::Menu(){}
void Menu::addItem(string n, double p){
        itemNames.push_back(n);//adds the name  to the end of the names list (the point of using push_back)
        itemPrices.push_back(p); //adds the pricr to the end of the prices list
        
}
 
    
      double Menu::getItemPrice(string name) const {
        for (int i = 0; i < itemNames.size(); i++)
             if (itemNames[i] == name) return itemPrices[i];
        return -1;
      }
void Menu::display() const{
    for(int i=0;i<itemNames.size(); i++) //from the first to the last element in the name vector (the menu)
        cout<<" - "<< itemNames[i]<<" : "<<itemPrices[i]<<" OMR"<<endl;
}
