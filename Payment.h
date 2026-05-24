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

    void setAmount(double total); //setter, updates the payment amount
    void setPaymentID(); //setter, sets the payment ID
    void setStatus(string status); //updates payment status

    double getAmount(); //getter, returns the payment amount
    string getPaymentID(); //getter, returns the payment ID
    string getStatus(); //getter, returns the payment status

    virtual void paymentReciept() = 0; //subclasses must override to process the payment
    virtual string getPaymentType() = 0; //subclasses must override to return Card or Cash payment
};
#endif //PAYMENT_H
