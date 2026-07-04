#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }

    ~Node() {
        delete left;
        delete right;
    }
};

void InOrderDepthFirstSearch(Node* node) {
    if (node == nullptr) {
        return;
    }

    InOrderDepthFirstSearch(node->left);
    cout << node->data << " ";
    InOrderDepthFirstSearch(node->right);
}

void PreOrderDepthFirstSearch(Node* node) {
    if (node == nullptr) {
        return;
    }

    cout << node->data << " ";
    PreOrderDepthFirstSearch(node->left);
    PreOrderDepthFirstSearch(node->right);
}

void PostOrderDepthFirstSearch(Node* node) {
    if (node == nullptr) {
        return;
    }

    PostOrderDepthFirstSearch(node->left);
    PostOrderDepthFirstSearch(node->right);
    cout << node->data << " ";
}

void BreadthFirstSearch(Node* root) {
    if (root == nullptr) {
        return;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        cout << node->data << " ";

        if (node->left != nullptr) {
            q.push(node->left);
        }

        if (node->right != nullptr) {
            q.push(node->right);
        }
    }
}

int main() {
    Node* root = new Node(2);
    root->left = new Node(5);
    root->right = new Node(3);
    root->left->right = new Node(10);
    root->left->left = new Node(9);
    root->right->left = new Node(7);

    cout << "\n In Order Depth First Search: ";
    InOrderDepthFirstSearch(root);
    cout << endl;

    cout << "\n Pre-Order Depth First Search: ";
    PreOrderDepthFirstSearch(root);
    cout << endl;

    cout << "\n Post-Order Depth First Search: ";
    PostOrderDepthFirstSearch(root);
    cout << endl;

    cout << "\n Breadth First Search: ";
    BreadthFirstSearch(root);
    cout << endl;
    
    delete root;
    root = nullptr;
    
    return 0;
}