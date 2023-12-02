#include <vector>
#include <string>
#include "../include/util.h"

std::vector<std::string> split(const std::string& s, char delimeter)
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