#pragma once
#include <iostream>
#include <vector>
#include "Currency.h"


class Person;
class Company;
class Tax;

class Office {
    vector<Tax*> supportedTaxes;
    vector<Person> people;
    vector<Company> companies;
public:
    Currency calculateTaxes();
    Currency calculateCompaniesTaxes();
    Currency calculatePeopleTaxes();
    void addTax(Tax& tax);
    void addPerson(Person& person);
    void addCompany(Company& company);
    vector<Tax*> getSupportedTaxes();
    vector<Person> getPeople();
    vector<Company> getCompanies();
    bool check_if_person_is_in_base(int& id);
    bool check_if_company_is_in_base(string& name);
    bool check_if_tax_is_in_base(string& name);
    Currency sum_of_companies_incomes();
    Currency sum_of_people_incomes();
    Currency sum_of_companies_taxes();
    Currency sum_of_people_taxes();
    Currency calculateVatTax();
    void clearOffice();
    void deleteTax(string name);

};
