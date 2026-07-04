#include <iostream>
#include <climits>
using namespace std;

class SinglyLinkedList {
    // Internal object used to store data within the list.
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };

    Node* head;
    int size;

    public:
    SinglyLinkedList() : head(nullptr), size(0) {}
    SinglyLinkedList(int value) : head(new Node(value)), size(1) {}

    ~SinglyLinkedList() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }

        // After deleting the data connected to a pointer, the pointer itself
        // may still holding the invalid memory address.
        //
        // This ensures that the "dangling pointer" is properly eliminated.
        head = nullptr;
    }

    void PushFront(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void PushBack(int value) { PushAt(size, value); }

    void PushAt(int position, int value) {
        if (position == 0) {
            PushFront(value);
            return;
        }

        if (position < 0 || position > size) {
            cout << "\nThe position is out of range...\n";
            return;
        }

        // Temporary node created to traverse through the list.
        // Will land on the node behind the position where the new one will be.
        Node* temp = head;
        for (int i = 0; i < position - 1; i++)
            temp = temp->next;
        
        Node* newNode = new Node(value);
        newNode->next = temp->next; // Preserves the nodes after the new node.
        temp->next = newNode;
        size++;
    }

    void PopFront() {
        if (head == nullptr) {
            cout << "List is empty...";
            return;
        }

        Node* nodeToChop = head;
        head = head->next;
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
            cout << "List is empty...";
            return;
        }

        if (position < 0 || position > size) {
            cout << "\nPosition is out of range...\n";
            return;
        }

        // Temporary node created to traverse the list.
        // Will land on the node behind the one to delete.
        Node* temp = head;
        for (int i = 0; i < position - 1; i++)
            temp = temp->next;

        Node* nodeToChop = temp->next; // Grabs the node to delete.
        temp->next = nodeToChop->next; // Saves the nodes behind the one to delete.
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

        Node* temp = head->next;
        for(int i = 1; i < size + 1; i++) {
            if (temp->data == value)
                return i;
            temp = temp->next;
        }
        cout << "\nNode with value " << value << "could not be found...\n";
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
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    // Detects if a node's pointer is set to a previous node in the linked list.
    void FloydCycleDetection() {
        //Creates a cycle for testing. The 6th node will point to the 3rd.
        head->next->next->next->next->next = head->next->next;

        Node *slow = head, *fast = head;
        while (slow != nullptr && fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                cout << "\nCycle detected\n";
                break;
            }
        }

        if (slow == fast) {
            slow = head;

            if (slow == fast) {
                while (fast->next != slow)
                    fast = fast->next;
            }
            else {
                while (slow->next != fast->next) {
                    slow = slow->next;
                    fast = fast->next;
                }
            }
            
            fast->next = nullptr;
        }


    }

    void Display() {
        if (head == nullptr) {
            cout << "\nThe list is empty...\n";
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
};


int main() {
    SinglyLinkedList list;
    list.PushFront(10);
    list.PushFront(100);
    list.PushFront(200);
    list.PushFront(500);
    list.PushFront(600);
    list.PushFront(80);
    cout << endl;
    list.Display();
    cout << endl;

    list.Reverse();
    list.Display();

    return 0;
}