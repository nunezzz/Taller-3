#include "NodeABB.h"
#include "Transaction.h"
#include <iostream>
#include <queue>
using namespace std;

// me agrupa 2 variables bajo un solo nombre, en este caso el numero de cuenta y la razón de la sospecha
struct suspiciousAccount
{
    int accountNumber;
    string reason;
};
class ABB
{
private:
    NodeABB *root;
    NodeABB *insert(NodeABB *node, Transaction *transaction);
    NodeABB *search(NodeABB *node, int data);
    void inOrder(NodeABB *node);
    void findSuspiciousTransactions(NodeABB *node, queue<suspiciousAccount> &suspiciousAccountss);
    void checkConditions(vector<Transaction *> &transList, queue<suspiciousAccount> &suspiciousAccounts);
    void collectTransactions(NodeABB *node, vector<Transaction *> &transList);

public:
    ABB();
    void insert(Transaction *transaction);
    Transaction *search(int key);
    void inOrder();
    void suspiciousTransactions(queue<suspiciousAccount> &suspiciousAccounts);
};
