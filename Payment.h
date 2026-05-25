#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
using namespace std;

class Payment {
    static int count;
    string paymentID;
    double amount; //stores the payment amount (double so that it can store decimal numbers)
    string status; //stores payment status (pending or completed)

public:
    Payment(); //default constructor
    virtual ~Payment(); //virtual destructor
    //setters
    void setAmount(double total);

    void setPaymentID();

    void setStatus(string status);

    //getters
    double getAmount();

    string getPaymentID();

    string getStatus();

    virtual void paymentReciept() = 0; //subclasses must override to print receipts
    virtual string getPaymentType() = 0; //subclasses must override to return Card or Cash payment
};
#endif //PAYMENT_H
