#include "Person.h"
#include "Tax.h"

Person::Person(Office& office, int& id, std::string& name, std::string& surname, int& age, Currency& salary, Employment& employment) {
    this->id = id;
    this->name = name;
    this->surname = surname;
    this->age = age;
    this->salary = salary;
    this->employment = employment;
    office.addPerson(*this);
}

int Person::getId() const noexcept
{
    return id;
}

int Person::getAge() const noexcept
{
    return age;
}

Currency Person::getSalary() const noexcept
{
    return salary;
}

Employment Person::getEmployment() const noexcept
{
    return employment;
}

Currency Person::calculateTaxes(Office& office) const noexcept
{
    Currency sum;
    vector<Tax*> supportedTaxes = office.getSupportedTaxes();
    for (auto tax : supportedTaxes)
        sum += tax->calculate(*this);
    return sum;
}

ostream& operator<<(ostream& exit, Person& person) noexcept {
    string id = to_string(person.getId());
    string age = to_string(person.getAge());
    string salary = to_string(person.getSalary().zl) + '.' + to_string(person.getSalary().gr);
    int employment = person.getEmployment();
    exit << "id: " + id + '\n';
    exit << "age: " + age + '\n';
    exit << "salary: " + salary + '\n';
    exit << "employment: " + stringEmploy[employment] + '\n';
    return exit;
}

string Person::getName() const noexcept {
    return name;
}

string Person::getSurname() const noexcept{
    return surname;
}

