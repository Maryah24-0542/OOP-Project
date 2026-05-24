#include "CardPayment.h"
#include <iostream>
using namespace std;

CardPayment::CardPayment() {
    setCardholderName();
    setCardLastFour();
    setExpiryDate();
    setCardType();
}

CardPayment::~CardPayment() {
}

//method: returns payment type
string CardPayment::getPaymentType() {
    return "Card"; //return payment type
}

void CardPayment::setCardholderName() {
    cout << "Enter card holder name:";
    cin >> cardholderName;
}

void CardPayment::setCardLastFour() {
    string cardNum;
    cout << "Enter valid card number: ";
    cin >> cardNum;
    validateCardNumber(cardNum);
}

void CardPayment::setExpiryDate() {
    string expiry;
    cout << "Enter valid card number: ";
    cin >> expiry;
    validateExpiryDate(expiry);
}

void CardPayment::setCardType() {
    cout << "Enter card type (Visa, MasterCard, Amex):";
    cin >> cardType;
}

string CardPayment::getCardholderName() {
    return cardholderName;
}

string CardPayment::getCardLastFour() {
    return cardLastFour;
}

string CardPayment::getExpiryDate() {
    //getter: returns expiry date
    return expiryDate; //returns the expiry date
}

string CardPayment::getCardType() {
    //getter: returns the card type
    return cardType; //returns the card type
}

void CardPayment::validateCardNumber(string cardNum) {
    //method: checks card number: length must be 19 (16 digits + 3 spaces at indexes 4, 9, 14)
    if (cardNum.length() != 19) {
        cout << "Invalid card number. It must be 19 characters.\n";
        cout << "Format: 1234 5678 9012 3456\n";
        return setCardLastFour();
    }

    if (cardNum[4] != ' ' || cardNum[9] != ' ' || cardNum[14] != ' ') {
        cout << "Invalid card number. There must be a space after every 4 digits.\n";
        return setCardLastFour();
    }

    for (int i = 0; i < cardNum.length(); i++) {
        if (i == 4 || i == 9 || i == 14) {
            continue;
        }
        if (!isdigit(cardNum[i])) {
            cout << "Invalid card number. Only digits are allowed.\n";
            return setCardLastFour();
        }
    }
    cardLastFour = cardNum.substr(15, 4);
}

void CardPayment::validateExpiryDate(string expiry) {
    // method: checks expiry date: must be valid format MM/YY (length 5, 4 digits with '/' after first two)
    if (expiry.length() != 5 || expiry[2] != '/') {
        cout << "Expiry date must be in MM/YY format!\n"; //print error message
        return setExpiryDate();
    }
    if (!isdigit(expiry[0]) || !isdigit(expiry[1]) ||
        !isdigit(expiry[3]) || !isdigit(expiry[4])) {
        cout << "Invalid expiry date. Month and year must be digits.\n";
        return setExpiryDate();
    }
    int month = stoi(expiry.substr(0, 2));
    int year = stoi(expiry.substr(3, 2));

    if (month < 1 || month > 12) {
        cout << "Invalid month. Month must be between 01 and 12.\n";
        return setExpiryDate();
    }

    if (year < 2026 || (year == 2026 && month < 5)) {
        cout << "Card is expired.\n";
        return setExpiryDate();
    }
    expiryDate = expiry;
}

void CardPayment::paymentReciept() {
    //method: print receipt
    cout << "========== CARD PAYMENT ==========\n"; //print header
    cout << "Payment accepted!\n";
    cout << "========== PAYMENT RECEIPT ==========\n"; //print receipt header
    cout << "Payment ID: " << getPaymentID() << "\n"; //print payment ID
    cout << "Card Type: " << cardType << "\n"; //print card type
    cout << "Card Number: **** **** **** " << cardLastFour << "\n"; //print masked card number
    cout << "Cardholder: " << cardholderName << "\n"; //print cardholder name
    cout << "Expiry Date: " << expiryDate << "\n"; //print expiry date
    cout << "Amount Charged: " << getAmount() << " OMR\n"; //print amount
    cout << "Payment Status: " << getStatus() << "\n"; //print status
    cout << "=====================================\n"; //print receipt footer
}
