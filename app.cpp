#include <fstream>
#include <iostream>
#include <queue>
#include "cache.h"

using namespace std;

// 60k 12-bit words
// the addresses of the trace file are big endian
int main() {
    /*
    // Each set maps to a block of standard memory, known as blocks
    // For the first example
    // 1-way set associative is direct mapped cache, each line is mapped to every n-addresses in memory
    // for the first example, every i mod 32 in memory address i maps to the resultant cache block
    // 
    // Load trace


     // TODO: Set up cache logic uing set associative cache logic
     // first set up the cache, should have N sets each with K lines per set
     // KN refers to the total number of lines

     */

    /*
    cout << "Results:\n" << "Hits: " << s.hit_count << "\nMisses: " << s.miss_count << "\n";
    */

    // allocate 4 bytes of memory
    /*
    unsigned char test[9] = {0x10, 0xBA, 0xCB, 0xAA, 0x45, 0x00, 0x10, 0xBA, 0xCB};

    // parse address from char array, get every 3 bytes
    long addr = 0;
    for (int x = 0; x < sizeof(test); x+=3) {
        addr = 0;
        // Load the next 3 bytes in reverse order
        for (int i = 2; i >= 0; i--) {
            addr = addr | test[i+x];
            if (!(i == 0))
                addr = addr << 8;
        }
        cout << "Full address: " << std::hex << addr << "\n";
        s.LoadMem(addr);
    }
    */
    int L = 8;
    int K = 2;
    int N = 32;
    vector<Cache> cachConfigs;
    cachConfigs.push_back(Cache(L, K, N, Cache::cache_type::FIFO));
    cachConfigs.push_back(Cache(8, 4, 16, Cache::cache_type::FIFO));
    cachConfigs.push_back(Cache(8, 8, 8, Cache::cache_type::FIFO));
    cachConfigs.push_back(Cache(8, 16, 4, Cache::cache_type::FIFO));

    streampos size;
    char * memblock;
    ifstream file ("TRACE1.DAT", ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [size];
        file.seekg (0, ios::beg);

        file.read (memblock, size);



        for (Cache c : cachConfigs) {
            for (int x = 0; x < size; x+=3){
                long addr = 0;
                // Load the next 3 bytes in reverse order
                for (int i = 2; i >= 0; i--) {
                    addr = addr | (unsigned char)memblock[i+x];
                    if (!(i == 0))
                        addr = addr << 8;
                }
                //cout << "Full address: " << std::hex << addr << "\n";
                c.LoadMem(addr);
            }
            printf("Bytes per Lines: %d\nLines per set: %d\nNumber of sets: %d\nMiss rate: %f\n\n",c.getBytesPerLine(), c.getLinesPerSet(), c.getNumSets(), (double)c.miss_count / (double)c.total);
        }
        cout << "\n";
        delete[] memblock;
    }
    return 0;
}

