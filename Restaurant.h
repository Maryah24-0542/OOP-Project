#include <sstream> //will use it for stringstream
#include <iomanip> //need it for setfill and setw
#include <string>
#include "Menu.h" //bc Resturant HAS-A menu (we will use it)

using namespace std;

class Restaurant{
	private:
    	int restaurantId;
    	string name;
    	Menu menu;  //Restaurant has-a Menu
	public:
    	Restaurant(int id, string n);
    	void addToMenu(string itemName,double price);
    	void display() const;
};
