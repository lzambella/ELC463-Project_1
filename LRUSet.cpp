/*
    Cache set for n-way set associative cache using LRU policy
    Make this an interface instead?
*/

#include "LRUSet.h"
using namespace std;


LRUSet::LRUSet(int & set_size) {
    LRUSet::max_size = set_size;
    LRUSet::data = vector<int>();
}

bool LRUSet::AddReference(int & addr) {
    if (LRUSet::Find(addr)) {
        // If the reference is in the queue then return a hit
        // push the element at the beginning of the vector to the end

        // Copy the value
        int temp_addr = LRUSet::data[0];

        // then remove it from the vector
        LRUSet::data.erase(LRUSet::data.begin());
        LRUSet::data.push_back(temp_addr);
        return 1;

    } else if (LRUSet::data.size() == LRUSet::max_size) {
        // pop the first index and add the reference address to the end
        LRUSet::data.erase(LRUSet::data.begin());
        LRUSet::data.push_back(addr);
        return 0;
    } else {
        // push the address to the vector
        LRUSet::data.push_back(addr);
        return 0;
    }
    return 0;
}
bool LRUSet::Find(int & addr) {
    // Basic search algorithm
    for (int i : LRUSet::data) {
        if (i == addr) return 1;
    }
    return 0;
}