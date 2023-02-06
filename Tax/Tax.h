#pragma once
#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "Person.h"
#include "Company.h"

using namespace std;

extern vector<string> stringEmploy;
extern vector<string> stringEnter;


class Tax {
protected:
    string name;
    vector<Employment> payer_p;
    vector<Enterprise> payer_c;

public:
    bool isEligible(Person const& person) const noexcept;
    bool isEligible(Company const& company) const noexcept;
    string getName() const noexcept;
    vector<Employment> getPayer_p() const noexcept;
    vector<Enterprise> getPayer_c() const noexcept;
    friend ostream& operator<<(ostream& os, Tax& tax) noexcept;
    virtual Currency calculate(Person const& person) = 0;
    virtual Currency calculate(Company const& company) = 0;
    virtual ~Tax() = default;

};

class LinearTax : public Tax {
    float perValue;
public:
    LinearTax(Office& office, string name, float& perValue, vector<Employment>& payer_p, vector<Enterprise>& payer_c);
    Currency calculate(Person const& person) override;
    Currency calculate(Company const& company) override;
    float getPerValue() const noexcept ;
    friend ostream& operator<<(ostream& os, LinearTax& tax) noexcept;
};

class ProgressiveTax : public Tax {
    vector<tuple<float, Currency>> thresholds;
public:
    ProgressiveTax(Office& office, string name, vector<tuple<float, Currency>>& thresholds, vector<Employment>& payer_p, vector<Enterprise>& payer_c);
    Currency calculate(Person const& person) override;
    Currency calculate(Company const& company) override;
    vector<tuple<float, Currency>> getThresholds()  const noexcept;
    friend ostream& operator<<(ostream& os, ProgressiveTax& tax) noexcept;
};

class ConstTax : public Tax {
    Currency value;
public:
    ConstTax(Office& office, string name, Currency& value, vector<Employment>& payer_p, vector<Enterprise>& payer_c);
    Currency calculate(Person const& person) override;
    Currency calculate(Company const& company) override;
    Currency getValue() const noexcept;
    friend ostream& operator<<(ostream& os, ConstTax& tax) noexcept;
};


