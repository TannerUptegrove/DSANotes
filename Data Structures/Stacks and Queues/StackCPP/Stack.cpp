#include <iostream>
#include <climits>
using namespace std;

class Stack {
    int* array;
    int top;
    int capacity;

    public:
    Stack(int numElements) {
        capacity = numElements;
        array = new int[capacity];
        top = -1;
    }

    ~Stack() {
        delete array;
    }

    bool IsEmpty() {
        return top < 0;
    }

    bool IsFull() {
        return top >= capacity - 1;
    }

    void Push(int value) {
        if (IsFull()) {
            cout << "\nStack overflow...\n";
            return;
        }   

        array[++top] = value;
    }

    int Pop() {
        if (IsEmpty()) {
            cout << "\nStack underflow...\n";
            return INT_MIN;
        }

        // "Erases" the value to be deleted by incrementing the top int,
        // preventing it from being accessed again.
        return array[top--];
    }

    int Peek() {
        if (IsEmpty()) {
            cout << "\nStack underflow...\n";
            return INT_MIN;
        }

        return array[top];
    }
};


int main() {
    Stack stack(40);
    stack.Push(16);
    cout << stack.Peek() << endl;
    cout << stack.Pop() << endl;
    cout << stack.Peek();

    return 0;
}