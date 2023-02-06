#pragma once
#include <iostream>
#include <string>
#include "Currency.h"

using namespace std;

class Invoice {
    string name;
    Currency netAmount;
    float vatRate;
public:
    Invoice(string name, Currency netAmount, float vatRate);
    string getName();
    Currency getNetAmount();
    float getVatRate();
    Currency calculateVat();
};



