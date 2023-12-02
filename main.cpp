#include <iostream>
#include "include/util.h"

int main() {
    std::vector<const char*> vec{"h","i"};
    std::cout << join<std::vector<const char*>, const char*>(vec, "\n");
    return 0;
}
