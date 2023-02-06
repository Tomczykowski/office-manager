
#include <gtest/gtest.h>
#include "Office.h"
#include "Person.h"
#include "Company.h"
#include "Tax.h"


TEST(OfficeUnitTest, addCompany)
{
    Office office;
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    office.addCompany(company);
    ASSERT_EQ(office.getCompanies()[0].getName(), company.getName());
}

TEST(OfficeUnitTest, addPerson)
{
    Office office;
    Currency salary(10000, 0);
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 1, age = 28;
    Person jan(office, id, name, surname, age, salary, emp);
    office.addPerson(jan);
    ASSERT_EQ(office.getPeople()[0].getId(), jan.getId());
}

TEST(OfficeUnitTest, addTax)
{
    Office office;
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    string podatekName = "Cukrowy";
    float  perValue = 25;
    LinearTax tax(office, "Cukrowy", perValue, payer_p, payer_c);
    ASSERT_EQ(office.getSupportedTaxes()[0]->getName(), tax.getName());
}

TEST(OfficeUnitTest, getSupportedTaxes)
{
    Office office;
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    string podatekName = "Cukrowy";
    float  perValue = 25;
    LinearTax tax(office, podatekName, perValue, payer_p, payer_c);
    ASSERT_EQ(office.getSupportedTaxes()[0]->getName(), tax.getName());
}

TEST(OfficeUnitTest, getPeople)
{
    Office office;
    Currency salary(10000, 0);
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 1, age = 28;
    Person jan(office, id, name, surname, age, salary, emp);
    ASSERT_EQ(office.getPeople()[0].getId(), jan.getId());
}

TEST(OfficeUnitTest, getCompanies)
{
    Office office;
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    ASSERT_EQ(office.getCompanies()[0].getName(), company.getName());
}

TEST(OfficeUnitTest, check_if_person_is_in_baseTrue)
{
    Office office;
    Currency salary(10000, 0);
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 1, age = 28;
    Person jan(office, id, name, surname, age, salary, emp);
    office.addPerson(jan);
    int a = 1;
    ASSERT_TRUE(office.check_if_person_is_in_base(a));
}

TEST(OfficeUnitTest, check_if_person_is_in_baseFalse)
{
    Office office;
    int a = 1;
    ASSERT_TRUE(!office.check_if_person_is_in_base(a));
}

TEST(OfficeUnitTest, check_if_company_is_in_baseTrue)
{
    Office office;
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    office.addCompany(company);
    auto a =company.getName();
    ASSERT_TRUE(office.check_if_company_is_in_base(a));
}

TEST(OfficeUnitTest, check_if_company_is_in_baseFalse)
{
    Office office;
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    string a = "abc";
    ASSERT_TRUE(!office.check_if_company_is_in_base(a));
}

TEST(OfficeUnitTest, check_if_tax_is_in_baseTrue)
{
    Office office;
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    string podatekName = "Cukrowy";
    float  perValue = 0.25;
    LinearTax tax(office, podatekName, perValue, payer_p, payer_c);
    string name = "Cukrowy";
    ASSERT_TRUE(office.check_if_tax_is_in_base(name));
}

TEST(OfficeUnitTest, check_if_tax_is_in_baseFalse)
{
    Office office;
    string name = "Cukrowy";
    ASSERT_TRUE(!office.check_if_tax_is_in_base(name));
}

TEST(OfficeUnitTest, sum_of_companies_incomes)
{
    Office office;
    Currency cur(100, 21);
    Invoice a("wydatki1", cur, 18);
    Invoice b("wydatki2", cur, 18);
    Invoice c("przychody1", cur, 10);
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    vecIn.push_back(a);
    vecIn.push_back(b);
    vecEx.push_back(c);
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    ASSERT_EQ(office.sum_of_companies_incomes().zl, 100);
    ASSERT_EQ(office.sum_of_companies_incomes().gr, 21);
}

TEST(OfficeUnitTest, sum_of_people_incomes)
{
    Office office;
    Currency salary(10000, 0);
    Currency sal(5000, 0);
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 1, age = 28;
    Person jan(office, id, name, surname, age, salary, emp);
    Person Kamil(office, id, name, surname, age, sal, emp);
    ASSERT_EQ(office.sum_of_people_incomes().zl, 15000);
    ASSERT_EQ(office.sum_of_people_incomes().gr, 0);
}

TEST(OfficeUnitTest, calculateCompaniesTaxes)
{
    Office office;
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    payer_c.push_back(ZOO);
    Currency podatkowy(2137, 0);
    ConstTax tax(office, "Cukrowy", podatkowy,payer_p, payer_c);
    Currency cur(12345, 50);
    Invoice a("wydatki1", cur, 10);
    Invoice b("wydatki2", cur, 10);
    Invoice c("przychody1", cur, 10);
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    vecIn.push_back(a);
    vecIn.push_back(b);
    vecEx.push_back(c);
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    ASSERT_EQ(office.calculateCompaniesTaxes().zl, 3371);
    ASSERT_EQ(office.calculateCompaniesTaxes().gr, 55);
}

TEST(OfficeUnitTest, calculatePeopleTaxes)
{
    Office office;
    vector<Employment> payer_p;
    payer_p.push_back(UOP);
    vector<Enterprise> payer_c;
    Currency salary(10000, 0);
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 1, age = 28;
    Person jan(office, id, name, surname, age, salary, emp);
    string podatekName = "Cukrowy";
    float  perValue = 0.25;
    LinearTax tax(office, podatekName, perValue, payer_p, payer_c);
    ASSERT_EQ(office.calculatePeopleTaxes().zl, 2500);
    ASSERT_EQ(office.calculatePeopleTaxes().gr, 0);
}

TEST(OfficeUnitTest, calculateTaxes)
{
    Office office;
    vector<Employment> payer_p;
    payer_p.push_back(UOP);
    vector<Enterprise> payer_c;
    payer_c.push_back(ZOO);
    Currency podatkowy(2137, 0);
    ConstTax tax(office, "Cukrowy", podatkowy,payer_p, payer_c);
    Currency cur(12345, 50);
    Invoice a("wydatki1", cur, 10);
    Invoice b("wydatki2", cur, 10);
    Invoice c("przychody1", cur, 10);
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    vecIn.push_back(a);
    vecIn.push_back(b);
    vecEx.push_back(c);
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    Currency salary(10000, 0);
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 1, age = 28;
    Person jan(office, id, name, surname, age, salary, emp);
    ASSERT_EQ(office.calculateTaxes().zl, 5508);
    ASSERT_EQ(office.calculateTaxes().gr, 55);

}
//
//TEST(OfficeUnitTest, calculateCompaniesTaxes)
//{
//    Office office;
//    vector<Employment> payer_p;
//    vector<Enterprise> payer_c;
//    payer_c.push_back(ZOO);
//    Currency cur(123, 10);
//    Invoice a("wydatki1", cur, 18);
//    Invoice b("wydatki2", cur, 18);
//    Invoice c("przychody1", cur, 18);
//    vector<Invoice> vecIn;
//    vector<Invoice> vecEx;
//    vecIn.push_back(a);
//    vecIn.push_back(b);
//    vecEx.push_back(c);
//    Company company(office, "IBM", vecIn, vecEx, ZOO);
//    ConstTax tax(office, "Cukrowy", cur, payer_p, payer_c);
//    ASSERT_EQ(office.calculateCompaniesTaxes().zl, 145);
//    ASSERT_EQ(office.calculateCompaniesTaxes().gr, 25);
//}

