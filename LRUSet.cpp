/*
    Cache set for n-way set associative cache using LRU policy
    Make this an interface instead?
*/

#include "LRUSet.h"
using namespace std;


LRUSet::LRUSet(short set_size) {
    LRUSet::max_size = set_size;
    LRUSet::data = vector<CacheEntry>();
}

bool LRUSet::AddReference(unsigned long tag, unsigned long offset) {
    if (LRUSet::Find(tag, offset)) {
        // If the reference is in the queue then return a hit
        // push the element at the beginning of the vector to the end

        // Copy the value
        CacheEntry temp_addr = LRUSet::data[0];

        // then remove it from the beginning of the vector to the end
        LRUSet::data.erase(LRUSet::data.begin());
        LRUSet::data.push_back(temp_addr);
        return 1;

    } else if (LRUSet::data.size() == LRUSet::max_size) {
        // pop the first index and add the reference address to the end
        LRUSet::data.erase(LRUSet::data.begin());
        LRUSet::data.push_back(CacheEntry(tag, offset));
        return 0;
    } else {
        // push the address to the vector
        LRUSet::data.push_back(CacheEntry(tag, offset));
        return 0;
    }
    return 0;
}
/*
*  Find whether the value specified is in the queue
*  Checks the index and tag of the reference and compares it to all the references currently loaded
* If both of them match then it returns true
*  Uses a pass by value to copy the given queue variable so the original one stays unmodified.
*/
bool LRUSet::Find(unsigned long tag, unsigned long offset) {

    for (CacheEntry e : LRUSet::data) {



        // compare the tag to the stored tag
        if (e.getTag() == tag) return 1;

    }
    return 0;
}