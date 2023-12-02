#ifndef UTIL_UTIL_H
#define UTIL_UTIL_H

#include <utility>
#include <vector>
#include <concepts>
#include <array>
#include <cstddef>
#include <set>
#include <string>
#include <stdexcept>
#include "custom_concepts.h"

/**
 * @brief Generates a <code>std::vector</code> that contains instances of <code>std::pair</code> that holds
 * both values in the given containers at each index.
 *
 * @tparam ContainerOne The type of the first container
 * @tparam ContainerTwo The type of the second container
 * @tparam T The type of element the first container holds
 * @tparam U The type of element the second container holds
 * @param first The first container
 * @param second The second container
 * @return An <code>std::vector</code> of <code>std::pair</code> containing the values of each container at
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
 * @brief Generates a <code>std::vector</code> containing instances of <code>std::pair</code> that hold
 * the element and the element's index for each element in the container.
 *
 * @tparam Container The type of the container
 * @tparam T The type of elements that the container holds
 * @param c The container
 * @return An <code>std::vector</code> of the instances of <code>std::pair</code>
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
 * @brief Splits a <code>std::string</code> based on the given delimeter into an <code>std::vector</code.
 * of std::string.
 *
 * @param s The string to split
 * @param delimeter The delimeter
 * @return An <code>std::vector</code> of strings that are separated from one another by delimeter
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

/**
 * @brief Creates an <code>std::vector</code> from the given container.
 *
 * @tparam Container The type of the given Container
 * @tparam T The type of elements the given Container contains
 * @param c The Container
 * @return An std::vector containing the elements of <code>c</code>
 */
template <typename Container, typename T>
requires is_container<Container>
std::vector<T> list_comprehension(Container c)
{
    std::vector<T> vec{};
    for (T o : c) {
        vec.push_back(o);
    }
    return vec;
}

/**
 * @brief Creates an <code>std::vector</code> containing the elements of <code>c</code>
 * that pass the given predicate <code>pred</code>.
 *
 * @tparam Container The type of the given Container
 * @tparam T The type of elements the given Container contains
 * @tparam Pred The type of the given predicate
 * @param c The Container
 * @param pred The predicate
 * @return An std::vector containing the elements of <code>c</code>
 */
template <typename Container, typename T, typename Predicate>
requires is_container<Container> && std::predicate<Predicate, T>
std::vector<T> list_comprehension(Container c, Predicate pred)
{
    std::vector<T> vec{};
    for (T o : c) {
        if (pred(o)) {
            vec.push_back(o);
        }
    }
    return vec;
}

/**
 * @brief Creates an <code>std::set</code> from the given container.
 *
 * @tparam Container The type of the given Container
 * @tparam T The type of elements the given Container contains
 * @param c The Container
 * @return An std::set containing the elements of <code>c</code>
 */
template <typename Container, typename T>
requires is_container<Container>
std::set<T> set_comprehension(Container c)
{
    std::set<T> s;
    for (T o : c) {
        s.insert(o);
    }
    return s;
}

/**
 * @brief Creates an <code>std::set</code> containing the element of <code>c</code>
 * that pass the predicate <code>pred</code>
 *
 * @tparam Container The type of the given Container
 * @tparam T The type of elements the given Container contains
 * @tparam Predicate The type of the given predicate
 * @param c The Container
 * @param pred The predicate
 * @return An std::set containing the elements of <code>c</code>
 */
template <typename Container, typename T, typename Predicate>
requires is_container<Container> && std::predicate<Predicate, T>
std::set<T> set_comprehension(Container c, Predicate pred)
{
    std::set<T> s;
    for (T o : c) {
        if (pred(o)) {
            s.insert(o);
        }
    }
    return s;
}

/**
 * @brief Converts the given collection into an <code>std::string</code> with its
 * tokens separated by delimeter.
 *
 * @tparam Container The type of the given container
 * @tparam T The type of the elements that <code>c</code> contains
 * @param c The container
 * @param delimeter The std::string to separate each element of <code>c</code> with
 * @return
 */
template <typename Container, typename T>
requires is_container<Container> && std::convertible_to<T, std::string>
std::string join(Container c, const std::string& delimeter = " ")
{
    std::string joined_str{};
    for (auto [idx, chunk] : enumerate<Container, T>(c)) {
        joined_str += static_cast<std::string>(chunk);
        if (idx < c.size() - 1) {
            joined_str += delimeter;
        }
    }
    return joined_str;
}

#endif