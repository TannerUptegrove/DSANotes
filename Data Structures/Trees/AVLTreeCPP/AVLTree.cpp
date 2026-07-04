#include <iostream>
#include <algorithm>
using namespace std;

class AVLTree {
    struct Node {
        int data;
        int height;
        Node* left;
        Node* right;

        Node(int value) : data(value), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    int GetHeight(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int GetBalance(Node* node) {
        if (node == nullptr)
            return 0;
        return GetHeight(node->left) - GetHeight(node->right);
    }

    // Right Right Case
    //
    //     y (Grandparent)            x
    //      \                       /   \
    //       x  (Parent)      ->   y     z
    //        \                 
    //         z (New node)
    //
    Node* LeftRotate(Node* y) {
        if (y == nullptr || y->right == nullptr)
            return y;

        Node* x = y->right;
        Node* xSubtree = x->left; // Preserves the subtree before rotation

        // Rotation
        x->left = y;
        y->right = xSubtree;

        //Update the heights.
        y->height = 1 + max(GetHeight(y->left), GetHeight(y->right));
        x->height = 1 + max(GetHeight(x->left), GetHeight(x->right));

        return x;
    }

    // Left Left Case
    //
    //         y (Grandparent)           x
    //        /                        /   \
    //       x  (Parent)         ->   z     y
    //      /                        
    //     z (New node)
    //
    Node* RightRotate(Node* y) {
        if (y == nullptr || y->left == nullptr)
            return y;

        Node* x = y->left;
        Node* xSubtree = x->right; // Preserves the subtree before rotation.

        // Rotation
        x->right = y;
        y->left = xSubtree;

        //Update the heights.
        y->height = 1 + max(GetHeight(y->left), GetHeight(y->right));
        x->height = 1 + max(GetHeight(x->left), GetHeight(x->right));

        return x;
    }

    Node* Insert(Node* node, int value) {
        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = Insert(node->left, value);
        else if (value > node->data)
            node->right = Insert(node->right, value);
        else
            return node;

        node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));
        int balance = GetBalance(node);

        // Left Left Case
        if (balance > 1 && value < node->left->data)
            return RightRotate(node);

        // Right Right Case
        if (balance < -1 && value > node->right->data)
            return LeftRotate(node);

        // Left Right Case
        if (balance > 1 && value > node->left->data)
            node->left = LeftRotate(node->left);
            return RightRotate(node);

        // Right Left Case
        if (balance < -1 && value < node->right->data)
            node->right = RightRotate(node->right);
            return LeftRotate(node);

        return node;
    }

    Node* Delete(Node* node, int key) {
        if (node == nullptr)
            return node;

        if (key < node->data)
            node->left = Delete(node->left, key);
        else if (key > node->data)
            node->right = Delete(node->right, key);
        else {
            if ((node->left == nullptr) || (node->right == nullptr)) {
                Node* temp = node->left ? node->left : node->right;


                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    delete node;
                    node = nullptr;
                    return temp;
                }
            }
            else {
                Node* temp = FindMinValue(node->right);
                node->data = temp->data;
                node->right = Delete(node->right, temp->data);
            }
        }

        if (node == nullptr)
                return node;
            
        node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));
        int balance = GetBalance(node);

        // Left Left Case
        if (balance > 1 && GetBalance(node->left) >= 0)
            return RightRotate(node);

        // Right Right Case
        if (balance < -1 && GetBalance(node->right) <= 0)
            return LeftRotate(node);
            
        // Left Right Case
        if (balance > 1 && GetBalance(node->left) < 0) {
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && GetBalance(node->right) > 0) {
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }

        return node;
    }

    Node* FindMinValue(Node* node) {
        Node* temp = node;
        while (temp != nullptr)
            temp = temp->left;
        return temp;
    }

    void Search(Node* node, int key) {
        if (node == nullptr)
            return;

        if (key < node->data)
            Search(node->left, key);
        else if (key > node->data)
            Search(node->right, key);
        else
            cout << "The node has been found at level " << node->height;
    }


    void Display(Node* node) {
        if (node == nullptr)
            return;

        Display(node->left);
        cout << node->data << " " << " H: " << node->height << " || ";
        Display(node->right);
    }

    public:
    AVLTree() : root(nullptr) {}

    // Functions lead to their recursive versions.
    void Insert(int value) { root = Insert(root, value); }
    void Delete(int key) { root = Delete(root, key); }
    void Search(int key) { Search(root, key); }
    void Display() { Display(root); }
};

// Driver Code
int main() {
    AVLTree* avl = new AVLTree();
    avl->Insert(10);
    avl->Insert(80);
    avl->Insert(17);
    avl->Insert(45);
    avl->Insert(89);
    avl->Insert(90);
    avl->Display();

    cout << endl;
    avl->Delete(80);
    avl->Display();

    cout << endl;
    avl->Search(17);

    return 0;
}