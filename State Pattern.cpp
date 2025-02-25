#include <iostream>
#include <string>
using namespace std;

class VendingMachine;

class State {
public:
    virtual void insertCoin(VendingMachine* machine) = 0;
    virtual void selectProduct(VendingMachine* machine) = 0;
    virtual void dispense(VendingMachine* machine) = 0;
    virtual string getName() = 0;
    virtual ~State() {}
};

// Context
class VendingMachine {
private:
    State* noCoinState;
    State* hasCoinState;
    State* soldState;
    State* soldOutState;
    
    State* currentState;
    int count;
    
public:
    VendingMachine(int count);
    ~VendingMachine();
    
    void insertCoin() {
        currentState->insertCoin(this);
    }
    
    void selectProduct() {
        currentState->selectProduct(this);
    }
    
    void dispense() {
        currentState->dispense(this);
        count--;
    }
    
    void setState(State* state) {
        currentState = state;
    }
    
    void releaseProduct() {
        cout << "Product dispensed" << endl;
    }
    
    int getCount() {
        return count;
    }
    
    void refill(int count) {
        this->count += count;
        cout << "Vending machine refilled, new count: " << this->count << endl;
        cout << "Current state: " << currentState->getName() << endl;
    }
    
    State* getNoCoinState() { return noCoinState; }
    State* getHasCoinState() { return hasCoinState; }
    State* getSoldState() { return soldState; }
    State* getSoldOutState() { return soldOutState; }
};

// Concrete states
class NoCoinState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        cout << "Coin inserted" << endl;
        machine->setState(machine->getHasCoinState());
    }
    
    void selectProduct(VendingMachine* machine) override {
        cout << "Please insert a coin first" << endl;
    }
    
    void dispense(VendingMachine* machine) override {
        cout << "Please insert a coin first" << endl;
    }
    
    string getName() override {
        return "NoCoinState";
    }
};

class HasCoinState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        cout << "Coin already inserted" << endl;
    }
    
    void selectProduct(VendingMachine* machine) override {
        cout << "Product selected" << endl;
        machine->setState(machine->getSoldState());
    }
    
    void dispense(VendingMachine* machine) override {
        cout << "No product selected" << endl;
    }
    
    string getName() override {
        return "HasCoinState";
    }
};

class SoldState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        cout << "Please wait, dispensing product" << endl;
    }
    
    void selectProduct(VendingMachine* machine) override {
        cout << "Please wait, dispensing product" << endl;
    }
    
    void dispense(VendingMachine* machine) override {
        machine->releaseProduct();
        if (machine->getCount() > 0) {
            machine->setState(machine->getNoCoinState());
        } else {
            cout << "Out of products" << endl;
            machine->setState(machine->getSoldOutState());
        }
    }
    
    string getName() override {
        return "SoldState";
    }
};

class SoldOutState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        cout << "Machine is sold out" << endl;
    }
    
    void selectProduct(VendingMachine* machine) override {
        cout << "Machine is sold out" << endl;
    }
    
    void dispense(VendingMachine* machine) override {
        cout << "No product dispensed" << endl;
    }
    
    string getName() override {
        return "SoldOutState";
    }
};

// VendingMachine implementation
VendingMachine::VendingMachine(int count) {
    noCoinState = new NoCoinState();
    hasCoinState = new HasCoinState();
    soldState = new SoldState();
    soldOutState = new SoldOutState();
    
    this->count = count;
    if (count > 0) {
        currentState = noCoinState;
    } else {
        currentState = soldOutState;
    }
}

VendingMachine::~VendingMachine() {
    delete noCoinState;
    delete hasCoinState;
    delete soldState;
    delete soldOutState;
}

int main() {
    VendingMachine* vendingMachine = new VendingMachine(2);
    
    cout << "Vending Machine Demo" << endl;
    cout << "1. Insert Coin" << endl;
    cout << "2. Select Product" << endl;
    cout << "3. Dispense" << endl;
    cout << "4. Refill" << endl;
    cout << "5. Exit" << endl;
    
    int choice;
    do {
        cout << "Enter choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                vendingMachine->insertCoin();
                break;
            case 2:
                vendingMachine->selectProduct();
                break;
            case 3:
                vendingMachine->dispense();
                break;
            case 4:
                vendingMachine->refill(3);
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 5);
    
    delete vendingMachine;
    
    return 0;
}