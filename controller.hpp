#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.hpp"
#include "view.hpp"

class Controller{
    //posila raw veci na model
public: 
    void ListAllBudgets();
    void CopyBudget();
    void AddBudget();
    void AddExpense();
    void AddCategory();
    void AddIncome();
    void SetPrimaryBudget();
    void PrintBudgetInfo();
    void PrintCategoryInfo();
    void PrintHelp();
private:

};

#endif