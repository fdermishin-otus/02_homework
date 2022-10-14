#include "split.hpp"

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> result{};
    std::string::size_type prev = 0;
    for (std::string::size_type cur = 0; cur < str.length(); ++cur) {
        if (str[cur] == delimiter) {
            result.emplace_back(str, prev, cur - prev);
            prev = cur + 1;
        }
    }
    result.emplace_back(str, prev, str.length() - prev);
    return result;
}
