#include <iostream>
#include <algorithm>
#include "Office.h"
#include "TaxFunctions.h"

using namespace std;
int main()
{
    Office office;
    vector<Employment> payer_pProg;
    vector<Enterprise> payer_cProg;
    payer_cProg.push_back(JDG);
    payer_cProg.push_back(SC);
    payer_pProg.push_back((UOZ));
    payer_pProg.push_back((UOD));
    vector<Employment> payer_pLinear;
    vector<Enterprise> payer_cLinear;
    payer_cLinear.push_back(ZOO);
    payer_cLinear.push_back(SC);
    payer_pLinear.push_back((UOP));
    payer_pLinear.push_back((UOD));
    vector<Employment> payer_pConst;
    vector<Enterprise> payer_cConst;
    payer_cConst.push_back(JDG);
    payer_cConst.push_back(SC);
    payer_pConst.push_back((UOZ));
    payer_pConst.push_back((UOP));

    vector<tuple<float, Currency>> vecTuples;
    Currency cur_t(1000, 0);
    vecTuples.push_back(tuple<float, Currency>(10, cur_t));
    AddCompanyToOfficeFromFile(office);
    AddPeopleToOfficeFromFile(office);
    Currency curThre(1000, 0);
    Currency cur(1000, 0);
    float value = 0.1;
    LinearTax linear(office, "linear", value, payer_pLinear, payer_cLinear);
    ConstTax cosTax(office, "const", cur, payer_pConst, payer_cConst);
    ProgressiveTax progressive(office, "progressive", vecTuples, payer_pProg, payer_cProg);

    char wybor;
    while(wybor != '9') {
        cout << "Wybierz co chcesz zobic:" << endl;
        cout << "1 - chce policzyc podatek dla firm" << endl;
        cout << "2 - chce policzyc podatek dla osob" << endl;
        cout << "3 - chce policzyc podatek dla firm i osob" << endl;
        cout << "9 - Zakoncz program" << endl;
        cin>>wybor;
        Currency compTax = office.calculateCompaniesTaxes();
        Currency persTax = office.calculatePeopleTaxes();
        Currency bothTax = office.calculateTaxes();

        switch (wybor)
        {
            case '1':
                cout << compTax<<endl;
                break;
            case '2':
                cout << persTax<<endl;
                break;
            case '3':
                cout << bothTax<<endl;
                break;
            case '9':
                break;
            default:
                cout << "Zly wybor."<<endl;
        }
    }
    return 0;
}
