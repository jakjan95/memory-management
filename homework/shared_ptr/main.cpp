#include "shared_ptr.hpp"

int main() {
    cs::shared_ptr<int> ptr(new int{5});
    auto ptr2(ptr);
    cs::shared_ptr<int> ptr3(new int{5});
    ptr3 = ptr;
    auto ptr4(std::move(ptr));
    cs::shared_ptr<int> ptr5(new int{5});
    ptr5 = std::move(ptr3);

    return 0;
}
