#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>
#include <iostream>
#include "model.hpp"
#include "view.hpp"

using namespace std;
class Controller{
public: 
    void ListAllBudgets();
    void CopyBudget(const vector<string> & params);
    void AddBudget(const vector<string> & params);
    void AddExpense(const vector<string> & params);
    void AddCategory(const vector<string> & params);
    void AddIncome(const vector<string> & params);
    void SetPrimaryBudget(const vector<string> & params);
    void PrintBudgetInfo(const vector<string> & params);
    void PrintCategoryInfo(const vector<string> & params);
    void PrintHelp();
private:
    View view;
    Model model;
};

#endif