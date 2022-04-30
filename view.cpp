#include "view.hpp"

/**
 * @brief Prints help text to std::out
 */
void View::PrintHelp(){
    std::ifstream f("howToUse.txt");

    if (f.is_open()){
        std::cout << f.rdbuf();
    }
}
/**
 * @brief Prints to std:out, whether the operation was successful or not
 * @param success true if operation was successful, false if not
 */
void View::PrintOperationResult( bool success){
    if(success){
        cout << "Operation Successful. " << endl;
    }
    else{
        cout << "Operation unsuccessful, please repeat the operation. " << endl;
    }
}
/**
 * @brief Displays detailed information about budget and its categories
 * @param budget Budget to display
 */
void View::PrintBudgetInfo(dataNS::Budget budget){
    double totalIncome = 0;
    double totalExpenditure = 0;
    double totalBudgeted = 0;
    cout << "Categories: " << endl;
    //category handling
    for(const auto &myPair : budget.categories){
        totalBudgeted += myPair.second.budgeted;
        double expenseInCategory = 0;
        for(const auto & expense : myPair.second.expenses){
            expenseInCategory += expense.amount;
        }
        totalExpenditure += expenseInCategory;
        //printing categori information
        cout << "   " << myPair.first << endl;
        cout << "       Budgeted: " << myPair.second.budgeted << endl; 
        cout << "       Expense: " << expenseInCategory << endl;
        cout << "       Left to spend: " << myPair.second.budgeted - expenseInCategory << endl;

    }
    for(const auto &income : budget.incomes) // access by reference to avoid copying
    {
        totalIncome += income.amount;
    }
    //printing budget information
    cout << "Total income: " << totalIncome << endl;
    cout << "Total expenditure: " << totalExpenditure << endl;
    cout << "Total budgeted: " << totalBudgeted << endl;
    cout << "Left to budget: " << totalIncome - totalBudgeted << endl;
}
/**
 * @brief Prints detailed information about category end expenses within
 * @param category category to display
 */
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
/**
 * @brief Prints list of all budgets with marker, which budget it the primary one
 * @param budgets Budgets holder
 */
void View::PrintBudgetsList(dataNS::BudgetsHolder budgets){
    if(budgets.primaryBudgetName == "" && budgets.otherBudgets.size() == 0){
        cout << "No budgets were added yet. Use add_budget <budget_name>. " << endl;
    }
    else{
        cout << budgets.primaryBudgetName << " - primary budget" << endl;
        for ( const auto &myPair : budgets.otherBudgets ) {
            std::cout << myPair.first << endl;
        }
    }
}

