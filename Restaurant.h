#include <sstream> //will use it for stringstream
#include <iomanip> //need it for setfill and setw
#include <string>
#include "Menu.h" //because Resturant HAS-A menu (we will use it)

using namespace std;

class Restaurant{
	private:
    	string restaurantId;
    	string name;
        string cuisine;
        string address;
    	Menu menu; //Restaurant has-a Menu
        static int count;

	public:
    	Restaurant(string n, string co, string adr);
    	void addToMenu(string itemName,double price);
    	void display() const;

};
