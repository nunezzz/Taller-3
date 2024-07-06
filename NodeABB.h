#pragma once
#include <iostream>
#include "Transaction.h"
using namespace std;

class NodeABB
{
    public:
    NodeABB(Transaction* trans);
    Transaction* transaction;
    NodeABB* left;
    NodeABB* right;

    //NodeABB(Transaction* trans) : transaction(trans), left(nullptr), right(nullptr) {}
};