#pragma once

#include <queue>
#include <vector>

using namespace std;

/**
 *  Abstract class representing a cache set
 */
class Set {
    private:
        virtual bool Find(int &) = 0;
    public:
        virtual bool AddReference(int &) = 0;
};