#ifndef VIEW_H
#define VIEW_H

#include "dataClasses.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class View{
public:
    void PrintHelp();
    void PrintBudgetsList(vector<Budget> budgets);
    void PrintOperationResult(bool success);
    void PrintBudgetInfo(Budget budget);
    void PrintCategoryInfo(Category category);
};


#endif