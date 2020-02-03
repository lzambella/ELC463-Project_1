using namespace std;
#include "cache.h"
#include <iostream>

/*
 * Set up the cache by defining its attributes and using that to caculate the total size
*/
Cache::Cache(int L, int K, int N) {
    Cache::hit_count = 0;
    Cache::total = 0;
    Cache::miss_count = 0;
    Cache::L = L;
    Cache::K = K;
    Cache::N = N;
    Cache::cache_size = L* K * N;
    // Initialize each set
    for (int i = 0; i < N; i++) {
        // Create a set with K lines in it
        Cache::set.push_back(CacheSet(K));
    }
}

/*
* Given a reference, load that address into its correct spot in the cache
* Check if the reference exists and return a hit otherwise use LRU to determine 
*/
void Cache::LoadMem(int Addr) {
    
    int set_num = Addr % N; // find set addr goes to
    cout << "Added memory address " << Addr << " to set " << set_num << "\n";
    //create pointer to the object
    CacheSet * temp_set = &Cache::set[set_num];

    // Add the address to the correct set then check if there was a hit or miss
    if (temp_set->AddData(Addr)) 
        Cache::hit_count++; // If hit, add to the hit count
    else
        Cache::miss_count++;
    Cache::total++;
}