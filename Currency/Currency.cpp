#include "Currency.h"

Currency::Currency(unsigned long long zl, int gr)
{
    if (gr >= 100)
        throw std::invalid_argument("Gr value cannot be grater than 100");
    this->gr = gr;
    this->zl = zl;
}

void Currency::operator+=(Currency const& value) noexcept
{
    this->zl += (value.zl + (this->gr + value.gr) / 100);
    this->gr = (this->gr + value.gr) % 100;
}

void Currency::operator-=(Currency const& value)
{
    if (*this < value)
        throw std::invalid_argument("Cannot subtract grater value");
    if (this->gr < value.gr)
    {
        this->zl -= 1;
        this->gr += 100;
    }
    this->zl -= value.zl;
    this->gr -= value.gr;
}

Currency Currency::operator+(Currency const& value) const noexcept
{
    Currency a = *this;
    a += value;
    return a;
}

Currency Currency::operator-(Currency const& value) const noexcept
{
    Currency a = *this;
    a -= value;
    return a;
}

bool Currency::operator<=(Currency const& value) const noexcept
{
    return (*this < value || *this == value);
}

bool Currency::operator>=(Currency const& value) const noexcept
{
    return (*this > value || *this == value);
}

bool Currency::operator==(Currency const& value) const noexcept
{
    return (this->zl == value.zl && this->gr == value.gr);
}

bool Currency::operator!=(Currency const& value) const noexcept
{
    return !(*this == value);
}

bool Currency::operator<(Currency const& value) const noexcept
{
    return (this->zl < value.zl || (this->zl == value.zl && this->gr < value.gr));
}

bool Currency::operator>(Currency const& value) const noexcept
{
    return (this->zl > value.zl || (this->zl == value.zl && this->gr > value.gr));
}

Currency Currency::operator*(float const& x) const noexcept
{
    Currency a;
    unsigned long long grosze = gr + zl * 100;
    grosze *= x;
    a.zl = grosze / 100;
    a.gr = grosze % 100;
    return a;
}

ostream& operator<<(ostream& os, Currency& currency) noexcept
{
    os << currency.zl << " zl " << int(currency.gr) << " gr";
    return os;
}
