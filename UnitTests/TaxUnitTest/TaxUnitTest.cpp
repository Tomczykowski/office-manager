#include <gtest/gtest.h>
#include "Tax.h"

TEST(TaxUnitTest, LinearTaxBasicConstructor)
{
    Office office;
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    float perValue = 10;
    LinearTax linearTax(office, "Cukrowy", perValue, payer_p, payer_c);
    ASSERT_EQ(linearTax.getName(), "Cukrowy");
    ASSERT_EQ(linearTax.getPayer_c().size(), 0);
    ASSERT_EQ(linearTax.getPayer_p().size(), 0);
    ASSERT_EQ(linearTax.getPerValue(), 10);
}

TEST(TaxUnitTest, LinearTaxIsEligiblePerson) {
    Office office;
    Currency salary(100, 12);
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 2, age = 25;
    Person jan(office, id,name,surname, age, salary, emp);
    float perValue = 10;
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    payer_p.push_back(UOP);
    LinearTax linearTax(office, "Cukrowy", perValue, payer_p, payer_c);
    ASSERT_TRUE(linearTax.isEligible(jan));
}

TEST(TaxUnitTest, LinearTaxIsEligiblePersonEmpty) {
    Office office;
    Currency salary(100, 12);
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 2, age = 25;
    Person jan(office, id,name,surname, age, salary, emp);
    float perValue = 10;
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    LinearTax linearTax(office, "Cukrowy", perValue, payer_p, payer_c);
    ASSERT_TRUE(!linearTax.isEligible(jan));
}

TEST(TaxUnitTest, LinearTaxIsEligibleCompany)
{
    Office office;
    Currency cur(1000, 0);
    Invoice a("wydatki1", cur, 18);
    Invoice b("wydatki2", cur, 18);
    Invoice c("przychody1", cur, 18);
    Invoice d("przychody2", cur, 18);
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    vecIn.push_back(a);
    vecIn.push_back(b);
    vecEx.push_back(c);
    vecEx.push_back(d);
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    payer_c.push_back(ZOO);
    float perV = 12;
    LinearTax linearTaxx(office, "imie", perV, payer_p, payer_c);
    perV = 10;
    LinearTax tax(office, "name", perV, payer_p, payer_c);
    ASSERT_TRUE(linearTaxx.isEligible(company));
}

TEST(TaxUnitTest, LinearTaxIsEligibleCompanyFalse)
{
    Office office;
    Currency cur(1000, 0);
    Invoice a("wydatki1", cur, 18);
    Invoice b("wydatki2", cur, 18);
    Invoice c("przychody1", cur, 18);
    Invoice d("przychody2", cur, 18);
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    vecIn.push_back(a);
    vecIn.push_back(b);
    vecEx.push_back(c);
    vecEx.push_back(d);
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    float perV = 12;
    LinearTax linearTaxx(office, "imie", perV, payer_p, payer_c);
    perV = 10;
    LinearTax tax(office, "name", perV, payer_p, payer_c);
    ASSERT_TRUE(!linearTaxx.isEligible(company));
}

TEST(TaxUnitTest, LinearTaxCalculatePerson) {
    Office office;
    Currency salary(100, 12);
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 2, age = 25;
    Person jan(office, id,name,surname, age, salary, emp);
    vector<Employment> payer_p;
    payer_p.push_back(UOP);
    vector<Enterprise> payer_c;
    float perV = 10;
    LinearTax linearTax(office, "Cukrowy", perV, payer_p, payer_c);
    ASSERT_EQ(linearTax.calculate(jan).zl, 1001);
    ASSERT_EQ(linearTax.calculate(jan).gr, 20);
}

TEST(TaxUnitTest, LinearTaxCalculatePersonIsNotInPayer) {
    Office office;
    Currency salary(100, 12);
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 2, age = 25;
    Person jan(office, id,name,surname, age, salary, emp);
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    float perV = 10;
    LinearTax linearTax(office, "Cukrowy", perV, payer_p, payer_c);
    ASSERT_EQ(linearTax.calculate( jan).zl, 0);
    ASSERT_EQ(linearTax.calculate(jan).gr, 0);
}

TEST(TaxUnitTest, LinearTaxCalculateCompany) {
    Office office;
    Currency cur(100, 12);
    Invoice a("wydatki1", cur, 18);
    Invoice b("wydatki2", cur, 18);
    Invoice c("przychody1", cur, 18);
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    vecIn.push_back(a);
    vecIn.push_back(b);
    vecEx.push_back(c);
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    vector<Enterprise> payer_c;
    payer_c.push_back(ZOO);
    vector<Employment> payer_p;
    float perV = 10;
    LinearTax linearTax(office, "Cukrowy", perV, payer_p, payer_c);
    ASSERT_EQ(linearTax.calculate(company).zl, 1001);
    ASSERT_EQ(linearTax.calculate(company).gr, 20);
}

