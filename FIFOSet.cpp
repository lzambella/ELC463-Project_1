#include <queue>
#include "FIFOSet.h"
#include <iostream>

using namespace std;

// constructor
FIFOSet::FIFOSet(int max_size) {
    FIFOSet::max_size = max_size;
    FIFOSet::set_data = queue<CacheEntry>();
}

FIFOSet::FIFOSet() {
    FIFOSet::max_size = 2;
    FIFOSet::set_data = queue<CacheEntry>();
}

FIFOSet::FIFOSet(int max, short tag, short index, short offset) {

}

// Add a reference to the queue
// Returns true for a hit, false for a miss
bool FIFOSet::AddReference(unsigned long tag, unsigned long offset) {
    // Check if the mem addr is already in the cache 
    // Clone the queue and pop until found (only way to do this, inefficient)

    if (FIFOSet::Find(tag, offset)) {
        // Hit
        cout << "Cache Hit\n";
        return 1;
    }
    else if (FIFOSet::set_data.size() == max_size) {
        cout << "Miss\nCache full, Popping queue\n";
        // Remove the first in queue before adding anything else
        FIFOSet::set_data.pop();
        FIFOSet::set_data.push(CacheEntry(tag, offset));
        return 0;
    }
    else {
        // Add the data to the non-full queue
        FIFOSet::set_data.push(CacheEntry(tag, offset));
        cout << "Miss\nAdded reference\n";
        return 0;
    }
}

/*
*  Find whether the value specified is in the queue
*  Checks the index and tag of the reference and compares it to all the references currently loaded
* If both of them match then it returns true
*  Uses a pass by value to copy the given queue variable so the original one stays unmodified.
*/
bool FIFOSet::Find(unsigned long tag, unsigned long offset) {
    // Copy the queue so it is non destructive
    queue<CacheEntry> q = FIFOSet::set_data;

    while (!q.empty()) {

        // We want to interate through each CacheEntry and compare the tags and indexes of each entry
        CacheEntry temp = q.front();

        // compare the tag to the stored tag
        if (temp.getTag() == tag) return 1;
        q.pop();
    }
    return 0;
}