#include <iostream>
#include <string>
using namespace std;

class Target {
public:
    virtual void request() = 0;
    virtual ~Target() {}
};

class OldSystem {
public:
    void specificRequest() {
        cout << "OldSystem: Handling specific request" << endl;
    }
};

class Adapter : public Target {
private:
    OldSystem* oldSystem;

public:
    Adapter() {
        oldSystem = new OldSystem();
    }

    ~Adapter() {
        delete oldSystem;
    }

    void request() override {
        cout << "Adapter: Translating request to OldSystem" << endl;
        oldSystem->specificRequest();
    }
};

int main() {
    Target* target = new Adapter();
    
    target->request();
    
    delete target;
    return 0;
}