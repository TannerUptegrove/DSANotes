#include <iostream>
#include <climits>
using namespace std;

class Queue {
    int* array;
    int front;
    int rear;
    int capacity;

    public:
    Queue(int numElements) {
        capacity = numElements;
        array = new int[capacity];
        front= -1;
        rear = -1;
    }

    int IsEmpty() {
        return front < 0;
    }

    int IsFull() {
        return front >= capacity - 1;
    }

    void Enqueue(int value) {
        if (IsFull()) {
            cout << "\nQueue overflow...\n";
            return;
        }

        if (IsEmpty()) {
            front = 0;
        }

        // Puts the new value at the back of the queue.
        array[++rear] = value;
    }

    int Dequeue() {
        if (IsEmpty()) {
            cout << "\nQueue underflow...\n";
            return INT_MIN;
        }

        // "Erases" the value to be deleted.
        // The front int is incremented after grabbing the value, preventing it
        // from being accessed again.
        int frontValue = array[front++];

        // Resetting the references if the queue is empty.
        if (IsEmpty()) {
            front = -1;
            rear = -1;
        }

        return frontValue;
    }

    int PeekFront() {
        if (IsEmpty()) {
            cout << "\nQueue underflow...\n";
            return INT_MIN;
        }

        return array[front];
    }

    int PeekRear() {
        if (IsEmpty()) {
            cout << "\nQueue underflow...\n";
            return INT_MIN;
        }

        return array[rear];
    }
};

int main() {
    Queue queue(20);
    queue.Enqueue(50);
    queue.Enqueue(80);
    queue.Enqueue(58);
    cout << queue.PeekFront() << endl;
    cout << queue.PeekRear() << endl;
    queue.Dequeue();
    cout << queue.PeekFront() << endl;

    return 0;
}