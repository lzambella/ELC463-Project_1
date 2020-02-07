#include <queue>
#include "FIFOSet.h"
#include <iostream>
using namespace std;

// constructor
FIFOSet::FIFOSet(int max_size) {
    FIFOSet::max_size = max_size;
    FIFOSet::set_data = queue<int>();
}

FIFOSet::FIFOSet() {
    FIFOSet::max_size = 2;
    FIFOSet::set_data = queue<int>();
}

// Add a reference to the queue
// Returns true for a hit, false for a miss
bool FIFOSet::AddReference(int & mem_addr) {
    // Check if the mem addr is already in the cache 
    // Clone the queue and pop until found (only way to do this, inefficient)
    if (FIFOSet::Find(mem_addr)) {
        // Hit
        cout << "Cache Hit\n";
        return 1;
    }
    else if (FIFOSet::set_data.size() == max_size) {
        cout << "Miss\nCache full, Popping queue\n";
        // Remove the first in queue before adding anything else
        FIFOSet::set_data.pop();
        FIFOSet::set_data.push(mem_addr);
        return 0;
    }
    else {
        // Add the data to the non-full queue
        FIFOSet::set_data.push(mem_addr);
        cout << "Miss\nAdded reference\n";
        return 0;
    }
}

/*
*  Find whether the value specified is in the queue
*  Uses a pass by value to copy the given queue variable so the original one stays unmodified.
*/
bool FIFOSet::Find(int &val) {
    // Copy the queue so it is non destructive
    queue<int> q = FIFOSet::set_data;
    while (!q.empty()) {
        int temp = q.front();
        if (temp == val) return 1;
        q.pop();
    }
    return 0;
}