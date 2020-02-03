#include <queue>
using namespace std;
// Represents a set in cache memory for n-way set cache
// assumes FIFO operation
class CacheSet {
    private:
        queue<int> set_data;    // Cache data in a set_data
        int max_size;           // Max size of the queue, if anything else gets added, then something must be removed
        bool SearchQueue(queue<int>, int&); // Search the queue
    public:
        CacheSet(int);               // Constructor
        CacheSet();
        bool AddData(int);           // Add a memory reference to the set
};