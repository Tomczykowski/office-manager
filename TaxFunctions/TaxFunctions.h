#pragma once
#include <fstream>
#include "Person.h"
#include "Invoice.h"
#include "Company.h"
#include <vector>
#include <sstream>
#include "Tax.h"

class Person;
class Office;

Currency stringToCurrency(string const& str);
Person getPersonFromFile(int const& id, Office& office);
void writePersonToFile(Person const& person);
void AddPeopleToOfficeFromFile(Office& office);
void AddCompanyToOfficeFromFile(Office& office);
std::vector<Employment> ParsePayer_P(std::string const& payerStr);
std::vector<Enterprise> ParsePayer_C(std::string const& payerStr);
std::vector<tuple<float, Currency>> ParseThresholds(std::string const& thresholds);
std::vector<Invoice> ParseInvoice(std::string const& InvoiceStr);

void clearFile();