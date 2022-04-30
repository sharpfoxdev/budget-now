#include "view.hpp"

void View::PrintHelp(){
    std::ifstream f("howToUse.txt");

    if (f.is_open()){
        std::cout << f.rdbuf();
    }
}
void View::PrintOperationResult( bool success){
    if(success){
        cout << "Operation Successful. " << endl;
    }
    else{
        cout << "Operation unsuccessful, please repeat the operation. " << endl;
    }
}
void View::PrintBudgetInfo(dataNS::Budget budget){
    double totalIncome = 0;
    double totalExpenditure = 0;
    double totalBudgeted = 0;
    cout << "Categories: " << endl;
    for(const auto &myPair : budget.categories){
        totalBudgeted += myPair.second.budgeted;
        double expenseInCategory = 0;
        for(const auto & expense : myPair.second.expenses){
            expenseInCategory += expense.amount;
        }
        totalExpenditure += expenseInCategory;
        cout << "   " << myPair.first << endl;
        cout << "       Budgeted: " << myPair.second.budgeted << endl; 
        cout << "       Expense: " << expenseInCategory << endl;
        cout << "       Left to spend: " << myPair.second.budgeted - expenseInCategory << endl;

    }

    for(const auto &income : budget.incomes) // access by reference to avoid copying
    {
        totalIncome += income.amount;
    }

    cout << "Total income: " << totalIncome << endl;
    cout << "Total expenditure: " << totalExpenditure << endl;
    cout << "Total budgeted: " << totalBudgeted << endl;
    cout << "Left to budget: " << totalIncome - totalBudgeted << endl;
}
void View::PrintCategoryInfo(dataNS::Category category){
    double expenseInCategory = 0;
    cout << "Expenses: " << endl;
    for(const auto & expense : category.expenses){
        cout << "   " << expense.amount << " " << expense.comment << endl;
        expenseInCategory += expense.amount;
    }
    cout << "Budgeted: " << category.budgeted << endl; 
    cout << "Expense: " << expenseInCategory << endl;
    cout << "Left to spend: " << category.budgeted - expenseInCategory << endl;
}
void View::PrintBudgetsList(dataNS::BudgetsHolder budgets){
    if(budgets.primaryBudgetName == "" && budgets.otherBudgets.size() == 0){
        cout << "No budgets specified. " << endl;
    }
    else{
        cout << budgets.primaryBudgetName << " - primary budget" << endl;
        for ( const auto &myPair : budgets.otherBudgets ) {
            std::cout << myPair.first << endl;
        }
    }
}

