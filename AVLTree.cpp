#include <iostream>
#include "Node.h"
#include "AVLTree.h"
using namespace std;

AVLTree ::AVLTree() : root(nullptr) {}

/* Función que devuelve la altura del nodo */
int AVLTree::height(Node *n)
{
    if (n == nullptr)
    {
        return 0;
    }
    return n->height;
}
/* Función que devuelve el valor maximo */
int AVLTree::max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
/* Función que realiza una rotación a la derecha y devuelve el nodo raíz */
Node *AVLTree::rightRotate(Node *y)
{
    Node *x = y->left;
    Node *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(height(y->left), height(y->right) + 1);
    x->height = max(height(x->left), height(x->right) + 1);
    return x;
}
/* Función que realiza una rotación a la izquierda y devuelve el nodo raíz */
Node *AVLTree::leftRotate(Node *x)
{
    Node *y = x->right;
    Node *t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = max(height(x->left), height(x->right) + 1);
    y->height = max(height(y->left), height(y->right) + 1);
    return y;
}
/* Función que devuelve el factor de balanceo del nodo */
int AVLTree::getBalance(Node *n)
{
    if (n == nullptr)
    {
        return 0;
    }
    return height(n->left) - height(n->right);
}
/* Función que inserta el nuevo nodo con la transacción al arbol y devuelve la raíz */
Node *AVLTree::insertNode(Node *node, Transaction *transaction)
{
    if (node == nullptr)
    {
        return new Node(transaction);
    }
    if (transaction->getID() < node->transactions->getID())
    {
        node->left = insertNode(node->left, transaction);
    }
    else if (transaction->getID() > node->transactions->getID())
    {
        node->right = insertNode(node->right, transaction);
    }
    else
    {
        return node;
    }
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && transaction->getID() < node->left->transactions->getID())
    {
        return rightRotate(node);
    }
    if (balance < -1 && transaction->getID() > node->right->transactions->getID())
    {
        return leftRotate(node);
    }
    if (balance > 1 && transaction->getID() > node->left->transactions->getID())
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && transaction->getID() < node->right->transactions->getID())
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
/* Función que busca el nodo en base al dato ingresado en el subárbol y devuelve la transacción correspondiente*/
Transaction *AVLTree::searchNode(Node *root, int key)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    if (root->transactions->getID() == key)
    {
        return root->transactions;
    }
    if (key < root->transactions->getID())
    {
        return searchNode(root->left, key);
    }
    return searchNode(root->right, key);
}
/* Función que realiza recorrido in orden del arbol*/
void AVLTree::inOrder(Node *root)
{
    if (root != nullptr)
    {
        inOrder(root->left);
        cout << root->transactions->getID() << " ";
        inOrder(root->right);
    }
}
/* Función que inserta una nueva transacción en árbol */
void AVLTree::insert(Transaction *transaction)
{
    root = insertNode(root, transaction);
}
/* Función que busca el dato correspondiente en el árbol*/
Transaction *AVLTree::search(int key)
{
    return searchNode(root, key);
}
/* Función que muestra los nodos del árbol */
void AVLTree::displayInOrder()
{
    inOrder(root);
}