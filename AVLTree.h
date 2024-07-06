#include <iostream>
#include "Node.h"
using namespace std;

class AVLTree
{
private:
    Node *root;

    int height(Node *N);
    int max(int a, int b);
    Node *rightRotate(Node *y);
    Node *leftRotate(Node *x);
    int getBalance(Node *N);
    Node *insertNode(Node *node, Transaction *transaction);
    Transaction *searchNode(Node *root, int key);
    void inOrder(Node *root);

public:
    AVLTree();
    void insert(Transaction *transaction);
    Transaction *search(int key);
    void displayInOrder();
};