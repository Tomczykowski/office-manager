#include "Office.h"
#include "Tax.h"

Currency Office::calculateTaxes()
{
    return calculateCompaniesTaxes() + calculatePeopleTaxes();
}

Currency Office::calculateCompaniesTaxes()
{
    Currency sum;
    for (auto company : companies)
        sum += company.calculateTaxes(*this);
    return sum;
}

Currency Office::calculatePeopleTaxes()
{
    Currency sum;
    for (auto person : people)
        sum += person.calculateTaxes(*this);
    return sum;
}

void Office::addTax(Tax& tax)
{
    supportedTaxes.push_back(&tax);
}

void Office::addCompany(Company& company)
{
    companies.push_back(company);
}

vector<Tax*> Office::getSupportedTaxes()
{
    return supportedTaxes;
}

vector<Company> Office::getCompanies()
{
    return companies;
}

bool Office::check_if_person_is_in_base(int& id)
{
    for (auto person : people)
        if (person.getId() == id)
            return true;
    return false;
}

bool Office::check_if_company_is_in_base(string& name)
{
    for (auto company : companies)
        if (company.getName() == name)
            return true;
    return false;
}

bool Office::check_if_tax_is_in_base(string& name)
{
    for (auto tax : supportedTaxes)
        if (tax->getName() == name)
            return true;
    return false;
}

Currency Office::sum_of_companies_incomes()
{
    Currency sum;
    for (auto company : companies)
        sum += (company.sumOfIncomes() - company.sumOfExpenses());
    return sum;
}

Currency Office::sum_of_people_incomes()
{
    Currency sum;
    for (auto person : people)
        sum += person.getSalary();
    return sum;
}

Currency Office::sum_of_companies_taxes()
{
    Currency sum;
    for (auto company : companies)
        sum += company.calculateTaxes(*this);
    return sum;
}

Currency Office::sum_of_people_taxes()
{
    Currency sum;
    for (auto person : people)
        sum += person.calculateTaxes(*this);
    return sum;
}

Currency Office::calculateVatTax()
{
    Currency sum;
    for (auto company : companies)
        sum += company.calculateVat();
    return sum;
}

void Office::addPerson(Person& person)
{
    people.push_back(person);
}

void Office::clearOffice() {
    auto itTax = supportedTaxes.begin();
    while (itTax != supportedTaxes.end()) {
        auto temp = itTax;
        ++itTax;
        delete* temp;
    }
    supportedTaxes = {};
    people.erase(people.begin(), people.end());
    companies.erase(companies.begin(), companies.end());
}

void Office::deleteTax(string name) {
    for (auto it = supportedTaxes.begin(); it != supportedTaxes.end(); ++it) {
        Tax* tax = *it;
        if (tax->getName() == name) {
            auto temp = tax;
            supportedTaxes.erase(it);
            delete temp;
            break;
        }
    }
}

vector<Person> Office::getPeople()
{
    return people;
}
