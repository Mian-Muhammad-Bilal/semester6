#include <iostream>
using namespace std;

// Enum to represent cache states
enum CacheState
{
    INVALID,
    SHARED,
    EXCLUSIVE,
    MODIFIED
};

// Global variables representing cache state and data
int cacheData = 0;
CacheState cacheState = INVALID;

void readFromMemory()
{
    // Simulate reading from main memory
    cacheData = 100;        // Example initial data
    cacheState = EXCLUSIVE; // Initially in EXCLUSIVE state
    cout << "Read from memory (EXCLUSIVE)" << endl;
}

void readFromCache()
{
    // Simulate reading from cache
    if (cacheState == INVALID)
    {
        readFromMemory();
    }
    else
    {
        cout << "Read from cache ";
        switch (cacheState)
        {
        case SHARED:
            cout << "(SHARED)" << endl;
            break;
        case EXCLUSIVE:
            cout << "(EXCLUSIVE)" << endl;
            break;
        case MODIFIED:
            cout << "(MODIFIED)" << endl;
            break;
        }
    }
}

void writeToMemory(int newData)
{
    // Simulate writing to main memory
    cacheData = newData;
    cacheState = EXCLUSIVE; // Move to EXCLUSIVE state
    cout << "Write to memory (EXCLUSIVE)" << endl;
}

void writeToCache(int newData)
{
    // Simulate writing to cache
    if (cacheState == INVALID)
    {
        writeToMemory(newData);
    }
    else
    {
        cacheData = newData;
        switch (cacheState)
        {
        case SHARED:
            cacheState = MODIFIED; // Move to MODIFIED state
            cout << "Write to cache (MODIFIED)" << endl;
            break;
        case EXCLUSIVE:
            cacheState = MODIFIED; // Move to MODIFIED state
            cout << "Write to cache (MODIFIED)" << endl;
            break;
        case MODIFIED:
            cout << "Write to cache (MODIFIED)" << endl;
            break;
        }
    }
}

void invalidateCache()
{
    cacheState = INVALID;
    cout << "Cache invalidated" << endl;
}

void printCacheState()
{
    cout << "Cache State: ";
    switch (cacheState)
    {
    case INVALID:
        cout << "INVALID" << endl;
        break;
    case SHARED:
        cout << "SHARED" << endl;
        break;
    case EXCLUSIVE:
        cout << "EXCLUSIVE" << endl;
        break;
    case MODIFIED:
        cout << "MODIFIED" << endl;
        break;
    }
}

int main()
{
    // Simulating cache operations
    readFromCache();   // Cache miss, fetch from memory (EXCLUSIVE)
    printCacheState(); // EXCLUSIVE

    writeToCache(200);
    printCacheState(); // MODIFIED

    readFromCache();   // Cache hit, read from cache (MODIFIED)
    printCacheState(); // MODIFIED

    invalidateCache();
    printCacheState(); // INVALID

    readFromCache();   // Cache miss, fetch from memory (EXCLUSIVE)
    printCacheState(); // EXCLUSIVE

    return 0;
}
