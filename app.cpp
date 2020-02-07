#include <fstream>
#include <iostream>
#include <queue>
#include "cache.h"

using namespace std;
// 60k 12-bit words
// the addresses of the trace file are big endian
int main() {
    /*
    const short L = 8; // bytes per line
    short K = 2; // # Lines per set
    short N = 32; // Number of sets
    short cache_size = L*K*N;
    cout << cache_size;
    cout << "\n";

    // Each set maps to a block of standard memory, known as blocks
    // For the first example
    // 1-way set associative is direct mapped cache, each line is mapped to every n-addresses in memory
    // for the first example, every i mod 32 in memory address i maps to the resultant cache block
    // 
    // Load trace
    streampos size;
    char * memblock;
    ifstream file ("TRACE1.DAT", ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [size];
        file.seekg (0, ios::beg);
        file.read (memblock, size);
        file.close();

        cout << "the entire file content is in memory\n";

        cout << size;
        cout << "\n";
    }

     // TODO: Set up cache logic uing set associative cache logic
     // first set up the cache, should have N sets each with K lines per set
     // KN refers to the total number of lines
     int cache[cache_size]; // Cache refs are 3 bytes long, use int as its 4-bytes




     // Load a memory address into the cahce
     */

    /* test Case comment out */
    Cache s = Cache(4, 4, 4, Cache::cache_type::LRU);
    vector<int> data =  {4,8,12,16,4,24,8,20};
    int i = 0;
    for (int val : data) {
        cout << "--------Reference " << i << "------------\n";
        s.LoadMem(val);
        i++;
        cout << "---------------\n\n";
    }
    
    cout << "Results:\n" << "Hits: " << s.hit_count << "\nMisses: " << s.miss_count << "\n";



    return 0;
}

