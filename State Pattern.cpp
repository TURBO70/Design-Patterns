#include <iostream>

class OnState;
class OffState;

class State {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~State() = default;
};

class LightBulb {
private:
    State* state; 

public:
    LightBulb(State* initialState) : state(initialState) {}

    void setState(State* newState) {
        state = newState;
    }

    void turnOn() {
        state->turnOn();
    }

    void turnOff() {
        state->turnOff();
    }
};

class OnState : public State {
public:
    void turnOn() override {
        std::cout << "Light is already ON.\n";
    }

    void turnOff() override {
        std::cout << "Turning OFF the light.\n";
    }
};

class OffState : public State {
public:
    void turnOn() override {
        std::cout << "Turning ON the light.\n";
    }

    void turnOff() override {
        std::cout << "Light is already OFF.\n";
    }
};

int main() {
    OffState off;
    OnState on;

    LightBulb bulb(&off);

    bulb.turnOn(); 
    bulb.setState(&on);
    bulb.turnOn();  
    bulb.turnOff(); 
    bulb.setState(&off);
    bulb.turnOff(); 

 
}
