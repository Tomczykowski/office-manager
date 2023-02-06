#pragma once
#include <iostream>
#include "Currency.h"
#include "Office.h"

enum Employment
{
    UOD,    // Umowa o dzielo
    UOP,    // Umowa o prace
    UOZ     // Umowa zlecenie
};

class Person {
    int id;
    std::string name;
    std::string surname;
    int age;
    Currency salary;
    Employment employment;
public:
    Person(Office& office, int& id, std::string& name, std::string& surname, int& age, Currency& salary, Employment& employment);
    int getId() const noexcept;
    int getAge() const noexcept;
    string getName() const noexcept;
    string getSurname() const noexcept;
    Currency getSalary() const noexcept;
    Employment getEmployment() const noexcept;
    Currency calculateTaxes(Office& office) const noexcept;
    friend ostream& operator<<(ostream& exit, Person& person) noexcept;

};

