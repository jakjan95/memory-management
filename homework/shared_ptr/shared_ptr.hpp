#pragma once

#include "sharedControlBlock.hpp"

namespace cs {
template <typename T>
class shared_ptr {
public:
    constexpr shared_ptr() noexcept = default;
    constexpr shared_ptr(std::nullptr_t) noexcept {}
    explicit shared_ptr(T* ptr)
        : ptr_(ptr), controlBlock_(new SharedControlBlock{}) {}

    shared_ptr(const shared_ptr& other) noexcept;
    shared_ptr(shared_ptr&& other) noexcept;
    ~shared_ptr();

    shared_ptr& operator=(const shared_ptr& other) noexcept;
    shared_ptr& operator=(shared_ptr&& other) noexcept;

    T& operator*() const noexcept { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }

    T* get() const noexcept { return ptr_; }

private:
    T* ptr_ = nullptr;
    SharedControlBlock* controlBlock_ = nullptr;
};

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& other) noexcept {
    ptr_ = other.ptr_;
    other.controlBlock_->incrementSharedRefs();
    controlBlock_ = other.controlBlock_;
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& other) noexcept {
    ptr_ = other.ptr_;
    controlBlock_ = other.controlBlock_;
    other.ptr_ = nullptr;
    other.controlBlock_ = nullptr;
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    if (controlBlock_) {
        if (controlBlock_->getSharedRefs() == 1) {
            delete ptr_;
            delete controlBlock_;
        } else {
            controlBlock_->decrementSharedRefs();
        }
    }
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& other) noexcept {
    if (controlBlock_) {
        if (controlBlock_->getSharedRefs() == 1) {
            delete ptr_;
            delete controlBlock_;
        } else {
            controlBlock_->decrementSharedRefs();
        }
    }

    ptr_ = other.ptr_;
    other.controlBlock_->incrementSharedRefs();
    controlBlock_ = other.controlBlock_;
    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& other) noexcept {
    if (controlBlock_) {
        if (controlBlock_->getSharedRefs() == 1) {
            delete ptr_;
            delete controlBlock_;
        } else {
            controlBlock_->decrementSharedRefs();
        }
    }

    ptr_ = other.ptr_;
    controlBlock_ = other.controlBlock_;
    other.ptr_ = nullptr;
    other.controlBlock_ = nullptr;
    return *this;
}

}  // namespace cs
