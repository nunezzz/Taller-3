#include <iostream>
#include "NodeABB.h"
using namespace std;

NodeABB :: NodeABB(Transaction* trans) : transaction(trans), left(nullptr), right(nullptr) {}
