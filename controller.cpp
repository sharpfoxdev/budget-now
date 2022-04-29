#include "controller.hpp"

void Controller::PrintHelp(){
    view.PrintHelp();
}
void Controller::SetPrimaryBudget(const vector<string> & params){
    /*for(const auto& arg : params){
        cout << arg << endl;
    }*/
    bool success = model.SetPrimaryBudget(params);
    view.PrintOperationResult(success);
}
void Controller::ListAllBudgets(){
    dataNS::BudgetsHolder budgets = model.GetBudgetsHolder();
    view.PrintBudgetsList(budgets);
}
void Controller::CopyBudget(const vector<string> & params){
    bool success = model.CopyBudget(params);
    view.PrintOperationResult(success);
}
void Controller::AddBudget(const vector<string> & params){
    bool success = model.AddBudget(params);
    view.PrintOperationResult(success);
}
void Controller::AddExpense(const vector<string> & params){
    bool success = model.AddExpense(params);
    view.PrintOperationResult(success);
}
void Controller::AddCategory(const vector<string> & params){
    bool success = model.AddCategory(params);
    view.PrintOperationResult(success);
}
void Controller::AddIncome(const vector<string> & params){
    bool success = model.AddIncome(params);
    view.PrintOperationResult(success);
}
void Controller::PrintBudgetInfo(const vector<string> & params){
    dataNS::Budget budget = model.GetBudget(params);
    view.PrintBudgetInfo(budget);
}
void Controller::PrintCategoryInfo(const vector<string> & params){
    dataNS::Category category = model.GetCategory(params);
    view.PrintCategoryInfo(category);
}