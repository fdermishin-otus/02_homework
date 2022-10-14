#include <iostream>

#include "ipaddress.hpp"
#include "split.hpp"

using AddressList = std::vector<IpAddress>;
constexpr int FIELDS_COUNT = 3;

AddressList read_data() {
    AddressList addresses{};
    std::string line;
    while (std::getline(std::cin, line)) {
        auto fields = split(line, '\t');
        if (fields.size() != FIELDS_COUNT) {
            throw std::runtime_error("Invalid format: wrong number of fields");
        }
        auto address = IpAddress::from_string(line);
        addresses.push_back(address);
    }
    return addresses;
}

void write_data(AddressList &addresses) {
    for (const auto &address: addresses) {
        std::cout << address << '\n';
    }
}

void filter_and_write(const AddressList &addresses, const std::function<bool(const IpAddress &address)> &predicate) {
    AddressList result{};
    std::copy_if(addresses.begin(), addresses.end(), std::back_inserter(result), predicate);
    write_data(result);
}

int main() {
    AddressList addresses = read_data();
    std::sort(addresses.rbegin(), addresses.rend());
    write_data(addresses);
    filter_and_write(addresses, [](const IpAddress &address) {
        return address.starts_with(1);
    });
    filter_and_write(addresses, [](const IpAddress &address) {
        return address.starts_with(46, 70);
    });
    filter_and_write(addresses, [](const IpAddress &address) {
        return address.has_byte(46);
    });
    std::cout.flush();
    return 0;
}
