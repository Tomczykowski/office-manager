#include <gtest/gtest.h>
#include "Company.h"
#include "Tax.h"

TEST(CompanyUnitTest, basicConstructior)
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
    ASSERT_EQ(company.getName(), "IBM");
    ASSERT_EQ(company.getIncomes()[0].getName(), vecIn[0].getName());
    ASSERT_EQ(company.getIncomes()[0].getVatRate(), vecIn[0].getVatRate());
    ASSERT_EQ(company.getIncomes()[0].getNetAmount(), vecIn[0].getNetAmount());
    ASSERT_EQ(company.getEnterprise(), ZOO);
    ASSERT_EQ(company.getExpenses()[0].getName(), vecEx[0].getName());
    ASSERT_EQ(company.getExpenses()[0].getNetAmount(), vecEx[0].getNetAmount());
    ASSERT_EQ(company.getExpenses()[0].getVatRate(), vecEx[0].getVatRate());
}

TEST(CompanyUnitTest, sumOfExpenses)
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
    ASSERT_EQ(company.sumOfExpenses(), Currency(2000));
}

TEST(CompanyUnitTest, sumOfIncomes)
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
    ASSERT_EQ(company.sumOfIncomes(), Currency(2000));
}

TEST(CompanyUnitTest, calculateeVatInBigger)
{
    Office office;
    Currency cur1(2000, 0);
    Currency cur2(1000, 0);
    Invoice a("wydatki1", cur1, 18);
    Invoice b("wydatki2", cur1, 18);
    Invoice c("przychody1", cur2, 18);
    Invoice d("przychody2", cur2, 18);
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    vecIn.push_back(a);
    vecIn.push_back(b);
    vecEx.push_back(c);
    vecEx.push_back(d);
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    ASSERT_EQ(company.calculateVat().zl, 360);
}



TEST(CompanyUnitTest, calculateeVatExBigger)
{
    Office office;
    Currency cur1(1000, 0);
    Currency cur2(2000, 0);
    Invoice a("wydatki1", cur1, 18);
    Invoice b("wydatki2", cur1, 18);
    Invoice c("przychody1", cur2, 18);
    Invoice d("przychody2", cur2, 18);
    vector<Invoice> vecIn;
    vector<Invoice> vecEx;
    vecIn.push_back(a);
    vecIn.push_back(b);
    vecEx.push_back(c);
    vecEx.push_back(d);
    Company company(office, "IBM", vecIn, vecEx, ZOO);
    ASSERT_EQ(company.calculateVat().zl, 0);
}

TEST(CompanyUnitTest, calculateTaxes)
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
    ASSERT_EQ(company.calculateTaxes(office).zl, 3371);
    ASSERT_EQ(company.calculateTaxes(office).gr, 55);
}

