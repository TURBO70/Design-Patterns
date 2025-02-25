#include <iostream>
#include <string>
using namespace std;

class Coffee {
public:
    virtual double getCost() const = 0;
    virtual string getDescription() const = 0;
    virtual ~Coffee() {}
};

class SimpleCoffee : public Coffee {
public:
    double getCost() const override {
        return 10.0;
    }
    
    string getDescription() const override {
        return "Simple coffee";
    }
};

class CoffeeDecorator : public Coffee {
protected:
    Coffee* coffee;
    
public:
    CoffeeDecorator(Coffee* coffee) : coffee(coffee) {}
    
    ~CoffeeDecorator() {
        delete coffee;
    }
};

class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}
    
    double getCost() const override {
        return coffee->getCost() + 2.0;
    }
    
    string getDescription() const override {
        return coffee->getDescription() + ", with milk";
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}
    
    double getCost() const override {
        return coffee->getCost() + 1.0;
    }
    
    string getDescription() const override {
        return coffee->getDescription() + ", with sugar";
    }
};

int main() {
    // Create a simple coffee
    Coffee* myCoffee = new SimpleCoffee();
    cout << "Cost: $" << myCoffee->getCost() << ", Description: " << myCoffee->getDescription() << endl;
    
    // Add milk to the coffee
    myCoffee = new MilkDecorator(myCoffee);
    cout << "Cost: $" << myCoffee->getCost() << ", Description: " << myCoffee->getDescription() << endl;
    
    // Add sugar to the coffee with milk
    myCoffee = new SugarDecorator(myCoffee);
    cout << "Cost: $" << myCoffee->getCost() << ", Description: " << myCoffee->getDescription() << endl;
    
    // Clean up
    delete myCoffee;
    
    return 0;
}