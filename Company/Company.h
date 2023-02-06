#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Office.h"
#include "Invoice.h"

class Office;

enum Enterprise     //rodzaje przedsiębiorstw
{
    JDG,    // jednoosobowa dzialalnosc gospodarcza
    SC,     // Szarotka przedsiebiorstwo wielobranzowe
    ZOO     // Spolka z ograniczona odpowiedzialnoscia
};

using namespace std;

class Company {
    string name;
    Enterprise enterprise;
    vector<Invoice> incomes;
    vector<Invoice> expenses;
public:
    Company(Office& office, string name, vector<Invoice>& incomes, vector<Invoice>& expenses, Enterprise enterprise);
    string getName() const noexcept;
    Enterprise getEnterprise() const noexcept;
    vector<Invoice> getIncomes() const noexcept;
    vector<Invoice> getExpenses() const noexcept;
    Currency sumOfIncomes() const noexcept;
    Currency sumOfExpenses() const noexcept;
    Currency calculateTaxes(Office& office) const noexcept;
    Currency calculateVat() const noexcept;
};

