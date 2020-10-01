#include <iostream>

#include "shared_ptr.hpp"
namespace cs {

template <typename T>
class weak_ptr {
public:
    constexpr weak_ptr() noexcept;
    weak_ptr(const weak_ptr& r) noexcept;
    weak_ptr(const std::shared_ptr<T>& r) noexcept;
    weak_ptr(weak_ptr&& r) noexcept;

    weak_ptr& operator=(const weak_ptr& r) noexcept;
    weak_ptr& operator=(weak_ptr&& r) noexcept;

    bool expired() const noexcept;

    long use_count() const noexcept;

    cs::shared_ptr<T> lock() const noexcept;

    void reset() noexcept;

private:
    T* ptr_ = nullptr;
};
}  // namespace cs
