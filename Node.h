#pragma once
#include "Transaction.h"
using namespace std;

class Node
{
    public:
    Transaction* transactions;
    Node* left;
    Node* right;
    int height;
    Node(Transaction* trans);
};