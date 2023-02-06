#include "Invoice.h"


Invoice::Invoice(string name, Currency netAmount, float vatRate) {
    this->name = name;
    this->netAmount = netAmount;
    this->vatRate = vatRate/100;
}

string Invoice::getName()
{
    return name;
}

Currency Invoice::getNetAmount()
{
    return netAmount;
}

float Invoice::getVatRate()
{
    return vatRate;
}

Currency Invoice::calculateVat() {
    return netAmount * vatRate;
}
