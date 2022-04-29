#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

namespace dataNS{
    struct Expense{
        double amount;
        string comment;
    };
    struct Income{
        double amount;
        string comment;
    };
    struct Category{
        string name;
        double budgeted;
        vector<Expense> expenses;
    };
    struct Budget{
        vector<Income> incomes;
        vector<Category> categories;
    };
    struct BudgetsHolder{
        string primaryBudgetName;
        Budget primaryBudget;
        map<string, Budget> otherBudgets;
    };
}

#endif