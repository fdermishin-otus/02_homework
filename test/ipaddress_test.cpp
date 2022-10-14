#include <gtest/gtest.h>

#include "ipaddress.hpp"

TEST(IpAddressTest, ParseValid) {
    EXPECT_NO_THROW(IpAddress::from_string("1.2.3.4"));
}

TEST(IpAddressTest, ParseInvalidDelimiter) {
    EXPECT_THROW(IpAddress::from_string("1.2.3,4"), std::exception);
}

TEST(IpAddressTest, ParseMissingByte) {
    EXPECT_THROW(IpAddress::from_string("1.2.3."), std::exception);
}

TEST(IpAddressTest, ParseExtraDelimiter) {
    EXPECT_THROW(IpAddress::from_string("1.2.3.4."), std::exception);
}

TEST(IpAddressTest, ParseExtraByte) {
    EXPECT_THROW(IpAddress::from_string("1.2.3.4.5"), std::exception);
}

TEST(IpAddressTest, ParseOutOfRange) {
    EXPECT_THROW(IpAddress::from_string("256.256.256.256"), std::exception);
}

TEST(IpAddressTest, ParseNegativeBytes) {
    EXPECT_THROW(IpAddress::from_string("1.2.3.-1"), std::exception);
}

TEST(IpAddressTest, ParseInvalidSymbols) {
    EXPECT_THROW(IpAddress::from_string("1.2.3.q"), std::exception);
}

TEST(IpAddressTest, OutputAddress) {
    auto address = IpAddress::from_string("1.2.3.4");
    std::ostringstream oss;
    oss << address;
    EXPECT_EQ(oss.str(), "1.2.3.4");
}

TEST(IpAddressTest, CompareAddressLastDigit) {
    auto address1 = IpAddress::from_string("1.2.3.4");
    auto address2 = IpAddress::from_string("1.2.3.5");
    EXPECT_LT(address1, address2);
}

TEST(IpAddressTest, CompareAddressByteValues) {
    auto address1 = IpAddress::from_string("1.2.3.4");
    auto address2 = IpAddress::from_string("1.10.3.4");
    EXPECT_LT(address1, address2);
}

TEST(IpAddressTest, StartsWithOne) {
    auto address = IpAddress::from_string("1.2.3.4");
    EXPECT_TRUE(address.starts_with(1));
}

TEST(IpAddressTest, NotStartsWithOne) {
    auto address = IpAddress::from_string("1.2.3.4");
    EXPECT_FALSE(address.starts_with(2));
}

TEST(IpAddressTest, StartsWithAll) {
    auto address = IpAddress::from_string("1.2.3.4");
    EXPECT_TRUE(address.starts_with(1, 2, 3, 4));
}

TEST(IpAddressTest, NotStartsWithAll) {
    auto address = IpAddress::from_string("1.2.3.4");
    EXPECT_FALSE(address.starts_with(1, 2, 3, 5));
}

TEST(IpAddressTest, HasByte) {
    auto address = IpAddress::from_string("1.2.3.4");
    EXPECT_TRUE(address.has_byte(2));
}

TEST(IpAddressTest, NotHasByte) {
    auto address = IpAddress::from_string("1.2.3.4");
    EXPECT_FALSE(address.has_byte(5));
}
