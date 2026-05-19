#include "CashPayment.h"
#include<iostream>
using namespace std;

CashPayment::CashPayment() : Payment() { //Default constructor: initializes cash payment with default values
    //inherits from Payment, no additional initialization needed
}

CashPayment::CashPayment(string id, double amount) : Payment(id, amount) { //Parameterized constructor: initializes with id and amount
    //inherits from Payment and initializes with id and amount
}

CashPayment::~CashPayment() { //Destructor: cleans up cash payment when object is deleted
    //no memory to clean up
}

bool CashPayment::validatePayment() { //Method: validation for method (does nothing so it always retuns true)
    //cash payment needs no validation
    return true; //always valid
}

bool CashPayment::processPayment() { //Method: process cash payment (creates order, status stays pending)
    cout << "\n========== CASH PAYMENT ==========\n"; //print header
    
    // Step 1: Validate payment
    if (!validatePayment()) {
        cout << "✗ Validation failed!\n"; //print error
        setStatus("Failed"); //set status to Failed
        return false; //payment failed
    }
    
    // Step 2: Status stays "Pending" (driver will confirm later)
    cout << "✓ Order created!\n"; //print success
    cout << "Amount: OMR" << getAmount() << "\n"; //print amount
    cout << "Status: " << getStatus() << " (waiting for driver confirmation)\n"; //print status
    cout << "\nNote: Driver will confirm payment when order is delivered.\n"; //print note
    
    // Step 3: Print receipt
    cout << "\n========== PAYMENT RECEIPT ==========\n"; //print receipt header
    cout << "Payment ID: " << getPaymentID() << "\n"; //print payment ID
    cout << "Payment Type: " << getPaymentType() << "\n"; //print payment type
    cout << "Amount: OMR" << getAmount() << "\n"; //print amount
    cout << "Status: " << getStatus() << "\n"; //print status
    cout << "====================================\n"; //print receipt footer
    
    cout << "\n✓ CASH PAYMENT ORDER CREATED!\n"; //print final message
    return true; //payment succeeded
}

//method: returns payment type
string CashPayment::getPaymentType() {
    return "Cash"; //return payment type
}