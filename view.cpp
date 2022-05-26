#include "view.hpp"

/**
 * @brief Prints help text to std::out
 */
void View::PrintHelp(){
    std::ifstream f("howToUse.txt");

    if (f.is_open()){
        std::cout << f.rdbuf();
    }
    f.close();
}
void HelpView::RenderTo(ostream & stream){
    stream << helpSourceStream.rdbuf();
}

void MessageView::RenderTo(ostream & stream){
    stream << message;
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
void OperationResultView::RenderTo(ostream & stream){
    if(success){
        stream << "Operation Successful. " << endl;
    }
    else{
        stream << "Operation unsuccessful, please repeat the operation. " << endl;
    }
}
/**
 * @brief Displays detailed information about budget and its categories
 * @param budget Budget to display
 */
void View::PrintBudgetInfo(dataNS::Budget budget){
    cout << "Start: " << budget.start.ToString() << endl;
    cout << "End: " << budget.end.ToString() << endl;
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
        cout << "       Spent " << (100*expenseInCategory)/myPair.second.budgeted << " \% of budget" << endl;
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
    if(totalIncome > 0){
        cout << "Spent " << (100*totalExpenditure)/totalIncome << " \% of income. " << endl;
    }
}
void BudgetInfoView::RenderTo(ostream & stream){
    stream << "Start: " << budget.start.ToString() << endl;
    stream << "End: " << budget.end.ToString() << endl;
    double totalIncome = 0;
    double totalExpenditure = 0;
    double totalBudgeted = 0;
    stream << "Categories: " << endl;
    //category handling
    for(const auto &myPair : budget.categories){
        totalBudgeted += myPair.second.budgeted;
        double expenseInCategory = 0;
        for(const auto & expense : myPair.second.expenses){
            expenseInCategory += expense.amount;
        }
        totalExpenditure += expenseInCategory;
        //printing categori information
        stream << "   " << myPair.first << endl;
        stream << "       Budgeted: " << myPair.second.budgeted << endl; 
        stream << "       Expense: " << expenseInCategory << endl;
        stream << "       Left to spend: " << myPair.second.budgeted - expenseInCategory << endl;
        stream << "       Spent " << (100*expenseInCategory)/myPair.second.budgeted << " \% of budget" << endl;
    }
    for(const auto &income : budget.incomes) // access by reference to avoid copying
    {
        totalIncome += income.amount;
    }
    //printing budget information
    stream << "Total income: " << totalIncome << endl;
    stream << "Total expenditure: " << totalExpenditure << endl;
    stream << "Total budgeted: " << totalBudgeted << endl;
    stream << "Left to budget: " << totalIncome - totalBudgeted << endl;
    if(totalIncome > 0){
        stream << "Spent " << (100*totalExpenditure)/totalIncome << " \% of income. " << endl;
    }
}
/**
 * @brief Prints detailed information about category end expenses within
 * @param category category to display
 */
void View::PrintCategoryInfo(dataNS::Category category){
    double expenseInCategory = 0;
    cout << "Expenses: " << endl;
    for(const auto & expense : category.expenses){
        cout << expense.date.ToString();
        cout << "   " << expense.amount << " " << expense.comment << endl;
        expenseInCategory += expense.amount;
    }
    cout << "Budgeted: " << category.budgeted << endl; 
    cout << "Expense: " << expenseInCategory << endl;
    cout << "Left to spend: " << category.budgeted - expenseInCategory << endl;
    cout << "Spent " << (100*expenseInCategory)/category.budgeted << " \% of budget" << endl;
}
void CategoryInfoView::RenderTo(ostream & stream){
    double expenseInCategory = 0;
    stream << "Expenses: " << endl;
    for(const auto & expense : category.expenses){
        stream << expense.date.ToString();
        stream << "   " << expense.amount << " " << expense.comment << endl;
        expenseInCategory += expense.amount;
    }
    stream << "Budgeted: " << category.budgeted << endl; 
    stream << "Expense: " << expenseInCategory << endl;
    stream << "Left to spend: " << category.budgeted - expenseInCategory << endl;
    stream << "Spent " << (100*expenseInCategory)/category.budgeted << " \% of budget" << endl;
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
void BudgetsListView::RenderTo(ostream & stream){
    if(budgets.primaryBudgetName == "" && budgets.otherBudgets.size() == 0){
        stream << "No budgets were added yet. Use add_budget <budget_name>. " << endl;
    }
    else{
        stream << budgets.primaryBudgetName << " - primary budget" << endl;
        for ( const auto &myPair : budgets.otherBudgets ) {
            stream << myPair.first << endl;
        }
    }
}

