#pragma once

#include "Set.h"
#include "LRUSet.h"
#include "FIFOSet.h"

#include <vector>
using namespace std;

class Cache {
    private:
        int cache_size; // Total size of the cache
        short L;        // Bytes per line
        short K;        // Lines per set (K-way set associative)
        short N;        // Number of sets
        /** 
         *  Array of sets for n-way cache
         *  Can either use FIFO or LRU operation
         */
        vector <Set*> set;

    public:
        enum cache_type {
            FIFO,
            LRU
        };
        int hit_count;
        int total;
        int miss_count;
        Cache(int, int, int, cache_type);
        void LoadMem (int); // Load from memory into its proper cache location (int MemAddr)
};