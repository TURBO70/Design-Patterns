#include <iostream>
using namespace std;

// Strategy interface
class PaymentStrategy {
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() {}
};

// Concrete strategies
class CreditCardStrategy : public PaymentStrategy {
private:
    string name;
    string cardNumber;
    string cvv;
    string dateOfExpiry;
    
public:
    CreditCardStrategy(const string& name, const string& cardNumber, 
                      const string& cvv, const string& dateOfExpiry) 
        : name(name), cardNumber(cardNumber), cvv(cvv), dateOfExpiry(dateOfExpiry) {}
    
    void pay(int amount) override {
        cout << amount << " paid with credit card" << endl;
    }
};

class PayPalStrategy : public PaymentStrategy {
private:
    string emailId;
    string password;
    
public:
    PayPalStrategy(const string& emailId, const string& password) 
        : emailId(emailId), password(password) {}
    
    void pay(int amount) override {
        cout << amount << " paid using PayPal" << endl;
    }
};

// Context
class ShoppingCart {
private:
    PaymentStrategy* paymentStrategy;
    
public:
    ShoppingCart() : paymentStrategy(nullptr) {}
    
    ~ShoppingCart() {
        delete paymentStrategy;
    }
    
    void setPaymentStrategy(PaymentStrategy* strategy) {
        delete paymentStrategy;
        paymentStrategy = strategy;
    }
    
    void checkout(int amount) {
        if (paymentStrategy) {
            paymentStrategy->pay(amount);
        } else {
            cout << "No payment method selected" << endl;
        }
    }
};

int main() {
    ShoppingCart* cart = new ShoppingCart();
    
    cout << "Enter payment method (1 for Credit Card, 2 for PayPal): ";
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        cart->setPaymentStrategy(new CreditCardStrategy("John Doe", "1234567890123456", "786", "12/2025"));
    } else if (choice == 2) {
        cart->setPaymentStrategy(new PayPalStrategy("john@example.com", "password"));
    }
    
    cart->checkout(100);
    
    delete cart;
    
    return 0;
}