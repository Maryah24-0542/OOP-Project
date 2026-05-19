#ifndef UNTITLED_CASHPAYMENT_H
#define UNTITLED_CASHPAYMENT_H

#endif //UNTITLED_CASHPAYMENT_H

#include "Payment.h"
#include<iostream>
#include<string>
using namespace std;

class CashPayment : public Payment { //cash payment inherits from payment
private:
    //no additional data members needed for cash payment

public:
    CashPayment(); //default constructor: initializes cash payment with default values
    CashPayment(string id, double amount); //parameterized constructor: initializes with id and amount
    ~CashPayment(); //destructor: cleans up cash payment when object is deleted

    bool validatePayment() override; //override: does nothing for cash, always returns true
    bool processPayment() override; //override: processes cash payment (creates order, status stays pending until driver confirms)
    string getPaymentType() override; //override: returns Cash
};

#endif