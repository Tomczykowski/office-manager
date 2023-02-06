#include <gtest/gtest.h>
#include "Person.h"
#include "Tax.h"

TEST(PersonUnitTest, basicConstructor)
{
    Office office;
    Currency cur(10000, 0);
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 2, age = 25;
    Person person(office, id,name,surname, age, cur, emp);
    ASSERT_EQ(person.getId(), id);
    ASSERT_EQ(person.getAge(), age);
    ASSERT_EQ(person.getEmployment(), UOP);
    ASSERT_EQ(person.getSalary().zl, cur.zl);
    ASSERT_EQ(person.getSalary().gr, cur.gr);
}

TEST(PersonUnitTest, calculateTaxes)
{
    Office office;
    vector<Employment> payer_p;
    payer_p.push_back(UOP);
    vector<Enterprise> payer_c;
    Currency salary(10000, 0);
    Currency sal(5000, 0);
    string name = "Jan", surname = "Nowak";
    Employment emp = UOP;
    int id = 2, age = 25;
    Person jan(office, id,name,surname, age, salary, emp);
    Person kamil(office, id,name,surname, age, salary, emp);
    Currency cur(100, 10);
    ConstTax tax(office, "Cukrowy", cur, payer_p, payer_c);
    ASSERT_EQ(jan.calculateTaxes(office).zl, 100);
    ASSERT_EQ(jan.calculateTaxes(office).gr, 10);
}