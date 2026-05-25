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

void Menu::addItemName() {
    string name;
    cout << "Enter item name: ";
    cin >> name;
    itemNames.push_back(name);
}

void Menu::addItemPrice() {
    double price;
    cout << "Enter item price: ";
    cin >> price;
    itemPrices.push_back(price);
}
void Menu::updateItemName(int ch) {
    if (isItemValid(ch)) {
        string name;

        cout << "Enter new item name: ";
        cin >> name;

        itemNames[ch - 1] = name;
    }
    else {
        cout << "Invalid item number." << endl;
    }
}
void Menu::updateItemPrice(int ch) {
    if (isItemValid(ch)) {
        double price;

        cout << "Enter new item price: ";
        cin >> price;

        itemPrices[ch - 1] = price;
    }
    else {
        cout << "Invalid item number." << endl;
    }
}

// Exception handling: prevents invalid menu removal,
// such as removing a non-existing item or removing the last remaining item
void Menu::removeItem(int ch) {
    try {
        if (itemNames.size() == 1) {
            throw "You can only update this item. The menu must have at least one item.";
        }
        if (!isItemValid(ch)) {
            throw "Invalid item number.";
        }
        //Remove the item at position ch - 1
        itemNames.erase(itemNames.begin() + ch - 1);
        itemPrices.erase(itemPrices.begin() + ch - 1);
        cout << "Item removed successfully." << endl;
    }
    catch (const char *msg) {
        cout << msg << endl;
    }
}
