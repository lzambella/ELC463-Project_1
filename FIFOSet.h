#pragma once

#include <queue>
#include "Set.h"
#include "CacheEntry.h"
#include <string.h>

using namespace std;
// Represents a set in cache memory for n-way set cache
// assumes FIFO operation
class FIFOSet: public Set {
    private:
        queue<CacheEntry> set_data; // Cache data
        int max_size;               // Max size of the queue, if anything else gets added, then something must be removed
        bool Find(unsigned long, unsigned long);          // Search the queue
    public:
        FIFOSet(int);               // Constructor
        FIFOSet(int, short, short, short);
        FIFOSet();
        bool AddReference(unsigned long, unsigned long);           // Add a memory reference to the set
};