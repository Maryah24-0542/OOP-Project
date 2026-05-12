#include <vector>
#include <string>
#include <iostream>
using namespace std;

bool   hasItem(string name) const;
double getItemPrice(string name) const;


// Menu class (gonna compose from Resturant)
class Menu{
    private:
        vector<string> itemNames; //vector of the item name
        vector<double> itemPrices;//vector of the item price
    public:
        Menu(); //we start with an empty menu
        void addItem(string n, double p);
    	void display() const; //reads only (we use const here)
};
