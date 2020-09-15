#include <iostream>
#include "FileHandler.hpp"

int main() {
    try {
        FileHandler fh{"./ResourceD.cpp"};
        std::cout << fh;
    } catch (FileOpenError& foe) {
        std::cerr << foe.what() << '\n';
    } catch (std::runtime_error& re) {
        std::cerr << re.what() << '\n';
    }
    return 0;
}
