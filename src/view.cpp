#include "view.hpp"

void HelpView::RenderTo(ostream & stream){
    ifstream f(pathHelpFile);
    if(f.is_open()){
        stream << f.rdbuf();
    }
    stream.flush();
    f.close();
}

void MessageView::RenderTo(ostream & stream){
    if(modelMessage != ""){
        stream << modelMessage << endl;
    }
    stream << message << endl;
    cout.flush();
}

void OperationResultView::RenderTo(ostream & stream){
    if(modelMessage != ""){
        stream << modelMessage << endl;
    }
    if(success){
        stream << "Operation Successful. " << endl;
    }
    else{
        stream << "Operation unsuccessful, please repeat the operation. " << endl;
    }
}

void BudgetInfoView::RenderTo(ostream & stream){
    if(modelMessage != ""){
        stream << modelMessage << endl;
    }
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

void CategoryInfoView::RenderTo(ostream & stream){
    if(modelMessage != ""){
        stream << modelMessage << endl;
    }
    stream << modelMessage;
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

void BudgetsListView::RenderTo(ostream & stream){
    if(modelMessage != ""){
        stream << modelMessage << endl;
    }
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

