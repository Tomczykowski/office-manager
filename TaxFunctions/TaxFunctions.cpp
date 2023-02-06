#include "TaxFunctions.h"
#include <ctype.h>
#include <stdexcept>
#include <algorithm>



using namespace std;

bool isNotNumber(string const& s){
    return (any_of(s.begin(), s.end(), [](char c){return !isdigit(c);}));
}

Currency stringToCurrency(string const& str) {
    if(str.empty())
        throw invalid_argument("Invalid number argument");
    string zl;
    string gr;
    vector<std::string> tokens;
    stringstream iss(str);
    string amount;
    while (std::getline(iss, amount, '.'))
            tokens.push_back(amount);

    gr = "0";
    if(tokens.size() > 1)
        gr = tokens[1];
    zl = tokens[0];
    if(isNotNumber(zl) || isNotNumber(gr))
        throw invalid_argument("Invalid number argument");
    return Currency(stoull(zl), stoi(gr));
}

Person getPersonFromFile(int const& id, Office& office) {
    string strId = to_string(id);
    fstream fileHandle;
    string filename = "C:\\Users\\wojte\\CLionProjects\\projektproi2022_sekula_tomczykowski_pawlak\\PersonList.txt";
    fileHandle.open(filename);
    string personData, line;


    while (getline (fileHandle, line)) {
        stringstream ssLine(line);
        vector<string> personInfo;
        while(std::getline(ssLine, personData, ';')){
            personInfo.push_back(personData);
        }
            if (personInfo[0] == strId) {
                fileHandle.close();
                int personId = stoi(personInfo[0]);
                string name = personInfo[1];
                string surname = personInfo[2];
                int age = stoi(personInfo[3]);
                auto employment = Employment(stoi(personInfo[5]));
                Currency salary = stringToCurrency(personInfo[4]);
                auto person = Person(office, personId, name, surname, age, salary, employment);
                return person;
            }
    }
    fileHandle.close();
    throw std::logic_error("No Person with given id!");
}

void writePersonToFile(Person const& person) {
    string id = to_string(person.getId());
    fstream fileHandle;
    string filename = "C:\\Users\\wojte\\CLionProjects\\projektproi2022_sekula_tomczykowski_pawlak\\PersonList.txt";
    fileHandle.open(filename);
    string line, personData;
    while (getline (fileHandle, line)) {
        stringstream ssLine(line);
        vector<string> personInfo;
        while (std::getline(ssLine, personData, ';')) {
            personInfo.push_back(personData);
        }
        string personId = personInfo[0];
        if(personId == id){
            throw invalid_argument("Person already in Database");
            fileHandle.close();
        }
    }
    fileHandle.close();

    ofstream outfile;
    outfile.open(filename, ios_base::app);
    string name = person.getName();
    string surname = person.getSurname();
    string age = to_string(person.getAge());
    string salary = to_string(person.getSalary().zl) + '.' + to_string(person.getSalary().gr);
    string employment = to_string(person.getEmployment());
    string PersonString = id + ';' + name + ';' + surname + ';' + age + ';' + salary + ';' + employment + '\n';

    outfile << PersonString;
    outfile.close();
}

void AddPeopleToOfficeFromFile(Office& office) {
    fstream fileHandle;
    fileHandle.open("C:\\Users\\wojte\\CLionProjects\\projektproi2022_sekula_tomczykowski_pawlak\\PersonList.txt");
    string line, personData;
    getline (fileHandle, line); // read first line
    while (getline (fileHandle, line)) {
        stringstream ssLine(line);
        vector<string> personInfo;
        while(std::getline(ssLine, personData, ';')){
            personInfo.push_back(personData);
        }
        int personId = stoi(personInfo[0]);
        string name = personInfo[1];
        string surname = personInfo[2];
        int age = stoi(personInfo[3]);
        auto employment = Employment(stoi(personInfo[5]));
        Currency salary = stringToCurrency(personInfo[4]);
        auto person = Person(office, personId, name, surname, age, salary, employment);
        //office.addPerson(person);
    }
}

void clearFile() {
    std::ofstream ofs;
    ofs.open("PersonList.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}


void AddCompanyToOfficeFromFile(Office &office) {
    fstream fileHandle;
    fileHandle.open("C:\\Users\\wojte\\CLionProjects\\projektproi2022_sekula_tomczykowski_pawlak\\CompanyList.txt");
    string line, personData;
    getline (fileHandle, line); // read first line

    while (getline (fileHandle, line)) {
        stringstream ssLine(line);
        vector<string> companyInfo;
        while(std::getline(ssLine, personData, ';')){
            companyInfo.push_back(personData);
        }
        string name = companyInfo[0];
        auto enterprise = Enterprise(stoi(companyInfo[1]));
        vector<Invoice> incomes = ParseInvoice(companyInfo[2]);
        vector<Invoice> expenses = ParseInvoice(companyInfo[3]);

        Company company = Company(office, name, incomes, expenses, enterprise);
    }
}


std::vector<Invoice> ParseInvoice(const string &invoiceStr) {
    std::vector<Invoice> invoices;
    if(invoiceStr == "<>" || invoiceStr == "< >")
        return invoices;
    std::vector<string> parsedInvoice;
    Currency netAmount;
    string parsedWord,name;
    float vatRate;
    bool klamra = false;
    for(char c : invoiceStr){
        if(c == '{')
            parsedWord = "";
        else if(c == ',') {
            if (klamra){
                klamra = false;
                continue;
            }else {
                parsedInvoice.push_back(parsedWord);
                parsedWord = "";
            }
        }
        else if(c == '}'){
            klamra = true;
            parsedInvoice.push_back(parsedWord);
            parsedWord = "";
            name = parsedInvoice[0];
            netAmount = stringToCurrency(parsedInvoice[1]);
            vatRate = stof(parsedInvoice[2]);
            invoices.push_back(Invoice(name, netAmount, vatRate));
            parsedInvoice.clear();
        }
        else
            parsedWord += c;
    }
    return invoices;
}

std::vector<Employment> ParsePayer_P(const string &payerStr) {
    std::vector<Employment> payer_p;
    char emp;
    for(char c : payerStr){
        if(c == ',' || c == '>'){
            payer_p.push_back(Employment(emp - '0'));
        }
        else
            emp = c;
    }
    return payer_p;
}

std::vector<Enterprise> ParsePayer_C(const string &payerStr) {
    std::vector<Enterprise> payer_c;
    char emp;
    for(char c : payerStr){
        if(c == ',' || c == '>'){
            payer_c.push_back(Enterprise(emp - '0'));
        }
        else
            emp = c;
    }
    return payer_c;
}

std::vector<tuple<float, Currency>> ParseThresholds(const string &thresholds) {
    std::vector<tuple<float, Currency>> vectThresholds;
    if(thresholds == "<>" || thresholds == "< >")
        return vectThresholds;
    std::vector<string> parsedTreshold;
    string parsedWord;

    bool klamra = false;
    for(char c : thresholds){
        if(c == '{')
            parsedWord = "";
        else if(c == ',') {
            if (klamra){
                klamra = false;
                continue;
            }else {
                parsedTreshold.push_back(parsedWord);
                parsedWord = "";
            }
        }
        else if(c == '}'){
            klamra = true;
            parsedTreshold.push_back(parsedWord);
            parsedWord = "";
            float stopa = stof(parsedTreshold[0]);
            Currency value = stringToCurrency(parsedTreshold[1]);
            vectThresholds.push_back({stopa, value});
            parsedTreshold.clear();
        }
        else
            parsedWord += c;
    }
    return vectThresholds;
}
