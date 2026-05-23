#include "Menu.h"
#include <iostream>
using namespace std;

Menu::Menu() {
}

void Menu::addItem(string n, double p) {
    itemNames.push_back(n); //adds the name  to the end of the names list (the point of using push_back)
    itemPrices.push_back(p); //adds the price to the end of the prices list
}

void Menu::display() {
    for (int i = 0; i < itemNames.size(); i++)
        cout << i + 1 << " - " << itemNames[i] << " : " << itemPrices[i] << " OMR" << endl;
}

string Menu::getItemName(int ch) const {
    return itemNames[ch - 1]; //vectors start from 0 not 1 thats why -1
}

double Menu::getItemPrice(int ch) const {
    return itemPrices[ch - 1];
}

bool Menu::isItemValid(int ch) const {
    return 1 <= ch && ch <= itemNames.size(); //true if the number of item exist in the menu, else false
}

void Menu::setItemName(int ch, string nwName) {
    if (isItemValid(ch))
        itemNames[ch - 1] = nwName;
    else
        cout << "Invalid Item Number" << endl;
}

void Menu::setItemPrice(int ch, double nwprice) {
    if (isItemValid(ch))
        itemPrices[ch - 1] = nwprice;
    else
        cout << "Invalid Item Number." << endl;
}
