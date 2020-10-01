#pragma once

#include <atomic>
#include <cstddef>
#include <functional>

template <typename T>
class SharedControlBlock {
public:
    SharedControlBlock(std::function<void(T*)> defDeleter = [](T* ptrToDelete) { delete ptrToDelete; })
        : defaultDeleter(defDeleter) {}

    void incrementSharedRefs() { ++sharedRefs_; }
    void decrementSharedRefs() { --sharedRefs_; }
    size_t getSharedRefs() const { return sharedRefs_.load(); }

    std::function<void(T*)> defaultDeleter;

private:
    std::atomic<size_t> sharedRefs_ = 1;
};
