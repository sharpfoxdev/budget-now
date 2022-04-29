#ifndef MODEL_H
#define MODEL_H

#include "dataClasses.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Model{
public:
    dataNS::BudgetsHolder GetAllBudgets();
    bool CopyBudget(const vector<string> & params);
    bool SetPrimaryBudget(const vector<string> & params);
    bool AddBudget(const vector<string> & params);
    bool AddExpense(const vector<string> & params);
    bool AddCategory(const vector<string> & params);
    bool AddIncome(const vector<string> & params);
    dataNS::Budget GetBudget(const vector<string> & params);
    dataNS::Category GetCategory(const vector<string> & params);
private:
    dataNS::BudgetsHolder allBudgets;
    void SaveBudgetsHolder(dataNS::BudgetsHolder bh);
};

#endif