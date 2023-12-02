#include <iostream>
#include "util.h"

int main() {
    std::string s = "HixmyxnamexisxJamesxhixxxxxx";
    auto x = list_comprehension<std::string, char>(s, [](char c){ return c != 'x'; });
    for (auto xx : x) {
        std::cout << xx << "\n";
    }
    return 0;
}
