#include <iostream>
using namespace std;

class Car {
public:
    virtual void show() const = 0;
};

class BMW : public Car {
public:
    void show() const override {
        cout << "This is a BMW." << endl;
    }
};

class SUV : public Car {
public:
    void show() const override {
        cout << "This is an SUV." << endl;
    }
};

class CarFactory {
public:
    static Car* createCar(const string& type) {
        if (type == "BMW") {
            return new BMW();
        } else if (type == "SUV") {
            return new SUV();
        } else {
            return nullptr;
        }
    }
};

int main() {
    string carType;
    cout << "Enter car type (BMW or SUV): ";
    cin >> carType;
    
    Car* myCar = CarFactory::createCar(carType);
    
    if (myCar) {
        myCar->show();
        delete myCar; // Don't forget to clean up
    } else {
        cout << "Invalid car type!" << endl;
    }
    
    return 0;
}