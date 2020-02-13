#pragma once

#include "Set.h"
#include "LRUSet.h"
#include "FIFOSet.h"

#include <vector>
#include <math.h>
#include <bitset>
#include <unordered_map>

using namespace std;

class Cache {
    private:
        int cache_size; // Total size of the cache
        short L;        // Bytes per line (size of each line)
        short K;        // Lines per set (K-way set associative)
        short N;        // Number of sets
        /** 
         *  Array of sets for n-way cache
         *  Can either use FIFO or LRU operation
         */
        vector <Set*> set;

        short tagSize;     //size of tag in bits
        short indexSize;   // size of index in bits
        short offsetSize;  // size of offset in bits (usually 3)

        unsigned int getOffset(unsigned long);
        unsigned int getIndex(unsigned long);
        unsigned int getTag(unsigned long);
        
    public:
        enum cache_type {
            FIFO,
            LRU
        };
        int hit_count;
        int total;
        int miss_count;
        Cache(int, int, int, cache_type);
        //void LoadMem (int); // Load from memory into its proper cache location (int MemAddr)
        void LoadMem(unsigned long); // add mem ref to cache

        int getBytesPerLine();
        int getLinesPerSet();
        int getNumSets();

        cache_type getType();
};