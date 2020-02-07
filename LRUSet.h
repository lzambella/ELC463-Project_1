/**
 * Cache set following the LRU policy
 * In an n-way set associative cache, there will be n amount of these sets in an array of some kind
 * The class uses a vector to determine the oldest by pushing the hit reference to the back of the queue
 * When there's a miss, the front of the queue gets popped
 */
#pragma once

#include <vector>
#include "Set.h"

using namespace std;
class LRUSet: public Set {
    private:
        // queue that fills with references
        vector<int> data;
        // Max size of the queue
        short max_size;
        /**
         * Search the queue for a specified value
         */
        bool Find(int&);
    public:
        /**
         * Create a new LruSet object
         * @param set_size number of lines of data in the set
         */
        LRUSet(int&);
        bool AddReference(int&);
};