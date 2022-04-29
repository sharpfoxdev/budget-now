#include "controller.hpp"

/**
 * @brief Calls view to print help text to CLI
 */
void Controller::PrintHelp(){
    view.PrintHelp();
}

/**
 * @brief Calls model to set primary budget and then calls view to display results. 
 * @param params primary budget parameters
 */
void Controller::SetPrimaryBudget(const vector<string> & params){
    bool success = model.SetPrimaryBudget(params);
    view.PrintOperationResult(success);
}
/**
 * @brief Gets BudgetHolder from Model and then calls View to display it
 */
void Controller::ListAllBudgets(){
    dataNS::BudgetsHolder budgets = model.GetBudgetsHolder();
    view.PrintBudgetsList(budgets);
}
/**
 * @brief Calls Model to copy old budget information into new one. 
 * @param params 
 */
void Controller::CopyBudget(const vector<string> & params){
    bool success = model.CopyBudget(params);
    view.PrintOperationResult(success);
}
/**
 * @brief Adds budget into Model and displays result
 * @param params Budget parameters
 */
void Controller::AddBudget(const vector<string> & params){
    bool success = model.AddBudget(params);
    view.PrintOperationResult(success);
}
/**
 * @brief Adds Expense into Model and displays result through View
 * @param params Expense parameters
 */
void Controller::AddExpense(const vector<string> & params){
    bool success = model.AddExpense(params);
    view.PrintOperationResult(success);
}
/**
 * @brief Adds category into Model and displays result through View
 * @param params Category params
 */
void Controller::AddCategory(const vector<string> & params){
    bool success = model.AddCategory(params);
    view.PrintOperationResult(success);
}
/**
 * @brief Adds income into Model and displays result through View
 * @param params Income params
 */
void Controller::AddIncome(const vector<string> & params){
    bool success = model.AddIncome(params);
    view.PrintOperationResult(success);
}
/**
 * @brief Gets budget from Model and calls View to display it. 
 * @param params Budget params
 */
void Controller::PrintBudgetInfo(const vector<string> & params){
    dataNS::Budget budget = model.GetBudget(params);
    view.PrintBudgetInfo(budget);
}
/**
 * @brief Gets Category from Model and calls View to display it. 
 * @param params Category params
 */
void Controller::PrintCategoryInfo(const vector<string> & params){
    dataNS::Category category = model.GetCategory(params);
    view.PrintCategoryInfo(category);
}