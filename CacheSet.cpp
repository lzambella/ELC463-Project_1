#include <queue>
#include "CacheSet.h"
#include <iostream>
using namespace std;

// constructor
CacheSet::CacheSet(int max_size) {
    CacheSet::max_size = max_size;
    CacheSet::set_data = queue<int>();
}

CacheSet::CacheSet() {
    CacheSet::max_size = 2;
    CacheSet::set_data = queue<int>();
}

// Add a reference to the queue
// Returns true for a hit, false for a miss
bool CacheSet::AddData(int mem_addr) {
    // Check if the mem addr is already in the cache 
    // Clone the queue and pop until found (only way to do this, inefficient)
    if (SearchQueue(set_data, mem_addr)) {
        // Hit
        cout << "Cache Hit\n";
        return 1;
    }
    else if (CacheSet::set_data.size() == max_size) {
        cout << "Miss\nCache full, Popping queue\n";
        // Remove the first in queue before adding anything else
        set_data.pop();
        set_data.push(mem_addr);
        return 0;
    }
    else {
        // Add the data to the non-full queue
        set_data.push(mem_addr);
        cout << "Miss\nAdded reference\n";
        return 0;
    }
}

/*
*  Find whether the value specified is in the queue
*  Uses a pass by value to copy the given queue variable so the original one stays unmodified.
*/
bool CacheSet::SearchQueue(queue<int> q, int &val) {
    while (!q.empty()) {
        int temp = q.front();
        if (temp == val) return 1;
        q.pop();
    }
    return 0;
}