#ifndef UTIL_UTIL_H
#define UTIL_UTIL_H

#include <utility>
#include <vector>
#include <concepts>
#include <array>
#include <cstddef>
#include <set>
#include "custom_concepts.h"

/**
 * @brief Generates a std::vector that contains instances of std::pair that holds
 * both values in the given containers at each index.
 *
 * @tparam ContainerOne The type of the first container
 * @tparam ContainerTwo The type of the second container
 * @tparam T The type of element the first container holds
 * @tparam U The type of element the second container holds
 * @param first The first container
 * @param second The second container
 * @return An std::vector of std::pair containing the values of each collection at
 *         each index
 */
template <typename ContainerOne, typename ContainerTwo, typename T, typename U>
requires is_container<ContainerOne> && is_container<ContainerTwo>
std::vector<std::pair<T, U>> zip(ContainerOne first, ContainerTwo second)
{
   std::vector<std::pair<T, U>> zips;
   int last_idx = first.size() > second.size() ? first.size() : second.size();
   int i =  0;
   for (auto first_it = first.begin(), second_it = second.begin(); first_it != first.end()
        && second_it != second.end() && i < last_idx; ++first_it, ++second_it) {
       zips.push_back(std::make_pair(*first_it, *second_it));
       ++i;
   }
}

/**
 * @brief Generates a std::vector containing instances of std::pair that hold
 * the element and the element's index for each element in the container.
 *
 * @tparam Container The type of the container
 * @tparam T The type of elements that the container holds
 * @param c The container
 * @return An std::vector of the instances of std::pair
 */
template <typename Container, typename T>
requires is_container<Container>
std::vector<std::pair<int, T>> enumerate(Container c)
{
    int i = 0;
    std::vector<std::pair<int, T>> enumerated;
    for (auto it = c.begin(); it != c.end(); ++it) {
        enumerated.push_back(std::make_pair(i++, *it));
    }
    return enumerated;
}

/**
 * @brief Splits a std::string based on the given delimeter into an std::vector
 * of std::string.
 *
 * @param s The string to split
 * @param delimeter The delimeter
 * @return An std::vector of strings that are separated from one another by delimeter
 */
std::vector<std::string> split(const std::string& s, char delimeter = ' ')
{
    /* TODO: make this work with delimeter as std::string */
    std::vector<std::string> splits{};
    std::string curr_str;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == delimeter) {
            if (!curr_str.empty()) {
                splits.push_back(curr_str);
            }
            curr_str = "";
            continue;
        }
        curr_str += s[i];
        if (i == s.size() - 1 && !curr_str.empty()) {
            splits.push_back(curr_str);
        }
    }
    return splits;
}

template <typename Collection, typename T>
requires is_container<Collection>
std::vector<T> list_comprehension(Collection c)
{
    std::vector<T> vec{};
    for (T o : c) {
        vec.push_back(o);
    }
    return vec;
}

template <typename Collection, typename T, typename Predicate>
requires is_container<Collection> && std::predicate<Predicate, T>
std::vector<T> list_comprehension(Collection c, Predicate pred)
{
    std::vector<T> vec{};
    for (T o : c) {
        if (pred(o)) {
            vec.push_back(o);
        }
    }
    return vec;
}

template <typename Collection, typename T>
requires is_container<Collection>
std::set<T> set_comprehension(Collection c)
{
    std::set<T> s;
    for (T o : c) {
        s.insert(o);
    }
    return s;
}

template <typename Collection, typename T, typename Predicate>
requires is_container<Collection> && std::predicate<Predicate, T>
std::set<T> set_comprehension(Collection c, Predicate pred)
{
    std::set<T> s;
    for (T o : c) {
        if (pred(o)) {
            s.insert(o);
        }
    }
    return s;
}

#endif