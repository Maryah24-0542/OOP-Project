#ifndef CASHPAYMENT_H
#define CASHPAYMENT_H

#include "Payment.h"
#include<iostream>
#include<string>
using namespace std;

class CashPayment : public Payment {
    //cash payment inherits from payment
    //no additional data members needed for cash payment
public:
    CashPayment(); //default constructor: initializes cash payment with input values
    ~CashPayment() override; //destructor: cleans up cash payment when object is deleted

    bool processPayment() override;

    //override: processes cash payment (creates order, status stays pending until driver confirms)
    string getPaymentType() override; //override: returns Cash
};

#endif //CASHPAYMENT_H
