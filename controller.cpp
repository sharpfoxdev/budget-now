#include "controller.hpp"

void Controller::PrintHelp(){
    view.PrintHelp();
}
void Controller::SetPrimaryBudget(const vector<string> & params){
    /*for(const auto& arg : params){
        cout << arg << endl;
    }*/
    bool success = model.CopyBudget(params);
    view.PrintOperationResult(success);
}
void Controller::ListAllBudgets(){
    vector<Budget> budgets = model.GetAllBudgets();
    view.PrintBudgetsList(budgets);
}
void Controller::CopyBudget(const vector<string> & params){
    bool success = model.CopyBudget(params);
    view.PrintOperationResult(success);
}
void Controller::AddBudget(const vector<string> & params){

}
void Controller::AddExpense(const vector<string> & params){

}
void Controller::AddCategory(const vector<string> & params){

}
void Controller::AddIncome(const vector<string> & params){

}
void Controller::PrintBudgetInfo(const vector<string> & params){

}
void Controller::PrintCategoryInfo(const vector<string> & params){

}