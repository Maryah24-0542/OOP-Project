#include "CashPayment.h"
#include <iostream>
using namespace std;

CashPayment::CashPayment() {
    //inherits from Payment, no additional initialization needed
}

CashPayment::~CashPayment() {
}

string CashPayment::getPaymentType() {
    return "Cash";
}

void CashPayment::paymentReciept() {
    //method: print receipt
    //Status stays "Pending" (driver will confirm later)
    cout << "Note: Driver will confirm payment when order is delivered.\n"; //print note
    cout << "========== PAYMENT RECEIPT ==========\n"; //print receipt header
    cout << "Payment ID: " << getPaymentID() << "\n"; //print payment ID
    cout << "Payment Type: " << getPaymentType() << "\n"; //print payment type
    cout << "Amount: " << getAmount() << " OMR\n"; //print amount
    cout << "Payment Status: " << getStatus() << " (waiting for driver confirmation)\n"; //print status
    cout << "=====================================\n"; //print receipt footer
}
