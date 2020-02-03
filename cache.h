#include "CacheSet.h"
#include <vector>
using namespace std;

class Cache {
    private:
        int cache_size; // Total size of the cache
        short L;        // Bytes per line
        short K;        // Lines per set (K-way set associative)
        short N;        // Number of sets
        vector <CacheSet> set;// Array of sets for n-way cache
    public:
        int hit_count;
        int total;
        int miss_count;
        Cache(int, int, int); // Class constructor
        void LoadMem (int); // Load from memory into its proper cache location (int MemAddr)
};