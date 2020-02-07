#pragma once

#include <queue>
#include "Set.h"

using namespace std;
// Represents a set in cache memory for n-way set cache
// assumes FIFO operation
class FIFOSet: public Set {
    private:
        queue<int> set_data;    // Cache data in a set_data
        int max_size;           // Max size of the queue, if anything else gets added, then something must be removed
        bool Find(int &); // Search the queue
    public:
        FIFOSet(int);               // Constructor
        FIFOSet();
        bool AddReference(int &);           // Add a memory reference to the set
};