#pragma once

#include <atomic>
#include <cstddef>

template <typename T>
class SharedControlBlock {
public:
    SharedControlBlock(void defDeleter(T*) = [](T* ptrToDelete) { delete ptrToDelete; })
        : defaultDeleter(defDeleter) {}

    void incrementSharedRefs() { ++sharedRefs_; }
    void decrementSharedRefs() { --sharedRefs_; }
    size_t getSharedRefs() const { return sharedRefs_.load(); }

    void (*defaultDeleter)(T*);

private:
    std::atomic<size_t> sharedRefs_ = 1;
};
