#ifndef UNTITLED_CARDPAYMENT
#define UNTITLED_CARDPAYMENT_H

#endif //UNTITLED_CARDPAYMENT_H

#include "Payment.h"
#include<iostream>
#include<string>
using namespace std;

class CardPayment : public Payment { //card payment inherits from payment
private:
    string cardholderName; //name on the card
    string cardLastFour; //only last 4 digits of card (for validation)
    string expiryDate; //expiry date in MM/YY format (for validation)
    string cardType; //type of card (Visa, MasterCard, Amex)

public:
    CardPayment(); //default constructor, initilaizes cardpayment with defult values
    CardPayment(string id, double amount, string name, string cardNum, string expiry); //parameterized constructor
    ~CardPayment(); //destructor: to clean up card payment when object is deleted

    void setCardholderName(string name); //setter: sets cardholder name
    void setCardNumber(string cardNum); //setter: sets card number (extracts last 4 digits)
    void setExpiryDate(string expiry); //setter: sets expiry date
    void setCardType(string type); //setter: sets card type

    string getCardholderName(); //getter: returns cardholder name
    string getCardLastFour(); //getter: returns last 4 digits of card
    string getExpiryDate(); //getter: returns expiry date
    string getCardType(); //getter: returns card type


    void maskCardNumber(string fullCard); //helper: extracts card number but stores only last 4 digits (security)

    bool validatePayment() override; //override: checks if card details are valid
    bool processPayment() override; //override: processes the payment (creates the order if valid)
    string getPaymentType() override; //override: returns "Card"
};

#endif
