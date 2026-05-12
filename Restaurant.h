#include <sstream> //will use it for stringstream
#include <iomanip> //need it for setfill and setw
#include <string>
#include "Menu.h" //because Resturant HAS-A menu (we will use it)

using namespace std;

class Restaurant{
	private:
    	string restaurantId; //the output gonna be like "R-0001"
    	string name;
        string cuisine;
        string address;
    	Menu menu; //Restaurant has-a Menu (compsition)
        static int count;

	public:
    	Restaurant(string n, string co, string adr);
    	void addToMenu(string itemName,double price);
    	void display() const;
        string getName() const;
        string getCusine() const;
        string getAddress() const;
        string getId() const;
};
