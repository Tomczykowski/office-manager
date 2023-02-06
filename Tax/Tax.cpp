#include "Tax.h"

vector<string> stringEmploy = { "UOD", "UOP", "UOZ" };
vector<string> stringEnter = { "JDG", "SC", "ZOO" };

bool Tax::isEligible(Person const& person) const noexcept
{
    return std::find(payer_p.begin(), payer_p.end(), person.getEmployment()) != payer_p.end();
}

bool Tax::isEligible(Company const& company) const noexcept
{
    return std::find(payer_c.begin(), payer_c.end(), company.getEnterprise()) != payer_c.end();
}

string Tax::getName() const noexcept
{
    return name;
}

vector<Employment> Tax::getPayer_p() const noexcept
{
    return payer_p;
}

vector<Enterprise> Tax::getPayer_c() const noexcept
{
    return payer_c;
}

ostream& operator<<(ostream& os, Tax& tax) noexcept
{
    return os;
}

bool sortSec(const tuple<float, Currency>& a, const tuple<float, Currency>& b) {
    return (get<1>(a) < get<1>(b));
}

LinearTax::LinearTax(Office& office, string name, float& perValue, vector<Employment>& payer_p, vector<Enterprise>& payer_c)
{
    if (perValue < 0)
        throw std::invalid_argument("");
    this->name = name;
    this->perValue = perValue;
    this->payer_p = payer_p;
    this->payer_c = payer_c;
    office.addTax(*this);
}

Currency LinearTax::calculate(Person const& person)
{
    if (isEligible(person))
        return person.getSalary() * perValue;
    return Currency();
}

Currency LinearTax::calculate(Company const& company)
{
    try {
        isEligible(company);
        //(company.sumOfIncomes() - company.sumOfExpenses()) > Currency();
    }
    catch (invalid_argument) {
        return Currency();
    }
    if (isEligible(company) && ((company.sumOfIncomes() - company.sumOfExpenses()) > Currency()))
        return (company.sumOfIncomes() - company.sumOfExpenses()) * perValue;
    return Currency();
}

float LinearTax::getPerValue() const noexcept
{
    return perValue;
}

ostream& operator<<(ostream& os, LinearTax& tax) noexcept
{
    os << "name: " << tax.getName() << '\n';
    os << "perValue: " << tax.getPerValue() << '\n';
    os << "peoplePayer: ";
    for (auto employment : tax.getPayer_p()) {
        os << stringEmploy[employment] << ", ";
    }
    os << '\n';
    os << "companyPayer: ";
    for (auto enterprise : tax.getPayer_c()) {
        os << stringEnter[enterprise] << ", ";
    }
    os << '\n';
    return os;
}


ProgressiveTax::ProgressiveTax(Office& office, string name, vector<tuple<float, Currency>>& thresholds, vector<Employment>& payer_p, vector<Enterprise>& payer_c)
{
    this->name = name;
    sort(thresholds.begin(), thresholds.end(), sortSec);
    this->thresholds = thresholds;
    this->payer_p = payer_p;
    this->payer_c = payer_c;
    office.addTax(*this);
}

Currency ProgressiveTax::calculate(Person const& person)
{
    Currency sum;
    if (isEligible(person)) {
        if (person.getSalary() < get<1>(thresholds[0]))
            return person.getSalary() * get<0>(thresholds[0]);

        else if (person.getSalary() > get<1>(thresholds[0]))
            sum += get<1>(thresholds[0]) * get<0>(thresholds[0]);

        for (auto i = ++thresholds.begin(); i != thresholds.end(); ++i) {     //thresholds must be sorted
            auto threshold = (*i);
            auto prev_iterator = i - 1;
            auto prev_threshold = *prev_iterator;
            if (person.getSalary() < get<1>(threshold)) {
                Currency value_diff = person.getSalary() - get<1>(prev_threshold);
                sum += value_diff * get<0>(threshold);
                return sum;
            }
            Currency value_diff = get<1>(threshold) - get<1>(prev_threshold);
            sum += (value_diff)*get<0>(threshold);

        }
    }
    return sum;
}

Currency ProgressiveTax::calculate(Company const& company)
{
    Currency sum;
    if (isEligible(company)) {
        try {
            Currency income = company.sumOfIncomes() - company.sumOfExpenses();
        }
        catch (invalid_argument) {
            return Currency();
        }
        Currency income = company.sumOfIncomes() - company.sumOfExpenses();
        if (income < get<1>(thresholds[0]))
            return income * get<0>(thresholds[0]);

        else if (income > get<1>(thresholds[0]))
            sum += get<1>(thresholds[0]) * get<0>(thresholds[0]);

        for (auto i = ++thresholds.begin(); i != thresholds.end(); ++i) {     //thresholds must be sorted
            auto threshold = (*i);
            auto prev_iterator = i - 1;
            auto prev_threshold = *prev_iterator;
            if (income < get<1>(threshold)) {
                Currency value_diff = income - get<1>(prev_threshold);
                sum += value_diff * get<0>(threshold);
                return sum;
            }
            else if (income > get<1>(threshold)) {
                Currency value_diff = get<1>(threshold) - get<1>(prev_threshold);
                sum += (value_diff)*get<0>(threshold);
            }
        }
    }
    return sum;
}

vector<tuple<float, Currency>> ProgressiveTax::getThresholds() const noexcept
{
    return thresholds;
}

ostream& operator<<(ostream& os, ProgressiveTax& tax) noexcept
{
    os << "name: " << tax.getName() << '\n';
    os << "thresholds: ";
    for (auto threshold : tax.getThresholds()) {
        os << '(' << get<0>(threshold) << ',' << get<1>(threshold);
    }
    os << '\n';
    os << "peoplePayer: ";
    for (auto employment : tax.getPayer_p()) {
        os << stringEmploy[employment] << ", ";
    }
    os << '\n';
    os << "companyPayer: ";
    for (auto enterprise : tax.getPayer_c()) {
        os << stringEnter[enterprise] << ", ";
    }
    os << '\n';
    return os;
}

ConstTax::ConstTax(Office& office, string name, Currency& value, vector<Employment>& payer_p, vector<Enterprise>& payer_c) {
    this->name = name;
    this->value = value;
    this->payer_p = payer_p;
    this->payer_c = payer_c;
    office.addTax(*this);
}

Currency ConstTax::calculate(Person const& person)
{
    if (isEligible(person))
        return value;
    return Currency();
}

Currency ConstTax::calculate(Company const& company)
{
    if (isEligible(company))
        return value;
    return Currency();
}

Currency ConstTax::getValue()  const noexcept
{
    return value;
}

ostream& operator<<(ostream& os, ConstTax& tax) noexcept
{
    os << "name: " << tax.getName() << '\n';
    os << "value: " << tax.getValue().zl << ',' << tax.getValue().gr << '\n';
    os << "peoplePayer: ";
    for (auto employment : tax.getPayer_p()) {
        os << stringEmploy[employment] << ", ";
    }
    os << '\n';
    os << "companyPayer: ";
    for (auto enterprise : tax.getPayer_c()) {
        os << stringEnter[enterprise] << ", ";
    }
    os << '\n';
    return os;
}
