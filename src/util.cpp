#include <vector>
#include <string>
#include "../include/util.h"

std::vector<std::string> util::split(const std::string &s, const std::string& delim) {
    std::vector<std::string> splits{};
    std::vector<std::size_t> start_idxs{};
    std::size_t next_idx{ 0 };
    std::size_t curr_idx{ 0 };
    while ((next_idx = s.find(delim, curr_idx)) != -1) {
        start_idxs.push_back(next_idx);
        curr_idx = next_idx + delim.size();
    }
    std::string first = s.substr(0, start_idxs[0]);
    if (!first.empty()) {
        splits.push_back(first);
    }
    for (int i = 0; i < start_idxs.size(); ++i) {
        std::string sub = s.substr(start_idxs[i] + delim.size(),
                                   start_idxs[i + 1] - start_idxs[i] - delim.size());
        if (!sub.empty()) {
            splits.push_back(sub);
        }
    }
    return splits;
}