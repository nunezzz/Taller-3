#include <iostream>
#include "Node.h"
#include "Transaction.h"
using namespace std;

Node :: Node (Transaction* trans) : transactions(trans),left(nullptr),right(nullptr),height(1){}
