#include <iostream>
#include <climits>
using namespace std;

class DoublyLinkedList {
    struct Node {
        int data;
        Node* prev;
        Node* next;

        Node(int value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    int size;

    public:
    DoublyLinkedList() : head(nullptr), size(0) {}
    DoublyLinkedList(int value) : head(new Node(value)), size(1 ) {}

    void PushFront(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head->prev = newNode; // Connects the old head to the new one.
        head = newNode;       // Reassigns the head as the new node.
        size++;
    }

    void PushBack(int value) {
        PushAt(size, value);
    }
    
    void PushAt(int position, int value) {
        if (position == 0)
            PushFront(value);

        if (position < 0 || position > size) {
            cout << "\nPosition is out of range...\n";
            return;
        }

        // Temporary node created to traverse the linked list.
        // Will land on the node behind the position where the new one will be.
        Node* temp = head;
        for (int i = 0; i < position - 1; i++)
            temp = temp->next;

        Node* newNode = new Node(value);
        newNode->next = temp->next; // Saves the nodes after the new one.
        newNode->prev = temp;       // Connects the new node to the one behind it.
        temp->next = newNode;
        size++;

        // Connects the node in front of the new node to it.
        if (newNode->next != nullptr)
            newNode->next->prev = newNode;
    }

    void PopFront() {
        if (head == nullptr) {
            cout << "\nList is empty...\n";
            return;
        }

        Node* nodeToChop = head;
        head = head->next;

        // Erases the new head's prev pointer. It must be after a nullptr
        // check to prevent a segmentation fault.
        if (head != nullptr)
            head->prev = nullptr;

        delete nodeToChop;
        size--;
    }
    
    void PopBack() { PopAt(size - 1); }

    void PopAt(int position) {
        if (position == 0) {
            PopFront();
            return;
        }

        if (head == nullptr) {
            cout << "\nList is empty...\n";
            return;
        }

        if (position < 0 || position > size) {
            cout << "\nPosition is out of range...\n";
            return;
        }

        // Temporary node created to traverse the linked list.
        // Will land behind the node to delete.
        Node* temp = head;
        for (int i = 0; i < position - 1; i++)
            temp = temp->next;

        Node* nodeToChop = temp->next;
        temp->next = nodeToChop->next; // Saves the nodes after the one to delete.

        // Connects the node after the deleted one back to the list.
        if (nodeToChop->next != nullptr)
            nodeToChop->next->prev = temp;

        delete nodeToChop;
        size--;
    }

    int GetDataAt(int position) {
        if (head == nullptr) {
            cout << "\nList is empty...\n";
            return INT_MIN;
        }

        if (position == 0)
            return head->data;

        if (position < 0 || position > size) {
            cout << "\nPosition is out of range...\n";
            return INT_MIN;
        }

        Node* temp = head;
        for (int i = 0; i < position; i++)
            temp = temp->next;
        return temp->data;
    }

    int GetIndex(int value) {
        if (head == nullptr) {
            cout << "\nList is empty...\n";
            return INT_MIN;
        }

        if (head->data == value)
            return 0;

        Node* temp = head;
        for (int i = 1; i < size + 1; i++) {
            if (temp->data == value)
                return i;
            temp = temp->next;
        }
        cout << "ERROR: Node with value " << value << " could not be found...";
        return INT_MIN;
    }

    void Reverse() {
        if (head == nullptr) {
            cout << "\nList is empty...\n";
            return;
        }

        if (size == 1) {
            cout << "\nList only has one node...\n";
            return;
        }

        Node *prev = nullptr, *curr = head, *next = nullptr;
        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            curr->prev = next;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    void Display() {
        if (head == nullptr) {
            cout << "\nList is empty...\n";
            return;
        }

        cout << "Linked list: ";
        if (size == 1) {
            cout << head->data;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < size - 1; i++) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << temp->data;
    }

    void DisplayBackwards() {
        if (head == nullptr) {
            cout << "\nList is empty...\n";
            return;
        }

        cout << "Linked list backwards: ";
        if (size == 1) {
            cout << head->data;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;

        while (temp->prev != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->prev;
        }
        cout << temp->data;
    }
};

int main() {
    DoublyLinkedList list(10);
    list.PushFront(20);

    list.Display();
    cout << endl;
    list.DisplayBackwards();

    return 0;
}