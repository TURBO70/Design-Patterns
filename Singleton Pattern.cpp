#include <iostream>
using namespace std;

class Singleton {
private:
    Singleton() {
        cout << "Singleton instance created" << endl;
    }
    
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
    static Singleton* instance;

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
    
    void showMessage() {
        cout << "Hello from Singleton!" << endl;
    }
};


Singleton* Singleton::instance = nullptr;

int main() {
    // Get the singleton instance
    Singleton* s1 = Singleton::getInstance();
    s1->showMessage();
    
    // Try to get another instance
    Singleton* s2 = Singleton::getInstance();
    s2->showMessage();
    
    // Both pointers point to the same instance
    cout << "Are both pointers the same? " << (s1 == s2 ? "Yes" : "No") << endl;
    
    return 0;
}