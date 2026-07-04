#include <iostream>
#include <climits>
#include<vector>
using namespace std;

class MaxHeap {
    vector<int> heap;
    int size;
    int capacity; //Max size.

    public:
    MaxHeap(int c) {
        size = 0;
        capacity = c;
        heap.resize(capacity);
    }

    void Heapify(int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] > heap[largest])
            largest = left;

        if (right < size && heap[right] > heap[largest])
            largest = right;

        if (largest != index) {
            swap(heap[index], heap[largest]);
            Heapify(largest);
        }
    }

    void BuildHeap(const vector<int>& h) {
        capacity = h.size();
        size = capacity;
        heap = h;

        for (int i = (size - 1) / 2; i >= 0; i--)
            Heapify(i);
    }

    void Insert(int value) {
        if (size == capacity) {
            capacity *= 2;
            heap.resize(capacity);
        }

        size++;
        int i = size - 1;
        heap[i] = value;

        while (i != 0 && heap[(i - 1) / 2] < heap[i]) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    int Top() {
        if (size <= 0)
            return INT_MIN;
        return heap[0];
    }

    int Pop() {
        if (size <= 0)
            return INT_MIN;

        if (size == 1) {
            size--;
            return heap[0];
        }

        int root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        Heapify(0);
        return root;
    }

    void Delete(int key) {
        int index = -1;
        for (int i = 0; i < size; ++i) {
            if (heap[i] == key) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "\n The key could not be found...\n";
            return;
        }

        if (index == size - 1) {
            size--;
            return;
        }

        heap[index] = heap[size - 1];
        size--;
        Heapify(index);
    }

    void Display() {
        for (int i = 0; i < size; ++i)
            cout << heap[i] << " ";
    }
};

int main() {
    // Create a MaxHeap with initial capacity of 6
    MaxHeap* maxHeap = new MaxHeap(6);
    vector<int> arr = { 2, 3, 4, 5, 10, 15 };

    // Build the heap from the array
    maxHeap->BuildHeap(arr);

    // Print the max heap
    maxHeap->Display();

    // Insert a node into the heap
    maxHeap->Insert(9);
    cout << "After inserting 9: " << endl;
    maxHeap->Display();

    // Get the maximum value from the max heap
    cout << "Top value: " << maxHeap->Top() << endl;

    // Delete the root node of the max heap
    cout << "Popped value: " << maxHeap->Pop() << endl;
    cout << "After popping: ";
    maxHeap->Display();

    // Delete a specific value from the max heap
    maxHeap->Delete(5);
    cout << "\nAfter deleting the node 5: ";
    maxHeap->Display();

    return 0;
}
