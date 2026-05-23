#ifndef CARDPAYMENT_H
#define CARDPAYMENT_H

#include "Payment.h"
#include <iostream>
#include <string>
using namespace std;

class CardPayment : public Payment {
    //card payment inherits from payment
    string cardholderName; //name on the card
    string cardLastFour; //stores only last 4 digits of card number (for validation and security)
    string expiryDate; //expiry date in MM/YY format (for validation)
    string cardType; //type of card (Visa, MasterCard, Amex)

public:
    CardPayment(); //default constructor, initializes card info with input values
    ~CardPayment() override; //destructor: to clean up card payment when object is deleted
    //setters
    void setCardholderName();

    void setCardLastFour();

    void setExpiryDate();

    void setCardType();

    //getters
    string getCardholderName();

    string getCardLastFour();

    string getExpiryDate();

    string getCardType();

    //methods
    void validateCardNumber(string cardNum); //checks if card number is valid
    void validateExpiryDate(string expiry); //checks if card expiry date is valid

    bool processPayment() override; //override: processes the payment
    string getPaymentType() override; //override: returns "Card"
};

#endif //CARDPAYMENT_H
