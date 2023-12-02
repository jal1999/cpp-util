#ifndef UTIL_CUSTOM_CONCEPTS_H
#define UTIL_CUSTOM_CONCEPTS_H

#include <concepts>

template <typename T>
concept is_container = requires (T o) {
    o.begin();
    o.end();
    o.size();
};

#endif
