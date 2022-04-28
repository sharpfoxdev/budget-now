#include "model.hpp"

vector<Budget> Model::GetAllBudgets(){
    Budget budget;
    vector<Budget> vec;
    vec.push_back(budget);
    return vec;
}
bool Model::CopyBudget(const vector<string> & params){
    return true;
}
bool Model::SetPrimaryBudget(const vector<string> & params){
    return true;
}
bool Model::AddBudget(const vector<string> & params){
    return true;
}
bool Model::AddExpense(const vector<string> & params){
    return true;
}
bool Model::AddCategory(const vector<string> & params){
    return true;
}
bool Model::AddIncome(const vector<string> & params){
    return true;
}
Budget Model::GetBudget(const vector<string> & params){
    Budget budget;
    return budget;
}
Category Model::GetCategory(const vector<string> & params){
    Category cat;
    return cat;
}