#include <gtest/gtest.h>
#include "TaxFunctions.h"
#include "Currency.h"
#include "Office.h"
#include "Company.h"

TEST(TaxFunctionUnitTest, stringToCurrencyBasic)
{
    Currency cur = stringToCurrency("1000.12");
    ASSERT_EQ(cur.zl, 1000);
    ASSERT_EQ(cur.gr, 12);
}


TEST(TaxFunctionUnitTest, stringToCurrencyGr0)
{
    Currency cur = stringToCurrency("1000");
    ASSERT_EQ(cur.zl, 1000);
    ASSERT_EQ(cur.gr, 0);
}

TEST(TaxFunctionUnitTest, stringToCurrencyZl0)
{
    Currency cur = stringToCurrency("0.23");
    ASSERT_EQ(cur.zl, 0);
    ASSERT_EQ(cur.gr, 23);
}

TEST(TaxFunctionUnitTest, stringToCurrencyError)
{
    ASSERT_THROW(Currency cur = stringToCurrency("100abc0"), invalid_argument);
}

TEST(TaxFunctionUnitTest, stringToCurrencyError2)
{
    ASSERT_THROW(Currency cur = stringToCurrency("100.a"), invalid_argument);
}

TEST(TaxFunctionUnitTest, stringToCurrencyError3)
{
    ASSERT_THROW(Currency cur = stringToCurrency(""), invalid_argument);
}

TEST(TaxFunctionUnitTest, getPersonFromFile)
{
    Office office;
    Currency salary = stringToCurrency("2500");
    Person person = getPersonFromFile(1,office);
    ASSERT_EQ(person.getAge(), 18);
    ASSERT_EQ(person.getEmployment(), 1);
    ASSERT_EQ(person.getId(), 1);
    ASSERT_EQ(person.getSalary(), salary);
}


TEST(TaxFunctionUnitTest, getPersonFromFileError)
{
    Office office;
    Currency salary = stringToCurrency("2500");
    ASSERT_THROW(getPersonFromFile(0,office), logic_error);
}


TEST(TaxFunctionUnitTest, writePersonToFile)
{
    Currency salary = stringToCurrency("25000");
    Office office;
    string name = "Janek", surname = "Nowakowski";
    Employment emp = UOP;
    int id = 12, age = 25;
    Person jan(office, id,name,surname, age, salary, emp);
    writePersonToFile(jan);
    Person p = getPersonFromFile(12, office);
    ASSERT_EQ(p.getId(), 12);
    ASSERT_EQ(p.getName(), "Janek");
    ASSERT_EQ(p.getSurname(), "Nowakowski");
}

TEST(TaxFunctionUnitTest, writePersonToFileError)
{
    Currency salary = stringToCurrency("2500");
    Office office;
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 2, age = 25;
    Person jan(office, id,name,surname, age, salary, emp);
    ASSERT_THROW(writePersonToFile(jan), invalid_argument);
}

TEST(TaxFunctionUnitTest, addPeopleToOfficeFromFile)
{
    Office office;
    office.clearOffice();
    AddPeopleToOfficeFromFile(office);
    auto people = office.getPeople();
    Person jan = people[10];
    ASSERT_EQ(jan.getId(), 11);
    ASSERT_EQ(jan.getName(), "Jan");
    ASSERT_EQ(jan.getSurname(), "Nowak");
}

