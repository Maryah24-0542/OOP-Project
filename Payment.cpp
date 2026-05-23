#include "Payment.h"
#include <bits/stdc++.h>
using namespace std;


Payment::Payment() {
    setPaymentID(); //sets payment ID
    amount = 0.0; //sets payment amount
    status = "Pending";
}

Payment::~Payment() {
    //virtual destructor (cleans up its own mess) to clean up derived classes, in our case, we dont have any special cleanup needed
}

void Payment::setAmount(double total) {
    amount = total;
}

void Payment::setPaymentID() {
    // create string stream to format the ID
    stringstream ss;
    // format ID as P-0001, P-0002, etc.
    ss << "P-" << setfill('0') << setw(4) << count++;
    // return the formatted string
    paymentID = ss.str();
}

void Payment::setStatus(string s) {
    //setter: updates the payment status: Pending, Completed
    status = s; //sets the status
}

double Payment::getAmount() {
    //getter: returns payment amount
    return amount; //returns amount
}

string Payment::getPaymentID() {
    //getter: returns payment ID
    return paymentID; //returns payment ID
}

string Payment::getStatus() {
    //getter: returns payment status
    return status; //return status
}
