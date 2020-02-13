#include "cache_entry.h"

using namespace std;

/**
 * @param refAddr Reference Address
 * @param tag the tag of the reference
 * @param index the idnex of the reference
 * @param offset the offset of the address, always zero since we dont bring in "buddies" for this sim
 */
CacheEntry::CacheEntry(long tag, long offset) {
    CacheEntry::tag = tag;
    CacheEntry::offset = offset;
}

/**
 * Gets the tag as a byte array
 */
long CacheEntry::getTag() {
    return CacheEntry::tag;
}


long CacheEntry::getOffset() {
    return CacheEntry::offset;
}