TEST(TaxUnitTest, LinearTaxCalculateCompanyIsNotInPayer) {
    Office office;
    Currency cur(100, 12);
    Invoice a("wydatki1", cur, 18);
    Invoice b("wydatki2", cur, 18);
    Invoice c("przychody1", cur, 18);
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    vecIn.push_back(a);
    vecIn.push_back(b);
    vecEx.push_back(c);
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    vector<Enterprise> payer_c;
    vector<Employment> payer_p;
    float perV = 10;
    LinearTax linearTax(office, "Cukrowy", perV, payer_p, payer_c);
    ASSERT_EQ(linearTax.calculate(company).zl, 0);
    ASSERT_EQ(linearTax.calculate(company).gr, 0);
}

TEST(TaxUnitTest, ProgressiveTaxBasicConstructor)
{
    Office office;
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    Currency cur(123, 10);
    vector<tuple<float, Currency>> xd;
    xd.push_back(tuple<float, Currency>(12, cur));
    ProgressiveTax tax(office, "Cukrowy", xd, payer_p, payer_c);
    ASSERT_EQ(tax.getName(), "Cukrowy");
    ASSERT_EQ(tax.getPayer_c().size(), 0);
    ASSERT_EQ(tax.getPayer_p().size(), 0);
    ASSERT_EQ(tax.getThresholds(), xd);
}

TEST(TaxUnitTest, ProgressiveTaxCalculate)
{
    Office office;
    vector<Employment> payer_p;
    payer_p.push_back(UOP);
    vector<Enterprise> payer_c;
    Currency salary(11000, 0);
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 2, age = 25;
    Person jan(office, id,name,surname, age, salary, emp);
    Currency cur(1000, 0);
    vector<tuple<float, Currency>> xd;
    xd.push_back(tuple<float, Currency>(10, cur));
    ProgressiveTax tax(office, "Cukrowy", xd, payer_p, payer_c);
    ASSERT_EQ(tax.calculate(jan).zl, 10000);
}

TEST(TaxUnitTest, ProgressiveTaxCalculateCompany)
{
    Office office;
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    payer_c.push_back(ZOO);
    Currency cur(123, 10);
    Invoice a("wydatki1", cur, 18);
    Invoice b("wydatki2", cur, 18);
    Invoice c("przychody1", cur, 18);
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    vecIn.push_back(a);
    vecIn.push_back(b);
    vecEx.push_back(c);
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    Currency cur1(1000, 0);
    vector<tuple<float, Currency>> xd;
    xd.push_back(tuple<float, Currency>(10, cur1));
    ProgressiveTax tax(office, "Cukrowy", xd, payer_p, payer_c);
    ASSERT_EQ(tax.calculate(company).zl, 1231);
    ASSERT_EQ(tax.calculate(company).gr, 0);
}

TEST(TaxUnitTest, ConstTaxBasicConstructor)
{
    Office office;
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    Currency cur(123, 10);
    ConstTax tax(office, "Cukrowy", cur, payer_p, payer_c);
    ASSERT_EQ(tax.getName(), "Cukrowy");
    ASSERT_EQ(tax.getPayer_c().size(), 0);
    ASSERT_EQ(tax.getPayer_p().size(), 0);
    ASSERT_EQ(tax.getValue(), cur);
}

TEST(TaxUnitTest, ConstTaxCalculate)
{
    Office office;
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    Currency cur(123, 10);
    Currency salary(11000, 0);
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 2, age = 25;
    Person jan(office, id,name,surname, age, salary, emp);
    payer_p.push_back(UOP);
    ConstTax tax(office, "Cukrowy", cur, payer_p, payer_c);
    ASSERT_EQ(tax.calculate(jan).zl, 123);
}

TEST(TaxUnitTest, ConstTaxCalculateCompany)
{
    Office office;
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;
    payer_c.push_back(ZOO);
    Currency cur(123, 10);
    Invoice a("wydatki1", cur, 18);
    Invoice b("wydatki2", cur, 18);
    Invoice c("przychody1", cur, 18);
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    vecIn.push_back(a);
    vecIn.push_back(b);
    vecEx.push_back(c);
    Currency salary(11000, 0);
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    ConstTax tax(office, "Cukrowy", cur, payer_p, payer_c);
    ASSERT_EQ(tax.calculate(company).zl, 123);
}
// 8)