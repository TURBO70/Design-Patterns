#include <iostream>
using namespace std;

class SortStrategy {
public:
    virtual void sort(int arr[], int size) = 0;
    virtual ~SortStrategy() {}
};

class BubbleSort : public SortStrategy {
public:
    void sort(int arr[], int size) override {
        cout << "Sorting array using bubble sort" << endl;
    }
};

class QuickSort : public SortStrategy {
public:
    void sort(int arr[], int size) override {
        cout << "Sorting array using quick sort" << endl;
    }
};

class Sorter {
private:
    SortStrategy* strategy;

public:
    Sorter() : strategy(nullptr) {}
    
    ~Sorter() {
        delete strategy;
    }
    
    void setStrategy(SortStrategy* newStrategy) {
        delete strategy;
        strategy = newStrategy;
    }
    
    void sortArray(int arr[], int size) {
        if (strategy) {
            strategy->sort(arr, size);
        } else {
            cout << "No sorting strategy set" << endl;
        }
    }
};

int main() {
    int arr[] = {5, 2, 9, 1, 3};
    int size = 5;
    
    Sorter sorter;
    
    cout << "Choose sorting algorithm (1=Bubble sort, 2=Quick sort): ";
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        sorter.setStrategy(new BubbleSort());
    } else {
        sorter.setStrategy(new QuickSort());
    }
    
    sorter.sortArray(arr, size);
    
    return 0;
}