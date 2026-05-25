#include <vector>
#include <string>
#include <iostream>
using namespace std;


// Menu class (will compose of Restaurant)
class Menu {
    vector<string> itemNames; //vector of the item name
    vector<double> itemPrices; //vector of the item price
public:
    Menu(); //we start with an empty menu

    void addItem(string n, double p);

    void display(); //reads only (we use const here)

    string getItemName(int ch) const;

    double getItemPrice(int ch) const;

    bool isItemValid(int ch) const;

    void addItemName();

    void addItemPrice();

    // for editing existing item
    void updateItemName(int ch);

    void updateItemPrice(int ch);

    void removeItem(int ch);
};
