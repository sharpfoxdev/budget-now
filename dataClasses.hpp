#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

/**
 * @brief Namespace holding structures that hold programs data.
 * This namespace also define functions to convert data from and to json, for
 * this reason they are encapsulated in this namespace to not colide with names
 * in json.hpp library. 
 */
namespace dataNS{
    /**
     * @brief Expense structure
     */
    struct Expense{
        double amount;
        string comment;
    };
    /**
     * @brief Income structure
     */
    struct Income{
        double amount;
        string comment;
    };
    /**
     * @brief Category in budget structure holding its expenses
     */
    struct Category{
        double budgeted;
        vector<Expense> expenses;
    };
    /**
     * @brief Budget structure holding its categories and incomes
     */
    struct Budget{
        vector<Income> incomes;
        map<string, Category> categories;
    };
    /**
     * @brief Structure holding all budgets.
     * Also holding primary budget separately from others for simpler access. 
     */
    struct BudgetsHolder{
        string primaryBudgetName;
        Budget primaryBudget;
        map<string, Budget> otherBudgets;
    };
}

#endif