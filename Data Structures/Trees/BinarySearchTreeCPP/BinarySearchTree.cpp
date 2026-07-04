#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}

    ~Node() {
        delete left;
        delete right;
    }
};

class BinarySearchTree {
    Node* root;

    Node* Insert(Node* node, int value) {
        // Executes when the traversing has reached
        // the bottom of the tree.
        // Will create the new node there.
        if (node == nullptr)
            return new Node(value);

        // Traversing down the tree.
        if (value < node->data)
            node->left = Insert(node->left, value);
        else if (value > node->data)
            node->right = Insert(node->right, value);
        else
            return; // Duplicate nodes are not accepted.

        return node;
    }

    Node* Delete(Node* node, int key) {
        if (node == nullptr) {
            cout << "\n The tree is empty...\n";
            return nullptr;
        }

        // Traversing down the tree until the node is found.
        if (key < node->data)
            node->left = Delete(node->left, key);
        else if (key > node->data)
            node->right = Delete(node->right, key);
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* inOrderSuccessor = FindMinNode(node->right);
            node->data = inOrderSuccessor->data;
            node->right = Delete(node->right, inOrderSuccessor->data);
        }

        return node;
    }

    Node* FindMinNode(Node* node) {
        Node* tempNode = node;
        while (tempNode && tempNode->left != nullptr)
            tempNode = tempNode->left;
        return tempNode;
    }

    Node* FindMaxNode(Node* node) {
        Node* tempNode = node;
        while (tempNode && tempNode->right != nullptr)
            tempNode = tempNode->right;
        return tempNode;
    }

    Node* Search(Node* node, int key) {
        if (node == nullptr) {
            cout << "\n A node with the given key could not be found...\n";
            return nullptr;
        }

        
        if (key == node->data)
            return node;
        if (key < node->data)
            cout << "here";
            return Search(node->left, key);

        return Search(node->right, key);
    }

    void Display(Node* node) {
        if (node == nullptr)
            return;

        Display(node->left);
        cout << node->data << " ";
        Display(node->right);
    }

    public:
    BinarySearchTree() : root(nullptr) {}
    BinarySearchTree(int value) : root(new Node(value)) {}

    ~BinarySearchTree() { 
        delete root; 
        root = nullptr;
    }

    // Functions lead to their recursive versions.
    void Insert(int value) { root = Insert(root, value); }
    void Delete(int key) { root = Delete(root, key); }
    Node* Search(int key) { return Search(root, key); }
    void Display() { Display(root); }

};
\
int main() {
    BinarySearchTree* tree = new BinarySearchTree();
    tree->Insert(50);
    tree->Insert(30);
    tree->Insert(20);
    tree->Insert(40);
    tree->Insert(70);
    tree->Insert(60);
    tree->Insert(80);

    cout << "\nBinary Search Tree: ";
    tree->Display();
    cout << endl;

    Node* found = tree->Search(50);
    cout << found->data;

    return 0;
}