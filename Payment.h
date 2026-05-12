#ifndef UNTITLED_PAYMENT_H
#define UNTITLED_PAYMENT_H

#endif //UNTITLED_PAYMENT_H

#include<iostream>
#include<string>
using namespace std;

class Driver; //we will define later

class Payment {
private:
  string paymentID;
  double amount; //stores the payment amount (double so that it can store decimal numbers)
  string status; //stores payment status (pending,completed or failed)
  string paymentDate; //stores the date the payment was made

public:
  Payment(); //default constructor
  Payment(string id, double amount); //constructor, initializes with amount and ID
  virtual ~Payment(); //virtual destructor
  void setAmount(double amount); //setter, updates the payment amount
  void setPaymentID(string id); //setter, sets the payment ID
  void setStatus(string status); //updates payment status
  void setPaymentDate(string date); //setter, sets the payment date
  double getAmount(); //getter, returns the payment amount
  string getPaymentID(); //getter, returns the payment ID
  string getStatus(); //getter, returns the payment status
  string getPaymentDate(); //getter, returns the payment date
  virtual bool validatePayment() = 0; //subclasses must override to check if payment information is valid
  virtual bool processPayment() = 0; //subclasses must override to process the payment
  virtual string getPaymentType() = 0; //subclasses must override to return Card or Cash payment
};
#endif 
