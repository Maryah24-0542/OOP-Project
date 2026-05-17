#include "Payment.h"
#include<iostream>
using namespace std;

Payment::Payment() { //Defult constructor (initializes private members with default values)
  paymentID = ""; //Empty payment ID
  amount = 0.0; //no amount yet
  status = "Pending"; //payment starts off as pending
  paymentDate = ""; //empty payment date
}

Payment::Payment(string id, double amount) { //parameterized constructor (initializes members with provided values)
  paymentID = id; //sets payment ID
  amount = amount; //sets payment amount
  status = "Pending";
  paymentDate = ""; //date will be set later
}


Payment::~Payment() { //visrtual destructor (cleans up its own mess) to clean up derived classes, in our case, we dont have any special cleanup needed
}

void Payment::setAmount(double amount) { //setter: updates the payment method
  amount = amount; //sets the amount
}

void Payment::setPaymentID(string id) { //setter: sets the payment ID
  paymentID = id; //sets the ID
}

void Payment::setStatus(string status){ //setter: updates the payment status: Pending, Completed, Failed
  status = status; //sets the status
}

void Payment::setPaymentDate(string date) { //setter: sets payment date
  paymentDate = date; //sets the date 
}

double Payment::getAmount() { //getter: returns payment amount
  return amount; //returns amount
}

string Payment::getPaymentID(){ //getter: returns payment ID
  return paymentID; //returns payment ID
}

string Payment::getStatus(){ //getter: returns payment status
  return status; //return status
}

string Payment::getPaymentDate() { //getter: returns the payment date
  return paymentDate; //returns date
}
