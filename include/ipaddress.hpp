#pragma once

#include <array>
#include <limits>

#include "split.hpp"

class IpAddress {

public:
    IpAddress() = delete;

    static IpAddress from_string(const std::string &line) {
        auto bytes = split(line, DELIMITER);
        return IpAddress(bytes);
    }

    bool operator<(const IpAddress &other) const {
        return data_ < other.data_;
    }

    friend std::ostream &operator<<(std::ostream &os, const IpAddress &address) {
        static_assert(BYTES > 0);
        auto back_it = std::prev(address.data_.cend());
        for (auto it = address.data_.cbegin(); it != address.data_.cend(); ++it) {
            os << static_cast<int>(*it); // prevent interpreting the byte as character
            if (it != back_it) {
                os << ".";
            }
        }
        return os;
    }

    template<typename... Args>
    bool starts_with(Args... args) const {
        static_assert(sizeof...(Args) <= BYTES);
        return starts_with_(std::make_index_sequence<sizeof...(Args)>(), args...);
    }

    bool has_byte(uint8_t query) const {
        return has_byte_(query, std::make_index_sequence<BYTES>());
    }

private:
    static constexpr int BYTES = 4;
    static constexpr char DELIMITER = '.';
    using DataType = std::array<uint8_t, BYTES>;
    static constexpr auto MAX_BYTE_VALUE = std::numeric_limits<DataType::value_type>::max();

    DataType data_;

    explicit IpAddress(const std::vector<std::string> &data) : data_{} {
        if (data.size() != BYTES) {
            throw std::runtime_error("Invalid number of bytes");
        }
        std::transform(data.cbegin(), data.cend(), data_.begin(), [](const std::string &s) {
            auto value = std::stoi(s);
            if (value < 0 || value > MAX_BYTE_VALUE) {
                throw std::runtime_error("Invalid byte value");
            }
            return static_cast<uint8_t>(value);
        });
    }

    template<std::size_t... Is, typename... Args>
    bool starts_with_(std::index_sequence<Is...>, Args... args) const {
        return ((data_[Is] == args) && ...);
    }

    template<std::size_t... Is>
    bool has_byte_(uint8_t byte, std::index_sequence<Is...>) const {
        return ((data_[Is] == byte) || ...);
    }
};
