#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class MinHeap {
    vector<int> heap;
    int size;
    int capacity; //Max size

    public:
    MinHeap(int c) {
        size = 0;
        capacity = c;
        heap.resize(capacity);
    }

    void Heapify(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;

        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            Heapify(smallest);
        }
    }

    void BuildHeap(const vector<int> h) {
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

        while (i != 0 && heap[(i - 1) / 2] > heap[i]) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    int Peek() {
        if (size <= 0) {
            cout << "\n The heap is empty...\n";
            return INT_MIN;
        } 

        return heap[0];
    }

    int ExtractMin() {
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
            cout << "\n The key was not found...\n";
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

    void Display() const {
        for (int i = 0; i < size; i++)
            cout << heap[i] << " ";
        cout << endl;
    }
};

int main() {
    MinHeap* minHeap = new MinHeap(6);
    vector<int> array = {15, 10, 5, 4, 3, 2};

    minHeap->BuildHeap(array);

    cout << endl;
    minHeap->Display();

    minHeap->Insert(1);
    cout << endl;
    minHeap->Display();

    cout << "\n" << minHeap->Peek();

    cout << "\n" << minHeap->ExtractMin();

    cout << endl;
    minHeap->Display();

    minHeap->Delete(4);
    cout << endl;
    minHeap->Display();

    delete minHeap;

    return 0;
}