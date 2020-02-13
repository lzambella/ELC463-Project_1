using namespace std;
#include "cache.h"
#include <iostream>

/*
 * Set up the cache by defining its attributes and using that to caculate the total size
 * 0000 0000 || 0000 0000 0000 0000 0000 0 (000) these bits are always 0 
 * block offset = Log_2 (Block Size in bytes?) bits
 * index = log_2 (Set Count or N)
 * The remaining bits are used for the tag
 * If the tag matches in a lookup, then there is a hit
 * 
 * 
 * 
*/
Cache::Cache(int L, int K, int N, Cache::cache_type type) {
    Cache::hit_count = 0;
    Cache::total = 0;
    Cache::miss_count = 0;
    Cache::L = L;
    Cache::K = K;
    Cache::N = N;
    Cache::cache_size = L* K * N;
    Cache::set = vector<Set*>();

    Cache::offsetSize = log2(L);
    Cache::indexSize = log2(N);
    Cache::tagSize = 32 - offsetSize - indexSize; // Word size is 32 bits
    // Initialize each set
    for (int i = 0; i < N; i++) {
        // Create a fifo/lru cache with k lines per set
        if (type == cache_type::FIFO)
            Cache::set.push_back(new FIFOSet(K));
        else if (type == cache_type::LRU)
            Cache::set.push_back(new LRUSet(K));
    }
}

/**
 * Load the specified memory address into cache
 */
void Cache::LoadMem(unsigned long addr) {
    
    /*
     * Get the tag, index, and offset from the supplied character address and feed itinto the cache
     */
    
    
    // first divide the reference into its components
    unsigned long offset = Cache::getOffset(addr);
    unsigned long index = Cache::getIndex(addr);
    unsigned long tag = Cache::getTag(addr);

    // attempt to load the values into the cache
    // get the index of the set the address should be added to...
    // this might not be needed as the index is defined by its size
    int set_index = index % N;

    //cout << std::dec << "Index: " << index << " Set_index: " << set_index << "\n";
    
    // get a pointer to that set and add a cacheEntry to it
    Set * ptr = Cache::set[set_index];

    // Add the address to the correct set then check if there was a hit or miss
    if (ptr->AddReference(tag,offset)) 
        Cache::hit_count++; // If hit, add to the hit count
    else
        Cache::miss_count++;
    Cache::total++;

}

unsigned int Cache::getOffset(unsigned long addr) {
    // The offset is the least significant bits
    /*
    *   First make a sequence of bits that are enabled for each offset bit and then AND it with the reference
    */
   // convert char array to long (4 bytes)

   // create offset bits, get set to 1 if that bit is part of the offset
    bitset<32> offsetBits;
    for (int i = 0; i < Cache::offsetSize; i++ ) 
        offsetBits.set(i);

    bitset<32> bitAddr(addr);
    bitset<32> res = offsetBits.operator&=(bitAddr);

    return res.to_ulong();
}

/**
 * Creates a mask of the inde bits and ANDs the address to get the index bits
 * 
 */
unsigned int Cache::getIndex(unsigned long addr) {
    bitset<32> indexBits;
    // Create a bit mask for the index and shift it left by the offset amount (index comes after offset)
    for (int i = 0; i < Cache::indexSize; i++)
        indexBits.set(i);
    indexBits = indexBits.operator<<(Cache::offsetSize);

    // Load the address into its own bit space
    bitset<32> addrBits(addr);

    // apply an AND to the address
    bitset<32> res = addrBits.operator&=(indexBits);

    // shift it right by the offset size so we have the actual value of the bits
    res = res.operator>>=(Cache::offsetSize);

    return res.to_ulong();
}

/**
 * Returns the tag of the given address
 */
unsigned int Cache::getTag(unsigned long addr) {
    bitset<32> tagMask;
    // Create a bit mask for the tag and shift it left by the offset+index amount
    for (int i = 0; i < Cache::tagSize; i++)
        tagMask.set(i);
    tagMask = tagMask.operator<<(Cache::offsetSize + Cache::indexSize);

    // Load address into bitset and AND with mask
    bitset<32> addrBits(addr);
    bitset<32> res = addrBits.operator&=(tagMask);

    // Shift back to end
    res = res.operator>>=(Cache::offsetSize + Cache::indexSize);
    
    return res.to_ullong();
}

// these can be optimized by returning pointers

int Cache::getBytesPerLine() {
    return Cache::L;
}

int Cache::getLinesPerSet() {
    return Cache::K;
}

int Cache::getNumSets() {
    return Cache::N;
}
