#pragma once
#include <iostream>

using namespace std;

struct Currency
{
    unsigned long long zl;
    int gr;
    explicit Currency(unsigned long long zl = 0, int gr = 0);
    void operator+=(Currency const& value) noexcept;
    void operator-=(Currency const& value);
    Currency operator+(Currency const& value) const noexcept;
    Currency operator-(Currency const& value) const noexcept;
    bool operator<=(Currency const& value) const noexcept;
    bool operator>=(Currency const& value) const noexcept;
    bool operator==(Currency const& value) const noexcept;
    bool operator!=(Currency const& value) const noexcept;
    bool operator<(Currency const& value) const noexcept;
    bool operator>(Currency const& value) const noexcept;
    Currency operator*(float const& x) const noexcept;
    friend ostream& operator<<(ostream& os, Currency& currency) noexcept;
};
