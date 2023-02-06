#include "Company.h"
#include "Tax.h"


Company::Company(Office& office, string name, vector<Invoice>& incomes, vector<Invoice>& expenses, Enterprise enterprise) {
    this->name = name;
    this->incomes = incomes;
    this->expenses = expenses;
    this->enterprise = enterprise;
    office.addCompany(*this);
}

string Company::getName() const noexcept
{
    return name;
}

Enterprise Company::getEnterprise() const noexcept
{
    return enterprise;
}

vector<Invoice> Company::getIncomes() const noexcept
{
    return incomes;
}

vector<Invoice> Company::getExpenses() const noexcept
{
    return expenses;
}

Currency Company::sumOfIncomes() const noexcept
{
    Currency sum;
    for (auto invoice : incomes)
        sum += invoice.getNetAmount();
    return sum;
}

Currency Company::sumOfExpenses() const noexcept
{
    Currency sum;
    for (auto invoice : expenses)
        sum += invoice.getNetAmount();
    return sum;
}

Currency Company::calculateTaxes(Office& office) const noexcept
{
    Currency sum;
    for (auto elem : office.getSupportedTaxes())
        sum += elem->calculate(*this);
    sum += calculateVat();
    return sum;
}

Currency Company::calculateVat() const noexcept
{
    Currency sum;
    for (auto invoice : incomes) {
        sum += invoice.calculateVat();
    }

    for (auto invoice : expenses) {
        try {
            sum -= invoice.calculateVat();
        }
        catch (invalid_argument) {
            return Currency();
        }
    }
    return sum;
}
