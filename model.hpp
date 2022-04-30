#ifndef MODEL_H
#define MODEL_H

#include "dataClasses.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "date.h"
#include "dateManager.hpp"


using json = nlohmann::json;
using namespace std;
using namespace std::chrono;
using namespace date;

class Model{
public:
    dataNS::BudgetsHolder GetBudgetsHolder();
    bool CopyBudget(const vector<string> & params);
    bool SetPrimaryBudget(const vector<string> & params);
    bool AddBudget(const vector<string> & params);
    bool AddExpense(const vector<string> & params);
    bool AddCategory(const vector<string> & params);
    bool AddIncome(const vector<string> & params);
    dataNS::Budget GetBudget(const vector<string> & params);
    dataNS::Category GetCategory(const vector<string> & params);
private:
    DateManager dateManager;
    dataNS::BudgetsHolder allBudgets;
    void SaveBudgetsHolder(dataNS::BudgetsHolder bh);
    const string jsonFile = "budgetData.json";
    void SignalIncorrectNumberOfParams();
    void SignalIncorrectParamType();
    void SignalUsedName();
    void SignalNoPrimaryBudget();
};

#endif