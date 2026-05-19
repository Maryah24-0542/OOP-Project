#include <vector>
#include <string>
#include <iostream>
using namespace std;




// Menu class (gonna compose from Resturant)
class Menu{
    private:
        vector<string> itemNames; //vector of the item name
        vector<double> itemPrices;//vector of the item price
    public:
        Menu(); //we start with an empty menu
        void addItem(string n, double p);
    	void display() const; //reads only (we use const here)
		string getItemName(int ch) const;
		double getItemPrice(int ch) const;
		bool isItemValid(int ch) const;
		//setters- in case we wanna update the item
		void setItemName(int ch, string nwName);
		void setItemPrice(int ch, double nwprice);
};
