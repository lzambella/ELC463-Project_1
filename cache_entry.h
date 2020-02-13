#pragma once

using namespace std;

/*
* Describes an entry in a cache set with information such as the tag, offset, and index
* offset should always be 0 for our purpose
* Does not include actual memory data as its a hit/miss sim only
*/
class CacheEntry {
    private:
        long tag;
        long offset;

    public:
        CacheEntry(long, long);
        long getTag();
        long getOffset();
};