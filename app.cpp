#include <fstream>
#include <iostream>
#include <queue>
#include "cache.h"

using namespace std;

int main() {
    int L = 8;
    int K = 2;
    int N = 32;
    vector<Cache> cachConfigs;
    vector<Cache> lru_configs;
    // FIFO configurations
    cachConfigs.push_back(Cache(L, K, N, Cache::cache_type::FIFO));
    cachConfigs.push_back(Cache(8, 4, 16, Cache::cache_type::FIFO));
    cachConfigs.push_back(Cache(8, 8, 8, Cache::cache_type::FIFO));
    cachConfigs.push_back(Cache(8, 16, 4, Cache::cache_type::FIFO));
    cachConfigs.push_back(Cache(8, 2, 128, Cache::cache_type::FIFO));    
    cachConfigs.push_back(Cache(8, 4, 64, Cache::cache_type::FIFO));
    cachConfigs.push_back(Cache(8, 8, 32, Cache::cache_type::FIFO));
    cachConfigs.push_back(Cache(8, 16, 16, Cache::cache_type::FIFO));

    // LRU configurations
    lru_configs.push_back(Cache(L, K, N, Cache::cache_type::LRU));
    lru_configs.push_back(Cache(8, 4, 16, Cache::cache_type::LRU));
    lru_configs.push_back(Cache(8, 8, 8, Cache::cache_type::LRU));
    lru_configs.push_back(Cache(8, 16, 4, Cache::cache_type::LRU));
    lru_configs.push_back(Cache(8, 2, 128, Cache::cache_type::LRU));    
    lru_configs.push_back(Cache(8, 4, 64, Cache::cache_type::LRU));
    lru_configs.push_back(Cache(8, 8, 32, Cache::cache_type::LRU));
    lru_configs.push_back(Cache(8, 16, 16, Cache::cache_type::LRU));

    streampos size;
    char * memblock;
    ifstream file ("TRACE2.DAT", ios::in|ios::binary|ios::ate);
    cout << "Opening file\n";
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [size];
        file.seekg (0, ios::beg);

        file.read (memblock, size);


        int count = 1;
        printf("FIFO Cache configurations.\n");
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
            printf("------Configuration %d-------\n", count);
            printf("Bytes per Lines: %d\nLines per set: %d\nNumber of sets: %d\nMiss rate: %f\n",c.getBytesPerLine(), c.getLinesPerSet(), c.getNumSets(), (double)c.miss_count / (double)c.total);
            printf("-----------------------------\n\n");
            count++;
        }

        printf("LRU Cache configurations\n");
        count = 0;
        for (Cache c : lru_configs) {
            for (int x = 0; x < size; x+=3){
                long addr = 0;
                // Load the next 3 bytes in reverse order
                for (int i = 2; i >= 0; i--) {
                    addr = addr | (unsigned char)memblock[i+x];
                    if (!(i == 0))
                        addr = addr << 8;
                }
                c.LoadMem(addr);
            }
            printf("------Configuration %d-------\n", count);
            printf("Bytes per Lines: %d\nLines per set: %d\nNumber of sets: %d\nMiss rate: %f\n",c.getBytesPerLine(), c.getLinesPerSet(), c.getNumSets(), (double)c.miss_count / (double)c.total);
            printf("-----------------------------\n\n");
            count++;
        }
        cout << "\n";
        
    }
    return 0;
}

