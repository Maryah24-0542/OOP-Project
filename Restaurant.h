#ifndef RESTAURANT_H
#define RESTAURANT_H
#include <iomanip> //need it for setfill and setw
#include <string>
#include "Menu.h" //because Resturant HAS-A menu (we will use it)

using namespace std;

class Restaurant {
    string restaurantId; //the output will be like "R-0001"
    string name;
    string cuisine;
    string address;
    double basePrepTime;
    double extraTimePerItem;
    Menu menu; //Restaurant has-a Menu (composition)
    static int count;


public:
    Restaurant();

    void addToMenu(string itemName, double price);

    double calcPrepTime(int itemCount);

    void display();

    //getters
    string getName() const;

    string getCuisine() const;

    string getAddress() const;

    string getId() const;

    Menu &getMenu();

    double getBasePrepTime() const;

    double getExtraTimePerItem() const;

    //setters
    void setName();

    void setCuisine();

    void setAddress();

    void setBasePrepTime();

    void setExtraTimePerItem();
};
#endif //RESTAURANT_H
