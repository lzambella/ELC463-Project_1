#pragma once

#include <queue>
#include <vector>

using namespace std;

/**
 *  Abstract class representing a cache set
 */
class Set {
    private:
        virtual bool Find(unsigned long, unsigned long) = 0;
    public:
        virtual bool AddReference(unsigned long, unsigned long) = 0;
};