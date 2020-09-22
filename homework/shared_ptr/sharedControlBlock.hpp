#pragma once

#include <atomic>
#include <cstddef>

class SharedControlBlock {
public:
    SharedControlBlock(size_t sharedRefs = 1)
        : sharedRefs_(sharedRefs) {}

    void incrementSharedRefs() { ++sharedRefs_; }
    void decrementSharedRefs() { --sharedRefs_; }
    size_t getSharedRefs() const { return sharedRefs_.load(); }

private:
    std::atomic<size_t> sharedRefs_;
};
