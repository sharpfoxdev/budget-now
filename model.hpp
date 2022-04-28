#ifndef MODEL_H
#define MODEL_H

#include "dataClasses.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
class Model{
public:
    vector<Budget> GetAllBudgets();
    bool CopyBudget(const vector<string> & params);
    bool SetPrimaryBudget(const vector<string> & params);
    bool AddBudget(const vector<string> & params);
    bool AddExpense(const vector<string> & params);
    bool AddCategory(const vector<string> & params);
    bool AddIncome(const vector<string> & params);
    Budget GetBudget(const vector<string> & params);
    Category GetCategory(const vector<string> & params);
};

#endif