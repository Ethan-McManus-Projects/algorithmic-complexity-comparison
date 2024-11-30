#ifndef MEMORY_TRACKER_H
#define MEMORY_TRACKER_H

#include <cstdlib>
#include <iostream>
#include <mutex>

class MemoryTracker {
private:
    inline static size_t totalMemory = 0;
    inline static size_t peakMemory = 0;
    inline static std::mutex memMutex;

public:
    // Function to allocate memory and track it
    static void* allocate(size_t size) {
        std::lock_guard<std::mutex> lock(memMutex);
        totalMemory += size;
        peakMemory = std::max(peakMemory, totalMemory);
        return std::malloc(size);
    }

    // Function to deallocate memory and update the tracker
    static void deallocate(void* ptr, size_t size) {
        std::lock_guard<std::mutex> lock(memMutex);
        totalMemory -= size;
        std::free(ptr);
    }

    // Reset memory tracking
    static void reset() {
        std::lock_guard<std::mutex> lock(memMutex);
        totalMemory = 0;
        peakMemory = 0;
    }

    // Get the current peak memory usage
    static size_t getPeakMemoryUsage() {
        std::lock_guard<std::mutex> lock(memMutex);
        return peakMemory;
    }
};

#endif
