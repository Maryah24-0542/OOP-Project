#include "CardPayment.h"
#include<iostream>
using namespace std;

CardPayment::CardPayment() : Payment() { //defult constructor: initializes card payment members with default values
    cardholderName = ""; //empty cardholder name
    cardLastFour = ""; //empty last 4 digits
    expiryDate = ""; //empty expiry date
    cardType = ""; //empty card type
}

CardPayment::CardPayment(string id, double amount, string name, string cardNum, string expiry) //parameterized constructor: initializes card payment with provided card details
    : Payment(id, amount) {
    cardholderName = name; //set cardholder name
    expiryDate = expiry; //set expiry date
    cardType = "Visa"; //default card type to visa
    maskCardNumber(cardNum); //extract and store only last 4 digits
}

CardPayment::~CardPayment() { //destructor: cleans up card payment when object is deleted
    //no memory to clean up
}

void CardPayment::setCardholderName(string name) { //setter: sets card holder name
    cardholderName = name; //set the name
}

void CardPayment::setCardNumber(string cardNum) { //setter: sets card number but extracts the last 4 digits
    maskCardNumber(cardNum); //extract last 4 digits of the card number
}

void CardPayment::setExpiryDate(string expiry) { //setter:  sets expiry date
    expiryDate = expiry; //set the expiry date
}

void CardPayment::setCardType(string type) { //setter: sets card type
    cardType = type; //set the card type 
}

string CardPayment::getCardholderName() { //getter: returns cardholder name
    return cardholderName; //returns the cardholder name
}

string CardPayment::getCardLastFour() { //getter: returns the last 4 digits of the card
    return cardLastFour; //return last 4 digits of the card
}

string CardPayment::getExpiryDate() { //getter: returns expiry date
    return expiryDate; //returns the expiry date
}

string CardPayment::getCardType() { //getter: returns the card type
    return cardType; //returns the card type
}

void CardPayment::maskCardNumber(string fullCard) { //Method: extracts and stores only the last 4 digits of the card (security purposes)
    string cleaned = ""; //create empty string to store cleaned card number
    
    for (int i = 0; i < fullCard.length(); i++) { //loop through each character in full card
        if (fullCard[i] != ' ') {// If character is not a space, add it to cleaned string
            cleaned += fullCard[i]; //add character to cleaned string
        }
    }
    
    if (cleaned.length() >= 4) {// Extract only last 4 digits of the card number
        cardLastFour = cleaned.substr(cleaned.length() - 4); //Get substring starting from (length - 4) to the end and store last 4 digits
    } else {
        cardLastFour = cleaned; //If card number is too short, store what we have
    }
}
bool CardPayment::validatePayment() { //method: checks if the card details are valid
    cout << "\nValidating card details...\n"; //print validation message
    
    // Check 1: Amount must be positive
    if (getAmount() <= 0) {
        cout << "Invalid amount!\n"; //print error
        return false; //validation failed
    }
    
    // Check 2: Card number must exist and have at least 4 digits
    if (cardLastFour.empty()) {
        cout << "No card number provided!\n"; //print error
        return false; //validation failed
    }
    
    if (cardLastFour.length() < 4) {
        cout << "Card number too short!\n"; //print error
        return false; //validation failed
    }
    
    // Check 3: Cardholder name must exist
    if (cardholderName.empty()) {
        cout << "No cardholder name provided!\n"; //print error
        return false; //validation failed
    }
    
    // Check 4: Expiry date must exist and be valid format MM/YY
    if (expiryDate.empty()) {
        cout << "No expiry date provided!\n"; //print error
        return false; //validation failed
    }
    
    // Check if expiry date is in MM/YY format (5 characters with / in middle)
    if (expiryDate.length() != 5 || expiryDate[2] != '/') {
        cout << "Expiry date must be in MM/YY format!\n"; //print error
        return false; //validation failed
    }
    
    cout << "✓ Card validation passed!\n"; //print success message
    return true; //all checks passed
}
bool CardPayment::processPayment() { //method: process the payment (creates the order if valid)
    cout << "\n========== CARD PAYMENT ==========\n"; //print header
    
    // Step 1: Validate card details
    if (!validatePayment()) {
        cout << "✗ Card validation failed!\n"; //print error
        setStatus("Failed"); //set status to Failed
        return false; //payment failed
    }
    
    // Step 2: Update payment status to Completed
    setStatus("Completed"); //payment is complete
    cout << "✓ Payment accepted!\n"; //print success
    
    // Step 3: Print receipt
    cout << "\n========== PAYMENT RECEIPT ==========\n"; //print receipt header
    cout << "Payment ID: " << getPaymentID() << "\n"; //print payment ID
    cout << "Card Type: " << cardType << "\n"; //print card type
    cout << "Card Number: ****" << cardLastFour << "\n"; //print masked card number
    cout << "Cardholder: " << cardholderName << "\n"; //print cardholder name
    cout << "Expiry Date: " << expiryDate << "\n"; //print expiry date
    cout << "Amount Charged: OMR" << getAmount() << "\n"; //print amount
    cout << "Status: " << getStatus() << "\n"; //print status
    cout << "====================================\n"; //print receipt footer
    
    cout << "\n✓ CARD PAYMENT SUCCESSFUL!\n"; //print final message
    return true; //payment succeeded
}

//method: returns payment type
string CardPayment::getPaymentType() {
    return "Card"; //return payment type
}
