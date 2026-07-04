// https://www.youtube.com/watch?v=TlfQOdeFy0Y

#include <iostream>
using namespace std;

enum Color { RED, BLACK };
struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
    Node* root;

    // Right Right Case
    //
    //     y (Grandparent)            x
    //      \                       /   \
    //       x  (Parent)      ->   y     z
    //        \                 
    //         z (New node)
    //
    void LeftRotate(Node* y) {
        if (y == nullptr || y->right == nullptr)
            return;

        Node* x = y->right;
        y->right = x->left; // To preserve x's left subtree before the rotation.

        if (x->left != nullptr)
            x->left->parent = y;

        x->parent = y->parent; // To preserve the parent of the node being rotated.

        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;

        // Rotation
        x->left = y;
        y->parent = x;
    }

    // Left Left Case
    //
    //         y (Grandparent)           x
    //        /                        /   \
    //       x  (Parent)         ->   z     y
    //      /                        
    //     z (New node)
    //
    void RightRotate(Node* y) {
        if (y == nullptr || y->left == nullptr)
            return;

        Node* x = y->left;
        y->left = x->right; // To preserve x's right subtree before the rotation.

        if (x->right != nullptr)
            x->right->parent = y;

        x->parent = y->parent; // To preserve the parent of the node being rotated.

        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;

        // Rotation
        x->right = y;
        y->parent = x;
    }

    // After an insertion, this fixes the color of nodes surrounding the new node, and
    // makes rotations as needed.
    void FixInsert(Node* z) {
        while (z != root && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) { // Tests if the new node is a left child three levels down from the root.
                Node* y = z->parent->parent->right;

                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } 
                else {
                    if (z == z->parent->right) { // If a Left Right case is found.
                        z = z->parent;
                        LeftRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    RightRotate(z->parent->parent);
                }
            } 
            else {
                Node* y = z->parent->parent->left;

                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } 
                else {
                    if (z == z->parent->left) { // If a Right Left case is found.
                        z = z->parent;
                        RightRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    LeftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void Delete(Node* z) {
        Node* y = z;
        Node* x = nullptr;
        Color yOriginalColor = y->color;

        if (z->left == nullptr) {
            x = z->right;
            Transplant(z, z->right);
        } 
        else if (z->right == nullptr) {
            x = z->left;
            Transplant(z, z->left);
        } 
        else {
            y = FindMinNode(z->right);
            yOriginalColor = y->color;
            x = y->right;

            if (y->parent == z) {
                if (x != nullptr)
                    x->parent = y; // Check if x is not nullptr before assigning parent
            } else {
                if (x != nullptr)
                    x->parent = y->parent; // Check if x and y->parent are not nullptr before assigning parent
                Transplant(y, y->right);
                if (y->right != nullptr)
                    y->right->parent = y; // Check if y->right is not nullptr before assigning parent
                y->right = z->right;
                if (y->right != nullptr)
                    y->right->parent = y; // Check if y->right is not nullptr before assigning parent
            }
            Transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr)
                y->left->parent = y; // Check if y->left is not nullptr before assigning parent
            y->color = z->color;
        }

        if (yOriginalColor == BLACK && x != nullptr) // Check if x is not nullptr
            FixDelete(x);

        delete z; // Free memory allocated for the deleted node
    }

    Node* FindMinNode(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Moves the subtree rooteed at v, into the position of u.
    void Transplant(Node* u, Node* v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
            
        if (v != nullptr)
            v->parent = u->parent;
    }

    // After an insertion, this fixes the color of nodes surrounding the new node, and
    // makes rotations as needed.
    void FixDelete(Node* x) {
        while (x != root && x != nullptr && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* sibling = x->parent->right;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    x->parent->color = RED;
                    LeftRotate(x->parent);
                    sibling = x->parent->right;
                }

                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    x = x->parent;
                } 
                else {
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        if (sibling->left != nullptr)
                            sibling->left->color = BLACK;

                        sibling->color = RED;
                        RightRotate(sibling);
                        sibling = x->parent->right;
                    }

                    sibling->color = x->parent->color;
                    x->parent->color = BLACK;

                    if (sibling->right != nullptr)
                        sibling->right->color = BLACK;

                    LeftRotate(x->parent);
                    x = root;
                }
            } 
            else {
                Node* sibling = x->parent->left;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    x->parent->color = RED;
                    RightRotate(x->parent);
                    sibling = x->parent->left;
                }

                if ((sibling->right == nullptr || sibling->right->color == BLACK) &&
                    (sibling->left == nullptr || sibling->left->color == BLACK)) {
                    sibling->color = RED;
                    x = x->parent;
                } 
                else {
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        if (sibling->right != nullptr)
                            sibling->right->color = BLACK;

                        sibling->color = RED;
                        LeftRotate(sibling);
                        sibling = x->parent->left;
                    }

                    sibling->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (sibling->left != nullptr)
                        sibling->left->color = BLACK;

                    RightRotate(x->parent);
                    x = root;
                }
            }
        }

        if (x != nullptr) //Prevents writing to an empty node.
            x->color = BLACK;
    }

    public:
    RedBlackTree() : root(nullptr) {}

    // Inserts a new node
    void Insert(int value) {
        Node* newNode = new Node(value);
        Node* parent = nullptr;
        Node* travNode = root;

        // Traversing the tree until it reaches the bottom,
        // assigning the parent node to the traversal node
        // right before moving it down the branches.
        while (travNode != nullptr) {
            parent = travNode;
            if (newNode->data < travNode->data)
                travNode = travNode->left;
            else
                travNode = travNode->right;
        }

        // Connecting the new node to the parent.
        newNode->parent = parent;

        // Connecting the parent to the new node.
        if (parent == nullptr)
            root = newNode;
        else if (newNode->data < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;

        FixInsert(newNode);
    }

    // Checks if a node slated for removal exists, then runs the deletion functions.
    void Remove(int key) {
        Node* nodeToDelete = Search(key);
        
        if (nodeToDelete == nullptr) {
            return;
        }

        Delete(nodeToDelete);
    }

    Node* Search(int key) {
        Node* travNode = root;
        while (travNode != nullptr) {
            if (key < travNode->data)
                travNode = travNode->left;
            else if (key > travNode->data)
                travNode = travNode->right;
            else {
                return travNode;
            }
        }

        cout << "Node with value " << key << " not found in the tree." << endl;
        return nullptr;
    }

    void PrintHelper(Node* root, string indent, bool last) {
        if (root != nullptr) {
            cout << indent;

            if (last) {
                cout << "R----";
                indent += "   ";
            }
            else {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = (root->color == RED) ? "RED" : "BLACK";
            cout << root->data << "(" << sColor << ")" << endl;
            PrintHelper(root->left, indent, false);
            PrintHelper(root->right, indent, true);
        }
    }

    void Display() {
        if (root == nullptr) {
            cout << "\n The tree is empty...\n";
            return;
        }
        PrintHelper(root, "", true);
    } 
};

int main() {
    RedBlackTree* rbTree = new RedBlackTree();
    rbTree->Insert(7);
    rbTree->Insert(3);
    rbTree->Insert(2);
    rbTree->Insert(6);
    rbTree->Insert(11);
    rbTree->Insert(10);
    rbTree->Insert(8);
    rbTree->Insert(22);
    rbTree->Insert(26);

    rbTree->Display();
    cout << endl;
    rbTree->Remove(22);
    rbTree->Display();

    return 0;
}


